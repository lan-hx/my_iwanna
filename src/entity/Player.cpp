//
// Created by lan on 2022/6/29.
//

#include "include/entity/Player.h"

Player::Player(const char *file) : Entity(file) {
  vx_ = 0;
  vy_ = 0;
  facing_ = 0;
  x_state_ = idle;
  y_state_ = on_ground;
}

void Player::PrepareJump() {
  switch (y_state_) {
    case on_ground:
      vy_ = 6;
      jump_cnt_ = 1;
      y_state_ = first_jump_begin;
      break;
    case first_jump_begin:
      if (jump_cnt_ < 8) {
        vy_ = 6;
        ++jump_cnt_;
        y_state_ = first_jump_begin;
      } else {
        vy_ = 6;
        jump_cnt_ = 0;
        y_state_ = first_jump_end;
      }
      break;
    case first_jump_end:
      vy_ = 6;
      y_state_ = second_jump_begin;
      break;
    case second_jump_begin:
      vy_ = 6;
      y_state_ = second_jump_end;
      break;
    case second_jump_end:
      if (vy_ > -6) {
        --vy_;
      }
      break;
  }
}