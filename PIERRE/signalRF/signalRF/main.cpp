#include <QApplication>
#include "signalrf.h"

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   signalRF s;
   s.show();

   return app.exec();
}
