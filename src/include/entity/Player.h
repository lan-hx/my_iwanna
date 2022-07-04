//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PLAYER_H_
#define MY_IWANNA_SRC_ENTITY_PLAYER_H_

#include <cstdint>
#include <istream>

#include "common/common.h"
#include "entity/Entity.h"

#define FIRST_JUMP_CNT_MAX 13
#define SECOND_JUMP_CNT_MAX 7
#define MOVE_CNT_MAX 3

class Player : public Entity {
 public:
  explicit Player();
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
  bool CanJump();
  inline int32_t GetVx() const { return vx_; }
  inline int32_t GetVy() const { return vy_; }
  inline XState GetXState() const { return x_state_; }
  inline YState GetYState() const { return y_state_; }
  // facing_ = 0 : facing left; facing_ = 1 : facing right
  inline int32_t GetFacing() const { return facing_; }

  friend std::istream &operator>>(std::istream &i, Player &p);

 private:
  int32_t vx_, vy_;
  // facing_ = 0 : facing left
  // facing_ = 1 : facing right
  int32_t facing_;
  XState x_state_;
  YState y_state_;
  int32_t jump_cnt_;
  int32_t move_cnt_;
};

std::istream &operator>>(std::istream &i, Player &p);

#endif  // MY_IWANNA_SRC_ENTITY_PLAYER_H_
