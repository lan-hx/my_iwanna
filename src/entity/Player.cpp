//
// Created by lan on 2022/6/29.
//

#include "entity/Player.h"

Player::Player() : Entity(player) {
  vx_ = 0;
  vy_ = 0;
  facing_ = 1;
  x_state_ = idle;
  y_state_ = drifting;
}

void Player::PrepareJump() {
  switch (y_state_) {
    case on_ground:
      vy_ = -6;
      jump_cnt_ = 1;
      y_state_ = first_jump_begin;
      break;
    case first_jump_begin:
      if (jump_cnt_ < FIRST_JUMP_CNT_MAX) {
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
      if (jump_cnt_ < SECOND_JUMP_CNT_MAX) {
        vy_ = -6;
        ++jump_cnt_;
      }
      break;
    case drifting:
      vy_ = -6;
      jump_cnt_ = 1;
      y_state_ = second_jump_begin;
    default:
      break;
  }
}

bool Player::CanJump() {
  switch (y_state_) {
    case on_ground:
      return true;
    case first_jump_begin:
      return (jump_cnt_ < FIRST_JUMP_CNT_MAX);
    case first_jump_end:
      return true;
    case second_jump_begin:
      return (jump_cnt_ < SECOND_JUMP_CNT_MAX);
    case drifting:
      return true;
    default:
      return false;
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
    vy_ = 0;
    jump_cnt_ = FIRST_JUMP_CNT_MAX;
  } else if (y_state_ == second_jump_begin) {
    vy_ = 0;
    jump_cnt_ = SECOND_JUMP_CNT_MAX;
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

void Player::PrepareLeft() {
  switch (x_state_) {
    case idle:
      vx_ -= 2;
      facing_ = 0;
      move_cnt_ = 1;
      x_state_ = moving;
      break;
    case moving:
      if (facing_ == 0) {
        if (move_cnt_ < MOVE_CNT_MAX) {
          --vx_;
          ++move_cnt_;
        }
      } else if (facing_ == 1) {
        vx_ -= move_cnt_ + 1;
        vx_ -= 2;
        facing_ = 0;
        move_cnt_ = 1;
      }
      break;
    default:
      break;
  }
}

void Player::PrepareRight() {
  switch (x_state_) {
    case idle:
      vx_ += 2;
      facing_ = 1;
      move_cnt_ = 1;
      x_state_ = moving;
      break;
    case moving:
      if (facing_ == 1) {
        if (move_cnt_ < MOVE_CNT_MAX) {
          ++vx_;
          ++move_cnt_;
        }
      } else if (facing_ == 0) {
        vx_ += move_cnt_ + 1;
        vx_ += 2;
        facing_ = 1;
        move_cnt_ = 1;
      }
      break;
    default:
      break;
  }
}

void Player::HorizontalIdle() {
  switch (x_state_) {
    case idle:
      break;
    case moving:
      if (facing_ == 1) {
        vx_ -= move_cnt_ + 1;
        move_cnt_ = 0;
        x_state_ = idle;
      } else if (facing_ == 0) {
        vx_ += move_cnt_ + 1;
        move_cnt_ = 0;
        x_state_ = idle;
      }
      break;
    default:
      break;
  }
}