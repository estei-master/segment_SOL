#include <QApplication>
#include "batterie.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    batterie b;
    b.show();

    return app.exec();
}
