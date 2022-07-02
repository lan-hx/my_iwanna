//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PLAYER_H_
#define MY_IWANNA_SRC_ENTITY_PLAYER_H_

#include <cstdint>
#include <istream>

#include "common/common.h"
#include "entity/Entity.h"

class Player : public Entity {
 public:
  explicit Player() : Entity(player) {}
  inline void SetVx(int32_t vx) { vx_ = vx; }
  inline void SetVy(int32_t vy) { vy_ = vy; }
  inline void SetXState(XState state) { x_state_ = state; }
  inline void SetYState(YState state) { y_state_ = state; }
  inline void SetFacing(int32_t facing) { facing_ = facing; }
  void PrepareLeft();
  void PrepareRight();
  void HorizontalIdle();
  void PrepareJump();
  void Jump();
  void TowardsLeft();
  void TowardsRight();
  void Move();
  void BreakJump();
  void InteruptJump();
  inline int32_t GetVx() const { return vx_; }
  inline int32_t GetVy() const { return vy_; }
  XState GetXState();
  YState GetYState();
  // facing_ = 0 : facing left
  // facing_ = 1 : facing right
  int32_t GetFacing();

  friend std::istream &operator>>(std::istream &i, Player &p);

 private:
  int32_t vx_, vy_;
  // facing_ = 0 : facing left
  // facing_ = 1 : facing right
  int32_t facing_;
  XState x_state_;
  YState y_state_;
  int32_t jump_cnt_;
};

std::istream &operator>>(std::istream &i, Player &p);

#endif  // MY_IWANNA_SRC_ENTITY_PLAYER_H_
