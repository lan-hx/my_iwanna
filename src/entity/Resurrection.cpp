//
// Created by zzh on 2022/7/6.
//
#include "entity/Resurrection.h"
std::istream &operator>>(std::istream &i, Resurrection &p) {
  i >> *static_cast<Entity *>(&p);
  assert((p.GetHotArea().GetType() == rectangular) && ("Hot Area of Resurrection must be rectangular. "));
  return i;
}