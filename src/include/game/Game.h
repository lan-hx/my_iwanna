//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_GAME_GAME_H_
#define MY_IWANNA_SRC_GAME_GAME_H_

#include <Qt>
#include <cstdint>

class _game_impl;
class Entity;

class Game {
 public:
  explicit Game();
  ~Game();
  int32_t Load(const char *file_name);
  void Reset();
  void Event(const Qt::Key &key, bool is_pressed);
  void Step();
  void CloseMap();
  bool InGame() const;
  int32_t GetFrameRate();
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const;
  bool IsDead() const;
  int32_t DeathCount();
  double PlayTime() const;
  const char *GetDebugOutput();
  Entity *GetPlayer();

 private:
  _game_impl *game_impl_;
};

#endif  // MY_IWANNA_SRC_GAME_GAME_H_
