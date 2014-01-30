#include "qth_base.h"

/*  Thread multi usage =)
 *
 *  L'idée : Construire les threads à partir du même modèle
 *           avec un paramètre indiquant le son comportement.
 *
 *  Tu en fera bien ce que tu en veux
 */
QTh_Base::QTh_Base(int type, QObject *parent) :
    QThread(parent)
{
    typeThread = type;

    switch(typeThread) {

    case QTHREAD_HORIZON:
        attInd = new qAttitudeIndicator();
        break;

    default:
        break;
    }
}

void QTh_Base::run()
{
//    switch(typeThread) {
//    case QTHREAD_HORIZON:
//        break;
//    default:
//        break;
//    }

    while (1) {
        switch(typeThread) {

        case QTHREAD_HORIZON:
            attInd->doHorizon();
            break;

        default:
            break;
        }
        msleep(50);
    }
}
