//
// Created by lan on 2022/6/29.
//

#include "include/entity/Portal.h"

std::istream &operator>>(std::istream &i, Portal &p) {
  i >> *static_cast<Entity *>(&p);
  i >> p.success_;
  int32_t map_len;
  i >> map_len;
  if (map_len > 0) {
    i >> p.map_;
  }
  assert((map_len == static_cast<int32_t>(p.map_.length())) && ("path error"));
  return i;
}

int32_t Portal::SerializeTo(char *str) {
  int32_t size = 0;
  size += Entity::SerializeTo(str);
  sprintf(str + size, "%8d", success_);
  size += 8;
  sprintf(str + size, "%8lld", map_.length());
  size += 8;
  sprintf(str + size, " %s", map_.c_str());
  size += map_.length() + 1;
  return size;
}