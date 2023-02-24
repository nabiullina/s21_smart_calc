#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QVector>

extern "C" {
#include "../smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int prev_sym = -1;
  int prev_sym_int = 0;
  QChar prev_sym_QChar;
  int dot_in_num = 0;
  int count_close_braces = 0;
  int count_open_braces = 0;
  double x_value = 0.0;
  enum previous_symbol { num, op, dot, open_brace, close_brace, x_num };

 private slots:
  void update();
  void clear();
  void dot_button();
  void func_button();
  void operator_button();
  void num_button();
  void open_brace_button();
  void close_brace_button();
  void x_button();
  void equal_button();
  void graph_button();
  void backspace_button();
  void change_prev_sym();
  void keyPressEvent(QKeyEvent *);
  void loan_button();
  void set_validators();

 private:
  Ui::MainWindow *ui;
  QDoubleValidator x_doubleValidator;
  QDoubleValidator num_doubleValidator;
  QIntValidator intValidator;
  double x_begin, x_end, h, x_;
  int n;

  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
