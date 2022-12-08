#include "mainwindow.h"
#include "networkhandler.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkHandler* networkhandler(new NetworkHandler);
    MainWindow* view(new MainWindow);
    Controller* controller(new Controller(networkhandler, view));
    view->show();
    return a.exec();
};


/* TODO
 * Veikka:
 *
 *
 * Niklas:

 *
 * Eemil:

 *
 * Saha?
 *
 * Yleistä:
 *  -siivousta + dokumentaatiota
 *  -Trafficmessages fronttiin
 *
 * */
