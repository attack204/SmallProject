#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_btnAdd_clicked();
    void on_btnDec_clicked();
    void on_btnMul_clicked();
    void on_btnDiv_clicked();
    void on_btnCalc_clicked();
    void on_btnCalcTwo_clicked();

private:
    Ui::MainWindow *ui;
    int whichMode;
    //1 add
    //2 dec
    //3 mul
    //4 div
};

#endif // MAINWINDOW_H
