#include <iostream>
#include <apicalls.hh>
#include <QApplication>
#include <mainwindow.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
