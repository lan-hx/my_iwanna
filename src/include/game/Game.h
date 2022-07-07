//
// Created by lan on 2022/7/4.
//

#ifndef MY_IWANNA_SRC_GAME__GAME_IMPL_H_
#define MY_IWANNA_SRC_GAME__GAME_IMPL_H_

#include <QObject>
#include <Qt>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "entity/Entity.h"
#include "entityset/EntitySet.h"
#include "game/ViewModel.h"

class Game : public QObject {
  Q_OBJECT

 public:
  explicit Game();
  void Load(const char *file_name);
  void Restart();
  void Event(const Qt::Key &key, bool is_pressed);
  void Step();
  void CloseMap();
  bool MapLoaded();
  inline bool InGame() const { return in_game_; }
  inline int32_t GetFrameRate() const { return frame_rate_; }
  void SetFrameRate(int32_t);
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const { return background_pic_.empty() ? nullptr : background_pic_.c_str(); }
  inline bool IsDead() const { return dead_; }
  inline int32_t DeathCount() const { return death_cnt_; }
  inline double PlayTime() const { return static_cast<double>(step_cnt_) / static_cast<double>(frame_rate_); }
  const char *GetDebugOutput();
  Player *GetPlayer() { return entities_->GetPlayer(); }

 private:
  void Die();
  void Save(const int32_t &resurrection_index);
  void Init();
  void ChangeMap(const char *file_name);

  bool dead_ = false;
  int32_t death_cnt_ = 0;
  int64_t step_cnt_ = 0LL;
  std::string cur_map_;
  std::string left_map_;
  std::string right_map_;
  std::string up_map_;
  std::string down_map_;
  int32_t cur_resurrection_;
  EntitySet *entities_;
  std::string background_pic_;
  bool in_game_ = false;
  int32_t frame_rate_ = 60;
  std::unordered_map<Qt::Key, std::string> key_command_map_;
  std::unordered_map<std::string, int32_t> command_state_;

 signals:
  void LoadedCallBack(int32_t ret);
  void StepCallBack();
  void DieSignal();
  void UpdateInfo(int32_t death_count, double play_time, const char *debug_info);
  void UpdateFrame();
};

int32_t Collide(const Entity &en1, const Entity &en2);

#endif  // MY_IWANNA_SRC_GAME__GAME_IMPL_H_
