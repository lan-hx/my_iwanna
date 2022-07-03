#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>

#include "UI/about/about.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // status bar
  play_time_ = new QLabel(this);
  ui->statusbar->addWidget(play_time_);
  death_count_ = new QLabel(this);
  ui->statusbar->addWidget(death_count_);
  debug_output_ = new QLabel(this);
  ui->statusbar->addWidget(debug_output_);
  fps_ = new QLabel(this);
  fps_->setFixedWidth(80);
  ui->statusbar->addPermanentWidget(fps_);
  frame_latency_ = new QLabel(this);
  frame_latency_->setFixedWidth(120);
  ui->statusbar->addPermanentWidget(frame_latency_);

  game_ui_ = new GameUI(this);
  setCentralWidget(game_ui_);
  game_ui_->setFixedSize(800, 600);
  adjustSize();

  connect(game_ui_, &GameUI::UpdateInfo,
          [&](int64_t nsec, int32_t death_count, double play_time, const char *debug_info) {
            play_time_->setText(QString("played time: %1s").arg(QString::number(play_time, 'f', 0)));
            death_count_->setText("death count: " + QString::number(death_count));
            debug_output_->setText(debug_info);
            fps_->setText("FPS: " + QString::number(1e9 / nsec, 'f', 2));
            frame_latency_->setText("latency: " + QString::number(nsec / 1e6, 'f', 2) + "ms");
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
    game_ui_->Pause();
    auto file_name = QFileDialog::getOpenFileName(this, "打开地图", "", "");
    if (game_ui_->Load(file_name.toUtf8()) != 0) {
      QMessageBox::warning(this, "打开失败", "打开地图失败");
    }
    game_ui_->Continue();
  });
  connect(ui->actionexit, &QAction::triggered, [&]() { close(); });
  connect(this, &MainWindow::SendKey, game_ui_, &GameUI::SendKey);
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::keyPressEvent(QKeyEvent *event) {
  auto key = event->key();
  switch (key) {
    case Qt::Key_P:
      emit Pause();
      break;
    default:
      emit SendKey(event, true);
  }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  auto key = event->key();
  switch (key) {
    default:
      emit SendKey(event, false);
  }
}
