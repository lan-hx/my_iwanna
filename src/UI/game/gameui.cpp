#include "UI/game/gameui.h"

#include <QBrush>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QMovie>
#include <QPainter>
#include <QPixmap>

#include "entity/Entity.h"
#include "ui_gameui.h"

GameUI::GameUI(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::GameUI),
      view_model_(this, this),
      timer_(new QTimer(this)),
      death_cover_(new QLabel(this))
      bgm_(nullptr),
      sound_(nullptr) {
  ui->setupUi(this);
  setFixedSize(800, 600);
  connect(timer_, &QTimer::timeout, [&]() { emit StepSignal(); });
  timer_->setTimerType(Qt::PreciseTimer);

  // dead
  QPixmap gameover(":/misc/gameover.png");
  death_cover_->setPixmap(gameover);
  death_cover_->move((width() - gameover.width()) / 2, (height() - gameover.height()) / 2);
  death_cover_->hide();

  // music

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

void GameUI::paintEvent([[maybe_unused]] QPaintEvent *event) {
  QPainter painter(this);
  QPixmap pixmap;
  QBrush brush;

  if (view_model_.InGame()) {
    if (view_model_.GetBackgroundPic() != nullptr) {
      bool ret = pixmap.load(view_model_.GetBackgroundPic());
      if (!ret) {
        // QMessageBox::warning(this, "图片加载失败", "图片加载失败！");
      }
      painter.drawPixmap(0, 0, width(), height(), pixmap);
    } else {
      brush.setStyle(Qt::SolidPattern);
      brush.setColor(Qt::cyan);
      painter.setBrush(brush);
      painter.setPen(Qt::transparent);
      painter.drawRect(0, 0, 799, 599);
    }
    for (const auto &entity : view_model_.GetEntitySet()) {
      if (entity->GetType() == player) {
        if (gifs_.contains(entity->GetEntityId())) {
          gifs_[entity->GetEntityId()]->move(entity->GetX(), entity->GetY());
        }
      } else if (!entity->IsHidden()) {
        bool ret = pixmap.load(entity->GetCurPic());
        if (!ret) {
          QMessageBox::warning(this, "图片加载失败", "图片加载失败！");
        }
        switch (entity->GetDrawType()) {
          case tiled:
            painter.drawTiledPixmap(entity->GetX(), entity->GetY(), entity->GetWidth(), entity->GetHeight(), pixmap);
            break;
          case scaled:
            painter.drawPixmap(entity->GetX(), entity->GetY(), entity->GetWidth(), entity->GetHeight(), pixmap);
        }
      }
    }
    if (view_model_.IsDead()) {
      death_cover_->show();
    } else {
      death_cover_->hide();
    }
  } else {
    // bg
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    painter.setBrush(brush);
    painter.setPen(Qt::red);
    painter.drawRect(0, 0, 799, 599);
  }
}

GameUI::~GameUI() { delete ui; }

void GameUI::Load(const char *file_name) { emit LoadSignal(file_name); }
void GameUI::Stop() {
  timer_->stop();
  emit CloseMapSignal();
  for (auto &gif : gifs_) {
    delete gif.second;
  }
  gifs_.clear();
  delete bgm_;
  bgm_ = nullptr;
}
void GameUI::Pause() { timer_->stop(); }
void GameUI::Continue() { timer_->start(); }
void GameUI::SendKey(QKeyEvent *event, bool is_pressed) {
  auto key = event->key();
  emit KeyEventSignal(static_cast<Qt::Key>(key), is_pressed);
}
void GameUI::Restart() {
  emit RestartSignal();
  delete bgm_;
  bgm_ = new QSound("music/bgmusic1.wav", this);
  bgm_->play();
  Continue();
}
void GameUI::UpdateMovies() {
  auto entity = view_model_.GetPlayer();
  if (!gifs_.contains(entity->GetEntityId())) {
    // brand new gif
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie(label);
    movie->setFileName(entity->GetCurPic());
    label->setMovie(movie);
    movie->start();
    label->show();
    gifs_.emplace(entity->GetEntityId(), label);
  } else if (gifs_[entity->GetEntityId()]->movie()->fileName() != entity->GetCurPic()) {
    // gif changed
    delete gifs_[entity->GetEntityId()];
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie(label);
    movie->setFileName(entity->GetCurPic());
    label->setMovie(movie);
    movie->start();
    label->show();
    gifs_[entity->GetEntityId()] = label;
  }
}
void GameUI::UpdateInfoFromGame(int32_t death_count, double play_time, const char *debug_info) {
  emit UpdateInfo(time_.nsecsElapsed(), death_count, play_time, debug_info);
  time_.restart();
}

void GameUI::AfterLoad(int32_t ret) {
  timer_->setInterval(1000 / view_model_.GetFrameRate());
  timer_->start();
  delete bgm_;
  bgm_ = new QSound("music/bgmusic1.wav", this);
  bgm_->play();
  emit LoadResult(ret);
}
