#include "mainwindow.h"

#include <math.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      x_doubleValidator(-1000000, 1000000, 15, this),
      num_doubleValidator(0, 1000000000000, 2, this),
      intValidator(0, 10000) {
  ui->setupUi(this);
  set_validators();
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
  connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(backspace_button()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(loan_button()));
}

void MainWindow::set_validators() {
  QLocale locale(QLocale::C);
  locale.setNumberOptions(QLocale::RejectGroupSeparator);
  x_doubleValidator.setLocale(locale);
  x_doubleValidator.setNotation(QDoubleValidator::StandardNotation);

  num_doubleValidator.setLocale(locale);
  num_doubleValidator.setNotation(QDoubleValidator::StandardNotation);

  ui->Xline->setValidator(&x_doubleValidator);
  ui->line_x_begin->setValidator(&x_doubleValidator);
  ui->line_y_begin->setValidator(&x_doubleValidator);
  ui->line_x_end->setValidator(&x_doubleValidator);
  ui->line_y_end->setValidator(&x_doubleValidator);

  ui->term_line->setValidator(&intValidator);
  ui->percent_line->setValidator(&num_doubleValidator);
  ui->sum_line->setValidator(&num_doubleValidator);
}

void MainWindow::loan_button() {
  QString term_text = ui->term_line->text();
  QString percent_text = ui->percent_line->text();
  QString sum_text = ui->sum_line->text();

  if (!(term_text.isEmpty() && percent_text.isEmpty() && sum_text.isEmpty())) {
    double amount = sum_text.toDouble();
    double percentage = percent_text.toDouble();
    double period = term_text.toDouble();

    double payment = 0;
    double total_sum = 0;
    double sum_interest = amount;
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    QString str_first_month_pay;
    QString month_pay;
    if (ui->cBox_type->currentText() == "????????????????????????????????????") {
      for (int i = 1; i <= period; i++) {
        payment = amount / period + sum_interest * percentage / 12.0 / 100;
        total_sum += payment;
        sum_interest = amount - i * amount / period;
        month_pay = QString("%L1").arg(payment, 0, 'f', 2);
        if (i == 1) {
          str_first_month_pay = month_pay;
        }
        month_pay = str_first_month_pay + " - " + month_pay;
      }
    } else {
      double prStavka = percentage / 12 / 100;
      payment = amount * (prStavka * pow(1 + prStavka, period) /
                          (pow(1 + prStavka, period) - 1));
      total_sum = payment * period;
      month_pay = QString("%L1").arg(payment, 0, 'f', 2);
    }
    ui->label_monpay->setText(month_pay);

    double overpayment = total_sum - amount;

    ui->label_paysum->setText(QString("%L1").arg(total_sum, 0, 'f', 2));
    ui->label_overpay->setText(QString("%L1").arg(overpayment, 0, 'f', 2));
  } else {
    QMessageBox::critical(this, "Invalid expression",
                          "Fields should not be empty");
  }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_0)
    ui->pushButton_0->click();
  else if (e->key() == Qt::Key_1)
    ui->pushButton_1->click();
  else if (e->key() == Qt::Key_2)
    ui->pushButton_2->click();
  else if (e->key() == Qt::Key_3)
    ui->pushButton_3->click();
  else if (e->key() == Qt::Key_4)
    ui->pushButton_4->click();
  else if (e->key() == Qt::Key_5)
    ui->pushButton_5->click();
  else if (e->key() == Qt::Key_6)
    ui->pushButton_6->click();
  else if (e->key() == Qt::Key_7)
    ui->pushButton_7->click();
  else if (e->key() == Qt::Key_8)
    ui->pushButton_8->click();
  else if (e->key() == Qt::Key_9)
    ui->pushButton_9->click();
  else if (e->key() == Qt::Key_Minus)
    ui->pushButton_min->click();
  else if (e->key() == Qt::Key_Plus)
    ui->pushButton_plus->click();
  else if (e->key() == Qt::Key_Slash)
    ui->pushButton_div->click();
  else if (e->key() == Qt::Key_Asterisk)
    ui->pushButton_mul->click();
  else if (e->key() == Qt::Key_Equal)
    ui->pushButton_RES->click();
  else if (e->key() == Qt::Key_ParenLeft)
    ui->pushButton_OB->click();
  else if (e->key() == Qt::Key_ParenRight)
    ui->pushButton_CB->click();
  else if (e->key() == Qt::Key_AsciiCircum)
    ui->pushButton_pow->click();
  else if (e->key() == Qt::Key_Backspace)
    ui->pushButton_C->click();
  else if (e->key() == Qt::Key_Period)
    ui->pushButton_dot->click();
  else if (e->key() == Qt::Key_Return)
    ui->pushButton_RES->click();
}

void MainWindow::backspace_button() {
  QString text = ui->label->text();
  text.chop(1);
  ui->label->setText(text);
  change_prev_sym();
}

void MainWindow::change_prev_sym() {
  QString str = ui->label->text();
  if (str.size() != 0) {
    prev_sym_int = ui->label->text()[ui->label->text().size() - 1].unicode();
    switch (prev_sym_int) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        prev_sym = num;
        break;
      case 'n':
      case 't':
      case 's':
      case 'g':
      case '(':
        prev_sym = open_brace;
        break;
      case 'x':
        prev_sym = x_num;
        break;
      case '+':
      case '-':
      case '*':
      case '/':
        prev_sym = op;
        break;
      case 'd':
        if (ui->label->text().endsWith("mod"))
          prev_sym = op;
        else
          prev_sym = open_brace;
        break;
      case '.':
        prev_sym = dot;
        break;
      case ')':
        prev_sym = close_brace;
      default:
        break;
    }
  } else {
    prev_sym = -1;
    ui->label->setText("0");
  }
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
  QString expression = ui->label->text();
  if (expression.size() != 0 && expression.size() <= 255 &&
      !expression.contains("e")) {
    if (prev_sym == num || prev_sym == close_brace || prev_sym == x_num) {
      double res = 0.0;
      x_value = 0.0;
      if (expression.size() != 0) x_value = ui->Xline->text().toDouble();
      QByteArray ba_x = expression.toLocal8Bit();
      char *str = ba_x.data();

      int error = MainCalc(str, &res, x_value);
      if (error) {
        QMessageBox::about(this, "Invalid expression", "Invalid input");
        ui->label->setText("0");
      } else {
        QString valueAsString = QString::number(res, 'g', 15);
        ui->label->setText(valueAsString);
      }
      if (res == 0) prev_sym = -1;
      if (res != (int)res) dot_in_num = 1;
    } else {
      QMessageBox::about(this, "Invalid expression", "Invalid input");
      ui->label->setText("0");
    }
  } else {
    QMessageBox::about(this, "Invalid expression", "Invalid input");
    ui->label->setText("0");
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
    QString needle = ui->label->text();
    QByteArray ba_x = needle.toLocal8Bit();
    char *str = ba_x.data();

    int error = OK;
    for (double X_ = x_begin; X_ < x_end && !error; X_ += h) {
      error = MainCalc(str, &Y, X_);
      x.push_back(X_);
      y.push_back(Y);
    }
    if (error) {
      QMessageBox::about(this, "Invalid expression", "Invalid input");
      ui->label->setText("0");
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  } else {
    QMessageBox::about(this, "Invalid expression", "Invalid input");
  }
  x.clear();
  y.clear();
}
