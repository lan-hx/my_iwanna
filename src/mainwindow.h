#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>

#include "UI/game/gameui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QLabel *death_count_;
  QLabel *play_time_;
  QLabel *debug_output_;
  QLabel *fps_;
  QLabel *frame_latency_;
  GameUI *game_ui_;

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 signals:
  void Pause();
  void SendKey(QKeyEvent *event, bool is_pressed);
};

#endif  // MAINWINDOW_H
