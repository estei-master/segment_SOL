#ifndef MAPZOOM_H
#define MAPZOOM_H

#include <QMainWindow>

class QNetworkSession;
class LightMaps;
class SlippyMap;

class MapZoom : public QMainWindow
{
    Q_OBJECT

public:
    MapZoom();
    qreal latitude, longitude;

private slots:
    void sessionOpened();
    void testGps();
    void aboutOsm();

protected:
    void timerEvent(QTimerEvent *event);
private:
    LightMaps *map;
    QNetworkSession *networkSession;
};

#endif
