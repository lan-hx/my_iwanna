#include <QApplication>

#include "mainwindow.h"
#include "map_generator/map_generator.h"

int main(int argc, char *argv[]) {
  GenerateTestMap();
  QApplication a(argc, argv);
  MainWindow window;
  window.show();
  return a.exec();  // NOLINT
}
