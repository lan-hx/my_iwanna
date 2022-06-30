#include "UI/game/gameui.h"

#include <QBrush>
#include <QPainter>
#include <QPixmap>

#include "ui_gameui.h"

GameUI::GameUI(QWidget *parent) : QWidget(parent), ui(new Ui::GameUI), timer_(new QTimer(this)) {
  ui->setupUi(this);
  connect(timer_, &QTimer::timeout, [&]() {
    //    game_.Step();
    update();
    emit UpdateInfo(time_.nsecsElapsed(), 0, 0.0);
    time_.restart();
  });
  timer_->start(static_cast<int>(16));
}

void GameUI::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPixmap pixmap;
  QBrush brush;

  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::cyan);
  painter.setBrush(brush);
  painter.setPen(Qt::red);
  painter.drawRect(0, 0, 799, 599);

  pixmap.load(":/kid/caper.png");
  painter.drawPixmap(100, 300, pixmap);
  pixmap.load(":/kid/run1.png");
  painter.drawPixmap(150, 300, pixmap);
  pixmap.load(":/kid/run2.png");
  painter.drawPixmap(200, 300, pixmap);
  pixmap.load(":/kid/stand1.png");
  painter.drawPixmap(250, 300, pixmap);
  pixmap.load(":/kid/stand2.png");
  painter.drawPixmap(300, 300, pixmap);
  pixmap.load(":/kid/whereabouts.png");
  painter.drawPixmap(350, 300, pixmap);
  pixmap.load(":/barrier/apple.png");
  painter.drawPixmap(100, 400, pixmap);
  pixmap.load(":/barrier/Archive_point_off.png");
  painter.drawPixmap(150, 400, pixmap);
  pixmap.load(":/barrier/Archive_point_on.png");
  painter.drawPixmap(200, 400, pixmap);
  pixmap.load(":/barrier/door.png");
  painter.drawPixmap(250, 400, pixmap);
  pixmap.load(":/barrier/grassland.png");
  painter.drawPixmap(300, 400, pixmap);
  pixmap.load(":/barrier/land.png");
  painter.drawPixmap(350, 400, pixmap);
  pixmap.load(":/barrier/Spikes.png");
  painter.drawPixmap(400, 400, pixmap);
  pixmap.load(":/Game_over.png");
  painter.drawPixmap(100, 50, pixmap);
}

GameUI::~GameUI() { delete ui; }

void GameUI::Pause() { timer_->stop(); }
void GameUI::Continue() { timer_->start(static_cast<int>(16)); }
