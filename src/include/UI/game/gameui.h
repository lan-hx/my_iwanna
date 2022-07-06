#ifndef GAMEUI_H
#define GAMEUI_H

#include <QElapsedTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QSoundEffect>
#include <QTimer>
#include <QWidget>
#include <cstdint>
#include <unordered_map>

#include "game/ViewModel.h"

namespace Ui {  // NOLINT
class GameUI;
}

class GameUI : public QWidget {
  Q_OBJECT

 public:
  explicit GameUI(QWidget *parent = nullptr);
  ~GameUI() override;
  void Load(const char *file_name);
  void Stop();
  void Pause();
  void Continue();
  void SendKey(QKeyEvent *event, bool is_pressed);
  void Restart();
  void UpdateMovies();
  void UpdateInfoFromGame(int32_t death_count, double play_time, const char *debug_info);
  void AfterLoad(int32_t ret);
  void DieHandle();

 private:
  Ui::GameUI *ui;  // NOLINT
  ViewModel view_model_;
  QTimer *timer_;
  QElapsedTimer time_;
  int64_t elasped_time_nsec_;
  int32_t timer_time_;
  std::unordered_map<int32_t, QLabel *> gifs_;
  QLabel *death_cover_;
  QSoundEffect *bgm_;
  QSoundEffect *death_sound_;
  QSoundEffect *sound_;

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void UpdateInfo(int64_t nsec, int32_t death_count, double play_time, const char *debug_info);  // NOLINT
  void LoadSignal(const char *file_name);
  void RestartSignal();
  void KeyEventSignal(const Qt::Key &key, bool is_pressed);
  void StepSignal();
  void CloseMapSignal();
  void LoadResult(int32_t ret);
};

#endif  // GAMEUI_H
