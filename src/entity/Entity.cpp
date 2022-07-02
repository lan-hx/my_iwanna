//
// Created by lan on 2022/6/29.
//

#include "include/entity/Entity.h"

#include "include/common/common.h"

Entity::Entity(EntityTypeId type) : type_(type) {}

Entity::~Entity() {
  for (auto pic : state_pics_) {
    delete[] pic;
  }
}

void Entity::SetPos(const int32_t &x, const int32_t &y) {
  x_ = x;
  y_ = y;
}

std::istream &operator>>(std::istream &i, Entity &e) {
  int32_t str_len;
  i >> e.entity_id_ >> e.x_ >> e.y_;
  i >> e.hot_area_;
  i >> e.hidden_ >> e.display_priority_ >> e.refresh_rate_ >> e.state_num_;
  for (int j = 0; j < e.state_num_; ++j) {
    i >> str_len;
    auto str = new char[str_len + 1];
    i.read(str, str_len);
    e.state_pics_.emplace_back(str);
  }
  e.cur_state_ = 0;
  return i;
}
