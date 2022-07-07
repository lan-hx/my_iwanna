//
// Created by lan on 2022/6/29.
//

#include "entity/Trap.h"

std::istream &operator>>(std::istream &i, Trap &t) {
  i >> *static_cast<Entity *>(&t);
  return i;
}
