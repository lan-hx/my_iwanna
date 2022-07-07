//
// Created by lan on 2022/6/29.
//

#include "entity/Portal.h"

std::istream &operator>>(std::istream &i, Portal &p) {
  i >> *static_cast<Entity *>(&p);
  return i;
}
