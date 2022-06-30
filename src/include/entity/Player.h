//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PLAYER_H_
#define MY_IWANNA_SRC_ENTITY_PLAYER_H_

#include "entity/Entity.h"

class Player : public Entity {
 public:
  enum YState { on_ground, first_jump_begin, first_jump_end, second_jump_begin, second_jump_end };
  enum XState { idle, toleft, toright };
  void SetVx(int vx);
  void SetVy(int vy);
  void SetXState(XState state);
  void SetYState(YState state);
  void SetFacing(int facing);
  int GetVx();
  int GetVy();
  XState GetXState();
  YState GetYState();
  int GetFacing();

 private:
  int vx_, vy_;
  int facing_;
  XState x_state_;
  YState y_state_;
};

#endif  // MY_IWANNA_SRC_ENTITY_PLAYER_H_
