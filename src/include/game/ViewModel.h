//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_GAME_VIEWMODEL_H_
#define MY_IWANNA_SRC_GAME_VIEWMODEL_H_

#include <QObject>
#include <Qt>
#include <cstdint>
#include <vector>

class Game;
class Entity;
class GameUI;

class ViewModel : public QObject {
  Q_OBJECT

 public:
  explicit ViewModel(QObject *parent, GameUI *game_ui);
  ~ViewModel() override;
  // int32_t Load(const char *file_name);
  // void Restart();
  // void Event(const Qt::Key &key, bool is_pressed);
  // void Step();
  // void CloseMap();
  bool InGame() const;
  int32_t GetFrameRate();
  std::vector<Entity *> GetEntitySet() const;
  const char *GetBackgroundPic() const;
  bool IsDead() const;
  // int32_t DeathCount();
  // double PlayTime() const;
  // const char *GetDebugOutput();
  Entity *GetPlayer();

 private:
  Game *game_impl_;
  GameUI *game_ui_;
};

#endif  // MY_IWANNA_SRC_GAME_VIEWMODEL_H_
