//
// Created by lan on 2022/6/29.
//

#include "include/entity/Entity.h"

#include "include/common/common.h"

Entity::Entity(const char *file) {
  int32_t size = 0;
  int32_t str_len;
  size += StringGetType(file + size, type_);
  size += StringGetInt(file + size, entity_id_);
  size += StringGetInt(file + size, x_);
  size += StringGetInt(file + size, y_);
  size += hot_area_.Load(file + size);
  size += StringGetInt(file + size, hidden_);
  size += StringGetInt(file + size, display_priority_);
  size += StringGetInt(file + size, refresh_rate_);
  size += StringGetInt(file + size, state_num_);
  for (int i = 0; i < state_num_; ++i) {
    size += StringGetInt(file + size, str_len);
    state_pics_.emplace_back(nullptr);
    state_pics_.back() = new char(str_len + 1);
    size += StringGetString(file + size, state_pics_.back());
  }
  cur_state_ = 0;
}

Entity::~Entity() {
  for (auto pic : state_pics_) {
    delete[] pic;
  }
}

const HotArea& Entity::GetHotArea()const{
  return hot_area_;
}

EntityTypeId Entity::GetType() const{
  return type_;
}