#include "mainwindow.h"

#include <math.h>

#include "./ui_mainwindow.h"

enum previous_symbol { num, op, dot, open_brace, close_brace, x_num };

int prev_sym = -1;
int dot_in_num = 0;
int count_close_braces = 0;
int count_open_braces = 0;
double x_value = 0.0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(num_button()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(x_button()));
  connect(ui->pushButton_OB, SIGNAL(clicked()), this,
          SLOT(open_brace_button()));
  connect(ui->pushButton_CB, SIGNAL(clicked()), this,
          SLOT(close_brace_button()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operator_button()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(operator_button()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(operator_button()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operator_button()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operator_button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operator_button()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot_button()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_RES, SIGNAL(clicked()), this, SLOT(equal_button()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph_button()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update() {
  QPushButton *button = (QPushButton *)sender();
  if (prev_sym == -1 || ui->label->text().endsWith("nan") ||
      ui->label->text().endsWith("inf")) {
    ui->label->setText(button->text());
  } else {
    ui->label->setText(ui->label->text() + button->text());
  }
}

void MainWindow::x_button() {
  if (prev_sym == open_brace || prev_sym == op || prev_sym == -1) {
    update();
    prev_sym = x_num;
  }
}

void MainWindow::clear() {
  ui->label->setText("0");
  prev_sym = -1;
  dot_in_num = 0;
  count_close_braces = 0;
  count_open_braces = 0;
}

void MainWindow::num_button() {
  if (prev_sym != close_brace) {
    update();
    prev_sym = num;
  }
}

void MainWindow::operator_button() {
  QPushButton *button = (QPushButton *)sender();
  if ((prev_sym == num || prev_sym == close_brace || prev_sym == x_num ||
       prev_sym == -1 ||
       (prev_sym == open_brace &&
        (button->text() == "+" || button->text() == "-"))) &&
      !ui->label->text().endsWith("nan") &&
      !ui->label->text().endsWith("inf")) {
    ui->label->setText(ui->label->text() + button->text());
    dot_in_num = 0;
    prev_sym = op;
  }
}

void MainWindow::func_button() {
  if (prev_sym == op || prev_sym == open_brace || prev_sym == -1) {
    update();
    ui->label->setText(ui->label->text() + "(");
    dot_in_num = 0;
    prev_sym = open_brace;
    ++count_open_braces;
  }
}

void MainWindow::dot_button() {
  if ((prev_sym == num && dot_in_num == 0) || prev_sym == -1) {
    ui->label->setText(ui->label->text() + ".");
    dot_in_num = 1;
    prev_sym = dot;
  }
}

void MainWindow::open_brace_button() {
  if (prev_sym == -1 || prev_sym == open_brace || prev_sym == op) {
    update();
    prev_sym = open_brace;
    dot_in_num = 0;
    ++count_open_braces;
  }
}

void MainWindow::close_brace_button() {
  if ((prev_sym == num || prev_sym == close_brace || prev_sym == x_num) &&
      (count_open_braces != count_close_braces)) {
    update();
    prev_sym = close_brace;
    dot_in_num = 0;
    ++count_close_braces;
  }
}

void MainWindow::equal_button() {
  if (ui->label->text().size() != 0) {
    if (prev_sym == num || prev_sym == close_brace || prev_sym == x_num) {
      double res = 0.0;
      x_value = 0.0;
//      if (ui->Xline->text().size() != 0) x_value = ui->Xline->text().toDouble();
//      QString qstring = ui->label->text();
//      char *str = new char(qstring.length());
//      QByteArray barr = qstring.toLatin1();
//      strlcpy(str, barr, qstring.length() + 1);
      QString needle = ui->label->text();
      QByteArray ba_x = needle.toLocal8Bit();
      char *str = ba_x.data();

      int error = MainCalc(str, &res, x_value);
      delete (str);
      if (error) {
        QMessageBox::about(this, "Invalid expression", "Invalid input");
      } else {
        QString valueAsString = QString::number(res, 'g', 15);
        ui->label->setText(valueAsString);
      }
//      if (res == 0) prev_sym = -1;
//      if (res != (int)res) dot_in_num = 1;
    } else {
      QMessageBox::about(this, "Invalid expression", "Invalid input");
    }
  }
}

void MainWindow::graph_button() {
  ui->widget->clearGraphs();
  if (ui->label->text() != "nan" && ui->label->text() != "inf") {
    double x_begin = ui->line_x_begin->text().toDouble();
    double x_end = ui->line_x_end->text().toDouble();
    double y_begin = ui->line_y_begin->text().toDouble();
    double y_end = ui->line_y_end->text().toDouble();

    ui->widget->xAxis->setRange(x_begin, x_end);
    ui->widget->yAxis->setRange(y_begin, y_end);
    h = 0.1;
    double Y = 0.0;
    char *str = new char(ui->label->text().length());
    QByteArray byte_arr = ui->label->text().toLatin1();
    strlcpy(str, byte_arr, ui->label->text().length() + 1);
    int error = OK;
    for (double X_ = x_begin; X_ < x_end && !error; X_ += h) {
      error = MainCalc(str, &Y, X_);
      x.push_back(X_);
      y.push_back(Y);
    }
    if (error) QMessageBox::about(this, "Invalid expression", "Invalid input");
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  } else {
    QMessageBox::about(this, "Invalid expression", "Invalid input");
  }
  x.clear();
  y.clear();
}
