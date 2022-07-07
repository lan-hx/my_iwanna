//
// Created by lan on 2022/6/29.
//

#include "entity/Barrier.h"
// #include "common/common.h"

std::istream &operator>>(std::istream &i, Barrier &b) {
  i >> *static_cast<Entity *>(&b);
  assert((b.GetHotArea().GetType() == rectangular) && ("Hot Area of Barrier must be rectangular. "));
  return i;
}