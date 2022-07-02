//
// Created by lan on 2022/6/29.
//

#include "game/Game.h"

#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <unordered_set>
#include <vector>

#include "common/common.h"
#include "entity/Barrier.h"
#include "entity/Player.h"
#include "entity/Portal.h"
#include "entity/Trap.h"
#include "hotarea/HotArea.h"

std::vector<Entity *> Game::GetEntitySet() const { return entities_->GetEntitySet(); }

Game::Game() {
  key_command_map_[Qt::Key_Left] = "Left";
  key_command_map_[Qt::Key_Right] = "Right";
  key_command_map_[Qt::Key_Shift] = "Jump";
  key_command_map_[Qt::Key_Z] = "Shoot";
  command_state_["Left"] = false;
  command_state_["Right"] = false;
  command_state_["Jump"] = false;
  command_state_["Shoot"] = false;
}

int32_t Game::Load(const char *file_name) {
  if (strcmp(file_name, "") == 0) {
    in_game_ = false;
    return 1;
  }
  std::ifstream ifs(file_name);
  if (!ifs.is_open()) {
    in_game_ = false;
    return 1;
  }
  int32_t file_size;
  int32_t entity_num;
  int32_t entity_size;
  int32_t cur_entity_size;
  EntityTypeId entity_type;
  std::vector<Entity *> entity_vec;
  int32_t background_len;
  dead_ = false;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  ifs >> file_size >> entity_num;
  for (int i = 0; i < entity_num; ++i) {
    ifs >> entity_size >> entity_type;
    try {
      Entity *e = nullptr;
      switch (entity_type) {
        case EntityTypeId::player:
          e = entity_vec.emplace_back(new Player());
          ifs >> *static_cast<Player *>(e);
          break;
        case EntityTypeId::barrier:
          e = entity_vec.emplace_back(new Barrier());
          ifs >> *static_cast<Barrier *>(e);
          break;
        case EntityTypeId::trap:
          e = entity_vec.emplace_back(new Trap());
          ifs >> *static_cast<Trap *>(e);
          break;
        case EntityTypeId::portal:
          e = entity_vec.emplace_back(new Portal());
          ifs >> *static_cast<Portal *>(e);
          break;
        case EntityTypeId::invalid_type:
          break;
        default:;
      }
    } catch (std::exception &e) {
      in_game_ = false;
      return 1;
    }
  }
  entities_ = new EntitySet(std::move(entity_vec));
  ifs >> background_len;
  ifs >> background_pic_;
  assert((background_pic_.length() == background_len) && ("background picture path error"));
  ifs >> frame_rate_;
  if (ifs.eof()) {
    ifs.close();
    in_game_ = true;
    return 0;
  }
  ifs.close();
  in_game_ = false;
  return 1;
}

void Game::Reset() {
  dead_ = false;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  entities_->Destroy();
  delete entities_;
  entities_ = nullptr;
  background_pic_.clear();
  background_pic_ = nullptr;
  in_game_ = false;
  frame_rate_ = 60;
}

int32_t Game::ResetAndLoad(const char *file) {
  Reset();
  return Load(file);
}

void Game::Event(const Qt::Key &key, bool is_pressed) {
  std::unordered_map<Qt::Key, std::string>::iterator find_res = key_command_map_.find(key);
  if (find_res != key_command_map_.end()) {
    command_state_[(*find_res).second] = is_pressed;
  }
}

void Game::Step() {
  // for all tracks
  // if activated
  //     move the corresponding entity

  // update vx
  // update vy

  // dx = vx
  // dy = vy

  // while (dx || dy)
  //     if (abs((dx - 1) * vy - vx * dy) < abs(dx * vy - vx * (dy - 1)))
  //         move x by 1 pixel
  //         decrease dx
  //         check death
  //         check track activations
  //         if collide with barrier
  //             rollback x
  //             dx = 0
  //     else
  //         similar
  ++step_cnt_;
  Player *player = entities_->GetPlayer();
  std::unordered_set<Entity *> entity_set;
  bool left = command_state_["Left"];
  bool right = command_state_["Right"];
  bool jump = command_state_["Jump"];
  bool collision = false;
  //   bool shoot = command_state_["Shoot"];
  if (left ^ right) {
    if (left) {
      //   player->PrepareLeft();
    } else {
      //   player->PrepareRight();
    }
  } else {
    // player->HorizontalIdle();
  }
  if (jump) {
    player->PrepareJump();
  }
  int32_t vx = player->GetVx();
  int32_t vy = player->GetVy();
  int32_t dx = vx;
  int32_t dy = vy;
  player->Move();
  for (auto entity : entities_->GetEntitySet()) {
    if (entity->GetType() == EntityTypeId::barrier) {
      if (!entity->IsHidden()) {
        if (Collide(*player, *entity)) {
          entity_set.emplace(entity);
        }
      }
    }
  }
  if (!entity_set.empty()) {
    player->BreakJump();
  }
  while (!entity_set.empty()) {
    if ((dx == 0) && (dy == 0)) {
      dead_ = true;
      return;
    }
    if (abs((dx - 1) * vy - vx * dy) < abs(dx * vy - vx * (dy - 1))) {
      if (vx > 0) {
        player->MoveX(-1);
        --dx;
      } else {
        player->MoveX(1);
        ++dx;
      }
    } else {
      if (vy > 0) {
        player->MoveY(-1);
        --dy;
      } else {
        player->MoveY(1);
        ++dy;
      }
    }
    for (auto entity : entity_set) {
      if (!Collide(*player, *entity)) {
        entity_set.erase(entity);
      }
    }
  }
}

bool Collide(const Entity &en1, const Entity &en2) {
  const HotArea &ha1 = en1.GetHotArea();
  const HotArea &ha2 = en2.GetHotArea();
  if (en1.GetType() != player) {
    return false;
  }
  int32_t minx = en1.GetX() + ha1.GetX(0);
  int32_t maxx = en1.GetX() + ha1.GetX(1);
  int32_t miny = en1.GetY() + ha1.GetY(0);
  int32_t maxy = en1.GetY() + ha1.GetY(1);
  switch (ha2.GetType()) {
    case rectangular:
      return (maxx >= en2.GetX() + ha2.GetX(0)) && (en2.GetX() + ha2.GetX(1) >= minx) &&
             (maxy >= en2.GetY() + ha2.GetY(0)) && (en2.GetY() + ha2.GetY(1) >= miny);
    case triangular: {
      int32_t x1 = en2.GetX() + ha2.GetX(0);
      int32_t y1 = en2.GetY() + ha2.GetY(0);
      int32_t x2 = en2.GetX() + ha2.GetX(1);
      int32_t y2 = en2.GetY() + ha2.GetY(1);
      int32_t x3 = en2.GetX() + ha2.GetX(2);
      int32_t y3 = en2.GetY() + ha2.GetY(2);
      if ((x1 >= minx) && (x1 <= maxx) && (y1 >= miny) && (y1 <= maxy)) {
        return true;
      }
      if ((x2 >= minx) && (x2 <= maxx) && (y2 >= miny) && (y2 <= maxy)) {
        return true;
      }
      if ((x3 >= minx) && (x3 <= maxx) && (y3 >= miny) && (y3 <= maxy)) {
        return true;
      }
      if (InTriangle(minx, miny, x1, y1, x2, y2, x3, y3)) {
        return true;
      }
      if (InTriangle(minx, maxy, x1, y1, x2, y2, x3, y3)) {
        return true;
      }
      if (InTriangle(maxx, miny, x1, y1, x2, y2, x3, y3)) {
        return true;
      }
      if (InTriangle(maxx, maxy, x1, y1, x2, y2, x3, y3)) {
        return true;
      }
      return false;
    }
    case point_set:
      for (int i = 0; i < ha2.GetPointNum(); ++i) {
        int32_t x = en2.GetX() + ha2.GetX(i);
        int32_t y = en2.GetY() + ha2.GetY(i);
        if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy)) {
          return true;
        }
      }
      return false;
    case invalid_hotarea_type:
      return false;
    default:
      return false;
  }
}