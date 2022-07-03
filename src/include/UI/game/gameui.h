#ifndef GAMEUI_H
#define GAMEUI_H

#include <QElapsedTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <cstdint>
#include <unordered_map>

#include "game/Game.h"

namespace Ui {  // NOLINT
class GameUI;
}

class GameUI : public QWidget {
  Q_OBJECT

 public:
  explicit GameUI(QWidget *parent = nullptr);
  ~GameUI() override;
  int32_t Load(const char *file_name);
  void Stop();
  void Pause();
  void Continue();
  void SendKey(QKeyEvent *event, bool is_pressed);

 private:
  Ui::GameUI *ui;  // NOLINT
  Game game_;
  QTimer *timer_;
  QElapsedTimer time_;
  int64_t elasped_time_nsec_;
  int32_t timer_time_;
  std::unordered_map<int32_t, QLabel *> gifs_;

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void UpdateInfo(int64_t nsec, int32_t death_count, double play_time, const char *debug_info);  // NOLINT
};

#endif  // GAMEUI_H
