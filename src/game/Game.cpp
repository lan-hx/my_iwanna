//
// Created by lan on 2022/6/29.
//

#include "game/Game.h"

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
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

int32_t Game::Load(const char *file) {
  int32_t file_size;
  int32_t cur_size = 0;
  int32_t entity_num;
  int32_t entity_size;
  int32_t cur_entity_size;
  EntityTypeId entity_type;
  std::vector<Entity *> entity_vec;
  int32_t background_len;
  cur_map_ = file;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  cur_size += StringGetInt(file + cur_size, file_size);
  cur_size += StringGetInt(file + cur_size, entity_num);
  for (int i = 0; i < entity_num; ++i) {
    cur_size += StringGetInt(file + cur_size, entity_size);
    StringGetType(file + cur_size, entity_type);
    entity_vec.emplace_back(nullptr);
    try {
      switch (entity_type) {
        case EntityTypeId::player:
          entity_vec.back() = new Player(file + cur_size);
          break;
        case EntityTypeId::barrier:
          entity_vec.back() = new Barrier(file + cur_size);
          break;
        case EntityTypeId::trap:
          entity_vec.back() = new Trap(file + cur_size);
          break;
        case EntityTypeId::portal:
          entity_vec.back() = new Portal(file + cur_size);
          break;
        case EntityTypeId::invalid_type:
          entity_vec.pop_back();
          break;
      }
    } catch (std::exception &e) {
      in_game_ = false;
      return 1;
    }
    cur_size += entity_size;
  }
  entities_ = new EntitySet(entity_vec);
  cur_size += StringGetInt(file + cur_size, background_len);
  background_pic_ = new char[background_len + 1];
  cur_size += StringGetString(file + cur_size, background_pic_);
  cur_size += StringGetInt(file + cur_size, frame_rate_);
  if (file_size != -1) {
    if (cur_size == file_size) {
      in_game_ = true;
      return 0;
    }
    in_game_ = false;
    return 1;
  }
  in_game_ = true;
  return 0;
}

void Game::Reset() {
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  cur_map_ = nullptr;
  entities_->Destroy();
  delete[] background_pic_;
  background_pic_ = nullptr;
  in_game_ = false;
  frame_rate_ = 60;
}

int32_t Game::ResetAndLoad(const char *file) {
  Reset();
  return Load(file);
}

void Game::Event(const std::vector<std::pair<Qt::Key, bool>> &key_events) {
  for (auto key_event : key_events) {
    std::unordered_map<Qt::Key, std::string>::iterator find_res = key_command_map_.find(key_event.first);
    if (find_res != key_command_map_.end()) {
      command_state_[(*find_res).second] = key_event.second;
    }
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

  Player *player = entities_->GetPlayer();
  bool left = command_state_["Left"];
  bool right = command_state_["Right"];
  bool jump = command_state_["Jump"];
  //   bool shoot = command_state_["Shoot"];
  if (left ^ right) {
    if (left) {
      player->PrepareLeft();
    } else {
      player->PrepareRight();
    }
  } else {
    player->HorizontalIdle();
  }
  if (jump) {
    player->PrepareJump();
  }
}

bool Collide(const Entity &en1, const Entity &en2){
  const HotArea ha1 = en1.GetHotArea();
  const HotArea ha2 = en2.GetHotArea();
  if (en1.GetType() != player){
    return false;
  }
  int32_t x1 = en1.GetX();
  int32_t y1 = en1.GetY();
  int32_t x2 = en2.GetX();
  int32_t y2 = en2.GetY();
  int32_t minx = x1 + ha1.GetX(0);
  int32_t maxx = x1 + ha1.GetX(1);
  int32_t miny = y1 + ha1.GetY(0);
  int32_t maxy = y1 + ha1.GetY(1);
  switch (ha2.GetType()){
    case rectangular:
      return (maxx >= x2 + ha2.GetX(0)) && (x2 + ha2.GetX(1) >= minx) && (maxy >= y2 + ha2.GetY(0)) && (y2 + ha2.GetY(1) >= miny);
    case triangular:
      for (int i = 0; i < 3; ++i){
        int32_t x = ha2.GetX(i);
        int32_t y = ha2.GetY(i);
        if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxx)){
            return true;
        }
      }
      return false;
  }
}