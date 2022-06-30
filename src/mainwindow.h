#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  QLabel *fps_;
  QLabel *frame_lag_;
  GameUI *game_ui_;

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 signals:
  void Pause();
};

#endif  // MAINWINDOW_H
