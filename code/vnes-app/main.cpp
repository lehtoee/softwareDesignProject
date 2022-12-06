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
 * - Time funktio observation vs forecast
 * - Connecti controllerin ja networkhandlerin väliin jotta saadaan data sinne
- The user must be able to request calculations and visualization on average daily
temperature at certain location in certain month
- The user must be able to request calculations and visualization on maximum and
minimum daily temperature at certain location in certain month
 *
 *
 * Niklas:
 * - Monthly averages weather datan datatyypiks, disablee timeline valinnan (aina 30 pvä)
 * - avg temp / day, max temp / day, min temp / day
 *
 * Eemil:
 * - Connecti controllerin ja networkhandlerin väliin jotta saadaan data sinne
 * - Parserin siirto
 *
 * Saha?
 *
 * Yleistä:
 * - Frontin ja backendin yhdistäminen
 * - Datan tallennus / kuvaajan tallennus
 *
 *
- Combine weather information (from FMI) and road maintenance information from a
selected location and time interval into one window.
- Combine weather information (from FMI) and road condition forecast information from
a selected location and time interval into one window.
 *
 * */
