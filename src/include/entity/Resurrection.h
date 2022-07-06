//
// Created by zzh on 2022/7/6.
//

#ifndef MY_IWANNA_RESURRECTION_H
#define MY_IWANNA_RESURRECTION_H
#include "common/common.h"
#include "entity/Entity.h"
class Resurrection : public Entity {
 public:
  explicit Resurrection() : Entity(resurrection) {}

  friend std::istream &operator>>(std::istream &i, Resurrection &b);

 private:
};

std::istream &operator>>(std::istream &i, Resurrection &b);
#endif  // MY_IWANNA_RESURRECTION_H
