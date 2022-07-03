//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_BARRIER_H_
#define MY_IWANNA_SRC_ENTITY_BARRIER_H_

#include "common/common.h"
#include "entity/Entity.h"

class Barrier : public Entity {
 public:
  explicit Barrier() : Entity(barrier) {}

  friend std::istream &operator>>(std::istream &i, Barrier &b);

 private:
};

std::istream &operator>>(std::istream &i, Barrier &b);

#endif  // MY_IWANNA_SRC_ENTITY_BARRIER_H_
