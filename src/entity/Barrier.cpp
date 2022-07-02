//
// Created by lan on 2022/6/29.
//

#include "include/entity/Barrier.h"

std::istream &operator>>(std::istream &i, Barrier &b) {
  i >> *static_cast<Entity *>(&b);
  return i;
}