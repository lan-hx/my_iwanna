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
  void Load(const char*);
  void Reset();
  void ResetAndLoad(const char*);
  void Event(std::vector<std::pair<char, bool>>);
  void Step();
  void CloseMap();
  bool MapLoaded();
  std::vector<Entity *> GetEntitySet() const;

 private:
  bool dead_ = false;
  int death_cnt_ = 0;
  long long step_cnt_ = 0ll;
  const char* cur_map_;
  EntitySet *entities_;
};

#endif  // MY_IWANNA_SRC_GAME_GAME_H_
