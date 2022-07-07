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
  inline void SetStartX(const int32_t &x) {start_x_ = x;}
  inline void SetStartY(const int32_t &y) {start_y_ = y;}
  inline int32_t GetStartX(){return start_x_;}
  inline int32_t GetStartY(){return start_y_;}

  friend std::istream &operator>>(std::istream &i, Resurrection &b);

 private:
  int32_t start_x_;
  int32_t start_y_;
};

std::istream &operator>>(std::istream &i, Resurrection &b);
#endif  // MY_IWANNA_RESURRECTION_H
