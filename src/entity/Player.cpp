//
// Created by lan on 2022/6/29.
//

#include "include/entity/Player.h"

void Player::PrepareJump() {
  switch (y_state_) {
    case on_ground:
      vy_ = -6;
      jump_cnt_ = 1;
      y_state_ = first_jump_begin;
      break;
    case first_jump_begin:
      if (jump_cnt_ < 9) {
        vy_ = -6;
        ++jump_cnt_;
      }
      break;
    case first_jump_end:
      vy_ = -6;
      jump_cnt_ = 1;
      y_state_ = second_jump_begin;
      break;
    case second_jump_begin:
      if (jump_cnt_ < 4) {
        vy_ = -6;
        ++jump_cnt_;
      }
      break;
    case drifting:
      vy_ = -6;
      y_state_ = second_jump_begin;
    default:
      break;
  }
}

void Player::Move() { Entity::SetPos(GetX() + vx_, GetY() + vy_); }

void Player::BreakJump() {
  if (y_state_ == first_jump_begin) {
    y_state_ = first_jump_end;
  } else if (y_state_ == second_jump_begin) {
    y_state_ = second_jump_end;
  } else if (y_state_ == landed) {
    y_state_ = on_ground;
  }
}

void Player::InteruptJump() {
  if (y_state_ == first_jump_begin) {
    jump_cnt_ = 9;
    vy_ = 0;
  } else if (y_state_ == second_jump_begin) {
    vy_ = 0;
  }
}

std::istream &operator>>(std::istream &i, Player &p) {
  i >> *static_cast<Entity *>(&p);
  p.vx_ = 0;
  p.vy_ = 0;
  p.facing_ = 0;
  p.x_state_ = idle;
  p.y_state_ = drifting;
  return i;
}
