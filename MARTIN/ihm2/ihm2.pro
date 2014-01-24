#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T15:30:09
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ihm2
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv \
                         /usr/local/include/opencv2 \
                         /usr/local/include/opencv2/core

LIBS += -L/opt/local/lib -lopencv_core -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_imgproc


SOURCES += main.cpp\
        mainwindow.cpp \
        camerawidget.cpp \
        nunchuck.cpp \
        qattitudeindicator.cpp \
        lightmaps.cpp \
        slippymap.cpp \
        mydisplay.cpp \
        battery.cpp \
    qbase.cpp \
    uart.cpp \
    zigbee.cpp

HEADERS  += mainwindow.h \
        camerawidget.h \
        nunchuck.h \
        qattitudeindicator.h \
        lightmaps.h \
        slippymap.h \
        mydisplay.h \
        librairie.h \
        battery.h \
    zigbee.h \
    qbase.h \
    typdefUart.h \
    uart.h

FORMS    += mainwindow.ui

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++11

RESOURCES +=
