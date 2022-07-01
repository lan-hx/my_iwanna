//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_GAME_GAME_H_
#define MY_IWANNA_SRC_GAME_GAME_H_

#include <Qt>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "entity/Entity.h"
#include "entityset/EntitySet.h"

class Entity;

class Game {
 public:
  explicit Game();
  int32_t Load(const char *file);
  void Reset();
  int32_t ResetAndLoad(const char *file);
  void Event(const std::vector<std::pair<Qt::Key, bool>> &key_events);
  void Step();
  void CloseMap();
  bool MapLoaded();
  bool InGame() const;
  int32_t GetFrameRate() const;
  void SetFrameRate(int32_t);
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const;
  inline bool IsDead() const { return dead_; }
  inline int32_t DeathCount() const { return death_cnt_; }
  inline double PlayTime() const { return static_cast<double>(step_cnt_) / static_cast<double>(frame_rate_); }

 private:
  bool dead_ = false;
  int32_t death_cnt_ = 0;
  int64_t step_cnt_ = 0LL;
  const char *cur_map_;
  EntitySet *entities_;
  char *background_pic_;
  bool in_game_;
  int32_t frame_rate_ = 60;
  std::unordered_map<Qt::Key, std::string> key_command_map_;
  std::unordered_map<std::string, bool> command_state_;
};

bool Collide(const Entity &en1, const Entity &en2);

#endif  // MY_IWANNA_SRC_GAME_GAME_H_
