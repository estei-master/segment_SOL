#include <QApplication>
#include "mainwindow.h"


/*  Modifs : Bouton start/stop Video actif
 *
 */
int main(int argc, char **argv) {

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    int retval = app.exec();
    return retval;
}
