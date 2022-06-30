//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PLAYER_H_
#define MY_IWANNA_SRC_ENTITY_PLAYER_H_

#include <cstdint>

#include "common/common.h"
#include "entity/Entity.h"

class Player : public Entity {
 public:
  explicit Player(const char *file);
  void SetVx(int32_t vx);
  void SetVy(int32_t vy);
  void SetXState(XState state);
  void SetYState(YState state);
  void SetFacing(int32_t facing);
  void PrepareLeft();
  void PrepareRight();
  void HorizontalIdle();
  void PrepareJump();
  void Jump();
  void TowardsLeft();
  void TowardsRight();
  int32_t GetVx();
  int32_t GetVy();
  XState GetXState();
  YState GetYState();
  // facing_ = 0 : facing left
  // facing_ = 1 : facing right
  int32_t GetFacing();

 private:
  int32_t vx_, vy_;
  // facing_ = 0 : facing left
  // facing_ = 1 : facing right
  int32_t facing_;
  XState x_state_;
  YState y_state_;
  int32_t jump_cnt_;
};

#endif  // MY_IWANNA_SRC_ENTITY_PLAYER_H_
