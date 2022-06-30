#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {  // NOLINT
class About;
}

class About : public QDialog {
  Q_OBJECT

 public:
  explicit About(QWidget *parent = nullptr);
  ~About() override;

 private:
  Ui::About *ui;  // NOLINT
};

#endif  // ABOUT_H
