#ifndef GAMEUI_H
#define GAMEUI_H

#include <QElapsedTimer>
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
  inline int32_t Load(const char *file_name) { return 0; }
  inline void Stop() {}
  void Pause();
  void Continue();

 private:
  Ui::GameUI *ui;  // NOLINT
  Game game_;
  QTimer *timer_;
  QElapsedTimer time_;
  int64_t elasped_time_nsec_;

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void UpdateInfo(int64_t nsec, int32_t death_count, double play_time);  // NOLINT
};

#endif  // GAMEUI_H
