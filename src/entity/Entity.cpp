//
// Created by lan on 2022/6/29.
//

#include "include/entity/Entity.h"

#include "include/common/common.h"

int32_t Entity::entity_id_cnt = 0;

Entity::Entity(EntityTypeId type) : type_(type) { entity_id_ = entity_id_cnt++; }

Entity::~Entity() {
  for (auto pic : state_pics_) {
    delete[] pic;
  }
}

std::istream &operator>>(std::istream &i, Entity &e) {
  int32_t str_len;
  int32_t draw_type;
  i >> e.entity_id_ >> e.x_ >> e.y_;
  i >> e.hot_area_;
  i >> e.hidden_ >> e.display_priority_ >> e.refresh_rate_ >> e.state_num_;
  for (int j = 0; j < e.state_num_; ++j) {
    i >> str_len;
    auto str = new char[str_len + 1];
    i.read(str, str_len);
    e.state_pics_.emplace_back(str);
  }
  i >> e.width_ >> e.height_ >> draw_type;
  switch (draw_type) {
    case 0:
      e.draw_type_ = scaled;
      break;
    case 1:
      e.draw_type_ = tiled;
      break;
    default:
      e.draw_type_ = tiled;
      break;
  }
  e.cur_state_ = 0;
  return i;
}

int32_t Entity::SerializeTo(char *str) {
  int32_t size = 0;
  size += 8;
  sprintf(str + size, "%8d", type_);
  size += 8;
  sprintf(str + size, "%8d", entity_id_);
  size += 8;
  sprintf(str + size, "%8d", x_);
  size += 8;
  sprintf(str + size, "%8d", y_);
  size += 8;
  size += hot_area_.SerializeTo(str + size);
  sprintf(str + size, "%8d", hidden_);
  size += 8;
  sprintf(str + size, "%8d", display_priority_);
  size += 8;
  sprintf(str + size, "%8d", refresh_rate_);
  size += 8;
  sprintf(str + size, "%8d", state_num_);
  size += 8;
  for (int i = 0; i < state_num_; ++i) {
    int len = strlen(state_pics_[i]);
    sprintf(str + size, "%8d", len);
    size += 8;
    sprintf(str + size, " %s", state_pics_[i]);
    size += len + 1;
  }
  sprintf(str + size, "%8d", width_);
  size += 8;
  sprintf(str + size, "%8d", height_);
  size += 8;
  sprintf(str + size, "%8d", draw_type_);
  size += 8;
  sprintf(str, "%8d", size);
  str[8] = ' ';
  return size;
}