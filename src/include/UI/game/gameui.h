#ifndef GAMEUI_H
#define GAMEUI_H

#include <QElapsedTimer>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>
#include <cstdint>

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

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void UpdateInfo(int64_t nsec, int32_t death_count, double play_time);  // NOLINT
};

#endif  // GAMEUI_H
