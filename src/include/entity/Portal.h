//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PORTAL_H_
#define MY_IWANNA_SRC_ENTITY_PORTAL_H_

#include "entity/Entity.h"

class Portal : public Entity {
 public:
  explicit Portal() = default;

  friend std::istream &operator>>(std::istream &i, Portal &p);

 private:
};

std::istream &operator>>(std::istream &i, Portal &p);

#endif  // MY_IWANNA_SRC_ENTITY_PORTAL_H_
