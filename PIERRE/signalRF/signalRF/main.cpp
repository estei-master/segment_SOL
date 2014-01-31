#include <QApplication>
#include "signalrf.h"

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   signalRF s;
   s.resize(200, 150);
   s.show();

   return app.exec();
}
