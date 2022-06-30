//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_GAME_GAME_H_
#define MY_IWANNA_SRC_GAME_GAME_H_

#include <cstdint>
#include <vector>

#include "entityset/EntitySet.h"

class Entity;

class Game {
 public:
  int32_t Load(const char *file);
  void Reset();
  int32_t ResetAndLoad(const char *);
  void Event(std::vector<std::pair<char, bool>>);
  void Step();
  void CloseMap();
  bool MapLoaded();
  bool InGame() const;
  int32_t GetFrameRate() const;
  void SetFrameRate(int32_t);
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const;

 private:
  bool dead_ = false;
  int32_t death_cnt_ = 0;
  int64_t step_cnt_ = 0LL;
  const char *cur_map_;
  EntitySet *entities_;
  char *background_pic_;
  bool in_game_;
  int32_t frame_rate_ = 60;
};

#endif  // MY_IWANNA_SRC_GAME_GAME_H_
