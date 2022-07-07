//
// Created by lan on 2022/6/29.
//

#include "include/entity/Portal.h"

std::istream &operator>>(std::istream &i, Portal &p) {
  i >> *static_cast<Entity *>(&p);
  i >> p.success_;
  int32_t map_len;
  i >> map_len;
  if (map_len > 0){
    i >> p.map_;
  }
  assert((map_len == p.map_.length()) && ("path error"));
  return i;
}
