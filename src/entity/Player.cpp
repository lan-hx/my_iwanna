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