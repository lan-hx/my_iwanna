//
// Created by lan on 2022/7/4.
//

#include "game/_game_impl.h"

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

std::vector<Entity *> _game_impl::GetEntitySet() const { return entities_->GetEntitySet(); }

_game_impl::_game_impl() {
  key_command_map_[Qt::Key_Left] = "Left";
  key_command_map_[Qt::Key_Right] = "Right";
  key_command_map_[Qt::Key_Shift] = "Jump";
  key_command_map_[Qt::Key_Z] = "Shoot";
  key_command_map_[Qt::Key_A] = "Left";
  key_command_map_[Qt::Key_D] = "Right";
  command_state_["Left"] = 0;
  command_state_["Right"] = 0;
  command_state_["Jump"] = 0;
  command_state_["Shoot"] = 0;
}

const char *_game_impl::GetDebugOutput() {
  static std::string output;
  output.clear();
  Player *player = entities_->GetPlayer();
  output = "x:" + std::to_string(player->GetX()) + " y:" + std::to_string(player->GetY());
  return output.c_str();
}

int32_t _game_impl::Load(const char *file_name) {
  if (strcmp(file_name, "") == 0) {
    in_game_ = false;
    return 1;
  }
  std::ifstream ifs(file_name);
  if (!ifs.is_open()) {
    in_game_ = false;
    return 1;
  }
  cur_map_ = file_name;
  int32_t file_size;
  int32_t entity_num;
  int32_t entity_size;
  EntityTypeId entity_type;
  std::vector<Entity *> entity_vec;
  std::vector<Entity *> player_vec;
  std::vector<Entity *> barrier_vec;
  std::vector<Entity *> trap_vec;
  std::vector<Entity *> portal_vec;
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
          assert((player_vec.empty()) && ("Multiple Player Info"));
          e = player_vec.emplace_back(new Player());
          ifs >> *static_cast<Player *>(e);
          break;
        case EntityTypeId::barrier:
          e = barrier_vec.emplace_back(new Barrier());
          ifs >> *static_cast<Barrier *>(e);
          break;
        case EntityTypeId::trap:
          e = trap_vec.emplace_back(new Trap());
          ifs >> *static_cast<Trap *>(e);
          break;
        case EntityTypeId::portal:
          e = portal_vec.emplace_back(new Portal());
          ifs >> *static_cast<Portal *>(e);
          break;
        case EntityTypeId::invalid_type:
          assert(true && ("Invalid Entity"));
          break;
        default:;
      }
    } catch (std::exception &e) {
      in_game_ = false;
      return 1;
    }
  }
  // entities_ = new EntitySet(std::move(entity_vec));
  entities_ = new EntitySet(std::move(player_vec), std::move(barrier_vec), std::move(trap_vec), std::move(portal_vec));
  ifs >> background_len;
  if (background_len > 0) {
    ifs >> background_pic_;
    assert((static_cast<int32_t>(background_pic_.length()) == background_len) && ("background picture path error"));
  }
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

void _game_impl::CloseMap() {
  dead_ = false;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  cur_map_.clear();
  entities_->Destroy();
  delete entities_;
  entities_ = nullptr;
  background_pic_.clear();
  in_game_ = false;
  frame_rate_ = 60;
}

void _game_impl::Restart() {
  std::string cur_map = cur_map_;
  CloseMap();
  Load(cur_map.c_str());
}

void _game_impl::Event(const Qt::Key &key, bool is_pressed) {
  std::unordered_map<Qt::Key, std::string>::iterator find_res = key_command_map_.find(key);
  if (find_res != key_command_map_.end()) {
    if ((*find_res).second == "Jump") {
      if (is_pressed) {
        if ((command_state_["Jump"] & 1) == 0) {
          command_state_["Jump"] |= 4;
        }
      } else {
        if ((command_state_["Jump"] & 1) == 1) {
          command_state_["Jump"] |= 2;
        }
      }
    }
    if (is_pressed) {
      command_state_[(*find_res).second] |= 1;
    } else {
      command_state_[(*find_res).second] &= 0xFFFFFFFE;
    }
  }
}

void _game_impl::Step() {
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
  for (auto entity : entities_->GetEntitySet()) {
    if (entity->GetType() != EntityTypeId::player) {
      if ((step_cnt_ % entity->GetRefreshRate()) == 0) {
        entity->SetCurState((entity->GetCurState() + 1) % entity->GetStateNum());
      }
    }
  }
  std::unordered_set<Entity *> entity_set;
  int32_t left = command_state_["Left"];
  int32_t right = command_state_["Right"];
  int32_t jump = command_state_["Jump"];
  bool interrupt_jump = false;
  bool break_jump = false;
  bool land = false;
  bool can_jump;
  //   bool shoot = command_state_["Shoot"];
  if ((left != 0) || (right != 0)) {
    if (left != 0) {
      player->PrepareLeft();
    }
    if (right != 0) {
      player->PrepareRight();
    }
  } else {
    player->HorizontalIdle();
  }
  if ((jump & 4) != 0) {
    player->BreakJump();
  }
  can_jump = player->CanJump();
  if ((jump & 1) != 0 || (jump & 2) != 0) {
    if (can_jump) {
      player->PrepareJump();
    }
  }
  if ((jump & 1) == 0) {
    break_jump = true;
  }
  int32_t vx = player->GetVx();
  int32_t vy = player->GetVy();
  if (vy < 6) {
    ++vy;
    player->SetVy(vy);
  }
  int32_t dx = vx;
  int32_t dy = vy;
  player->MoveTo(player->GetX(), player->GetY() + dy);
  for (auto entity : entities_->GetBarrierSet()) {
    if (!entity->IsHidden()) {
      switch (Collide(*player, *entity)) {
        case 1:
          entity_set.emplace(entity);
          if (vy > 0) {
            land = true;
          }
          if (vy < 0) {
            interrupt_jump = true;
          }
          break;
        default:
          break;
      }
    }
  }
  while (!entity_set.empty()) {
    if (dy == 0) {
      if (!dead_) {
        dead_ = true;
        ++death_cnt_;
      }
    }
    if (vy > 0) {
      player->MoveByY(-1);
      --dy;
    } else {
      player->MoveByY(1);
      ++dy;
    }
    for (auto entity : entity_set) {
      switch (Collide(*player, *entity)) {
        case 0:
          entity_set.erase(entity);
          break;
        default:
          break;
      }
    }
  }
  player->MoveTo(player->GetX() + dx, player->GetY());
  for (auto entity : entities_->GetBarrierSet()) {
    if (!entity->IsHidden()) {
      switch (Collide(*player, *entity)) {
        case 1:
          entity_set.emplace(entity);
          break;
        default:
          break;
      }
    }
  }
  while (!entity_set.empty()) {
    if (dx == 0) {
      if (!dead_) {
        dead_ = true;
        ++death_cnt_;
      }
    }
    if (vx > 0) {
      player->MoveByX(-1);
      --dx;
    } else {
      player->MoveByX(1);
      ++dx;
    }
    for (auto entity : entity_set) {
      switch (Collide(*player, *entity)) {
        case 0:
          entity_set.erase(entity);
          break;
        default:
          break;
      }
    }
  }
  if (can_jump && interrupt_jump) {
    player->InteruptJump();
  }
  if (break_jump) {
    player->BreakJump();
  }
  if (land) {
    player->SetYState(landed);
  } else {
    if (jump == 0) {
      if (player->GetYState() == on_ground) {
        player->SetYState(drifting);
      }
    }
  }

  switch (player->GetYState()) {
    case on_ground:
    case landed:
      if (player->GetXState() == idle) {
        if (player->GetFacing() == 1) {
          player->SetCurState(1);
        } else {
          player->SetCurState(5);
        }
      } else {
        if (player->GetFacing() == 1) {
          player->SetCurState(3);
        } else {
          player->SetCurState(7);
        }
      }
      break;
    default:
      if (player->GetVy() < 0) {
        if (player->GetFacing() == 1) {
          player->SetCurState(2);
        } else {
          player->SetCurState(6);
        }
      } else {
        if (player->GetFacing() == 1) {
          player->SetCurState(0);
        } else {
          player->SetCurState(4);
        }
      }
  }

  for (auto entity : entities_->GetTrapSet()) {
    if (!entity->IsHidden()) {
      if (Collide(*player, *entity) != 0) {
        if (!dead_) {
          dead_ = true;
          ++death_cnt_;
        }
      }
    }
  }

  command_state_["Jump"] = command_state_["Jump"] & 1;
}

int32_t Collide(const Entity &en1, const Entity &en2) {
  const HotArea &ha1 = en1.GetHotArea();
  const HotArea &ha2 = en2.GetHotArea();
  if (en1.GetType() != player) {
    return 0;
  }
  int32_t minx = en1.GetX() + ha1.GetX(0);
  int32_t maxx = en1.GetX() + ha1.GetX(1);
  int32_t miny = en1.GetY() + ha1.GetY(0);
  int32_t maxy = en1.GetY() + ha1.GetY(1);
  int32_t ret = 0;
  switch (ha2.GetType()) {
    case rectangular:
      if ((maxx > en2.GetX() + ha2.GetX(0)) && (en2.GetX() + ha2.GetX(1) > minx) && (maxy > en2.GetY() + ha2.GetY(0)) &&
          (en2.GetY() + ha2.GetY(1) > miny)) {
        ret |= 1;
      }
      return ret;
    case triangular: {
      int32_t x1 = en2.GetX() + ha2.GetX(0);
      int32_t y1 = en2.GetY() + ha2.GetY(0);
      int32_t x2 = en2.GetX() + ha2.GetX(1);
      int32_t y2 = en2.GetY() + ha2.GetY(1);
      int32_t x3 = en2.GetX() + ha2.GetX(2);
      int32_t y3 = en2.GetY() + ha2.GetY(2);
      if ((x1 > minx) && (x1 < maxx) && (y1 > miny) && (y1 < maxy)) {
        return 1;
      }
      if ((x2 > minx) && (x2 < maxx) && (y2 > miny) && (y2 < maxy)) {
        return 1;
      }
      if ((x3 > minx) && (x3 < maxx) && (y3 > miny) && (y3 < maxy)) {
        return 1;
      }
      if (InTriangle(minx, miny, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(minx, maxy, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(maxx, miny, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(maxx, maxy, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      return 0;
    }
    case point_set:
      for (int i = 0; i < ha2.GetPointNum(); ++i) {
        int32_t x = en2.GetX() + ha2.GetX(i);
        int32_t y = en2.GetY() + ha2.GetY(i);
        if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy)) {
          return 1;
        }
      }
      return 0;
    case invalid_hotarea_type:
      return 0;
    default:
      return 0;
  }
}
