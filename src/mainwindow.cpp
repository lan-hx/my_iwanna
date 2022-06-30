#include "mainwindow.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "UI/about/about.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // status bar
  play_time_ = new QLabel(this);
  ui->statusbar->addWidget(play_time_);
  death_count_ = new QLabel(this);
  ui->statusbar->addWidget(death_count_);
  fps_ = new QLabel(this);
  fps_->setFixedWidth(80);
  ui->statusbar->addPermanentWidget(fps_);
  frame_lag_ = new QLabel(this);
  frame_lag_->setFixedWidth(80);
  ui->statusbar->addPermanentWidget(frame_lag_);

  game_ui_ = new GameUI(this);
  setCentralWidget(game_ui_);
  game_ui_->setFixedSize(800, 600);
  adjustSize();

  connect(game_ui_, &GameUI::UpdateInfo, [&](int64_t nsec, int32_t death_count, double play_time) {
    play_time_->setText("played time: " + QString::number(play_time));
    death_count_->setText("death count: " + QString::number(death_count));
    fps_->setText("FPS: " + QString::number(1e9 / nsec, 'g', 4));
    frame_lag_->setText("lag: " + QString::number(nsec / 1e6, 'g', 4) + "ms");
  });

  // connect
  connect(this, &MainWindow::Pause, [&]() {
    game_ui_->Pause();
    QMessageBox::about(this, "暂停", "游戏已暂停，按OK返回");
    game_ui_->Continue();
  });
  connect(ui->actionproject_info, &QAction::triggered, [&]() {
    game_ui_->Pause();
    About ab(this);
    ab.exec();
    game_ui_->Continue();
  });
  connect(ui->actionauthor, &QAction::triggered, [&]() {});
  connect(ui->actionpause, &QAction::triggered, [&]() { emit Pause(); });
  connect(ui->actionstop, &QAction::triggered, [&]() { game_ui_->Stop(); });
  connect(ui->actionopen, &QAction::triggered, [&]() {
    auto file_name = QFileDialog::getOpenFileName(this, "打开地图", "", ".map");
    game_ui_->Load(file_name.toUtf8());
  });
  connect(ui->actionexit, &QAction::triggered, [&]() { close(); });

  // key event
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::keyPressEvent(QKeyEvent *event) {
  auto key = event->key();
  switch (key) {
    case Qt::Key_P:
      emit Pause();
      break;
    default:;
  }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  auto key = event->key();
  switch (key) { default:; }
}
