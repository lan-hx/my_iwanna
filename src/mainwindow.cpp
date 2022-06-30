#include "mainwindow.h"

#include <QLabel>

#include "UI/about/about.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // status bar
  QLabel *fps = new QLabel("FPS: 0", this);
  ui->statusbar->addPermanentWidget(fps);

  // connect
  connect(ui->project_info, &QAction::triggered, this, [&]() {
    About ab(this);
    ab.exec();
  });
}

MainWindow::~MainWindow() { delete ui; }
