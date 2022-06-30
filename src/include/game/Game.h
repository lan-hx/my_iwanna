//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_GAME_GAME_H_
#define MY_IWANNA_SRC_GAME_GAME_H_

#include <vector>

#include "entityset/EntitySet.h"

class Entity;

class Game {
 public:
  void Event(std::vector<std::pair<char, bool>>);
  void Step();
  std::vector<Entity *> GetEntitySet() const;

 private:
  bool dead_ = false;
  EntitySet *entities_;
};

#endif  // MY_IWANNA_SRC_GAME_GAME_H_
