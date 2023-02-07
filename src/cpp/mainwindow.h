#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H