#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkHandler* networkhandler(new NetworkHandler);
    Controller* controller(new Controller(networkhandler));
    MainWindow* view(new MainWindow(controller));
    view->show();
    return a.exec();
}
