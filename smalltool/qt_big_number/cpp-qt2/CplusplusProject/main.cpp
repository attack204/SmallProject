#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include<BigNumber.h>
#include <QQuickStyle>

using namespace std;
int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Material");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
