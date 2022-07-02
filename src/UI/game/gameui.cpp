#include "UI/game/gameui.h"

#include <QBrush>
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <QPainter>
#include <QPixmap>

#include "ui_gameui.h"

GameUI::GameUI(QWidget *parent) : QWidget(parent), ui(new Ui::GameUI), timer_(new QTimer(this)) {
  ui->setupUi(this);
  connect(timer_, &QTimer::timeout, [&]() {
    if (game_.InGame()) {
      game_.Step();
      emit UpdateInfo(time_.nsecsElapsed(), game_.DeathCount(), game_.PlayTime());
      time_.restart();
    }
    update();
  });
  timer_->setTimerType(Qt::PreciseTimer);

  // debug
  //  QLabel *l1 = new QLabel(this);
  //  QMovie *movie1 = new QMovie(this);
  //  movie1->setFileName(":/hero/eastIdle.gif");
  //  l1->setMovie(movie1);
  //  movie1->start();
  //  l1->move(100, 100);
  //  QLabel *l2 = new QLabel(this);
  //  QMovie *movie2 = new QMovie(this);
  //  movie2->setFileName(":/hero/eastMoving.gif");
  //  l2->setMovie(movie2);
  //  movie2->start();
  //  l2->move(150, 100);
  //  QLabel *l3 = new QLabel(this);
  //  QMovie *movie3 = new QMovie(this);
  //  movie3->setFileName(":/hero/westIdle.gif");
  //  l3->setMovie(movie3);
  //  movie3->start();
  //  l3->move(200, 100);
  //  QLabel *l4 = new QLabel(this);
  //  QMovie *movie4 = new QMovie(this);
  //  movie4->setFileName(":/hero/westMoving.gif");
  //  l4->setMovie(movie4);
  //  movie4->start();
  //  l4->move(250, 100);
}

void GameUI::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPixmap pixmap;
  QBrush brush;

  if (game_.InGame()) {
    for (const auto &entity : game_.GetEntitySet()) {
      bool ret = pixmap.load(":/hero/westMoving.gif");
      if (!ret) {
        // qDebug() << "图片加载失败： " << entity->GetCurPic();
      }
      // painter.drawPixmap(entity->GetX(), entity->GetY(), pixmap);
      painter.drawTiledPixmap(entity->GetX(), entity->GetY(), pixmap.width(), pixmap.height(), pixmap);
    }
  } else {
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    painter.setBrush(brush);
    painter.setPen(Qt::red);
    painter.drawRect(0, 0, 799, 599);
  }
}

GameUI::~GameUI() { delete ui; }

int32_t GameUI::Load(const char *file_name) {
  auto ret = game_.Load(file_name);
  timer_->setInterval(1000 / game_.GetFrameRate());
  timer_->start();
  return ret;
}
void GameUI::Stop() {
  timer_->stop();
  // game_.CloseMap();
}
void GameUI::Pause() { timer_->stop(); }
void GameUI::Continue() { timer_->start(); }
void GameUI::SendKey(QKeyEvent *event, bool is_pressed) {
  auto key = event->key();
  game_.Event(static_cast<Qt::Key>(key), is_pressed);
}
