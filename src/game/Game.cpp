//
// Created by lan on 2022/6/29.
//

#include "include/game/Game.h"

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <vector>

#include "include/common/common.h"
#include "include/entity/Barrier.h"
#include "include/entity/Player.h"
#include "include/entity/Portal.h"
#include "include/entity/Trap.h"

std::vector<Entity *> Game::GetEntitySet() const { return entities_->GetEntitySet(); }

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