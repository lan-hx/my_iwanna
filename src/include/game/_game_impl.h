//
// Created by lan on 2022/7/4.
//

#ifndef MY_IWANNA_SRC_GAME__GAME_IMPL_H_
#define MY_IWANNA_SRC_GAME__GAME_IMPL_H_

#include <Qt>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "entity/Entity.h"
#include "entityset/EntitySet.h"
#include "game/Game.h"

class _game_impl {
 public:
  explicit _game_impl();
  int32_t Load(const char *file_name);
  void Reset();
  int32_t ResetAndLoad(const char *file);
  void Event(const Qt::Key &key, bool is_pressed);
  void Step();
  void CloseMap();
  bool MapLoaded();
  inline bool InGame() const { return in_game_; }
  inline int32_t GetFrameRate() const { return frame_rate_; }
  void SetFrameRate(int32_t);
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const;
  inline bool IsDead() const { return dead_; }
  inline int32_t DeathCount() const { return death_cnt_; }
  inline double PlayTime() const { return static_cast<double>(step_cnt_) / static_cast<double>(frame_rate_); }
  const char *GetDebugOutput();
  Player *GetPlayer() { return entities_->GetPlayer(); }

 private:
  bool dead_ = false;
  int32_t death_cnt_ = 0;
  int64_t step_cnt_ = 0LL;
  EntitySet *entities_;
  std::string background_pic_;
  bool in_game_ = false;
  int32_t frame_rate_ = 60;
  std::unordered_map<Qt::Key, std::string> key_command_map_;
  std::unordered_map<std::string, int32_t> command_state_;
};

int32_t Collide(const Entity &en1, const Entity &en2);

#endif  // MY_IWANNA_SRC_GAME__GAME_IMPL_H_
