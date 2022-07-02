//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENEMY_H_
#define MY_IWANNA_SRC_ENTITY_ENEMY_H_

#include "entity/Entity.h"

class Trap : public Entity {
 public:
  explicit Trap() : Entity(trap) {}

  friend std::istream &operator>>(std::istream &i, Trap &t);

 private:
};

std::istream &operator>>(std::istream &i, Trap &t);

#endif  // MY_IWANNA_SRC_ENTITY_ENEMY_H_
