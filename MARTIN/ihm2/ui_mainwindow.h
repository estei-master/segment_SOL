/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jan 30 17:04:41 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *widget_principal;
    QTabWidget *Onglet;
    QWidget *vol_immersif;
    QPushButton *VideoStreaming;
    QPushButton *emergency_stop;
    QWidget *gridLayoutWidget;
    QGridLayout *cameralayout;
    QWidget *gridLayoutWidget_4;
    QGridLayout *maplayout;
    QPushButton *Photo;
    QWidget *gridLayoutWidget_6;
    QGridLayout *batterylayout;
    QWidget *gridLayoutWidget_7;
    QGridLayout *batterylayout_2;
    QLabel *Name;
    QLabel *Name_2;
    QFrame *line_2;
    QWidget *gridLayoutWidget_9;
    QGridLayout *powerlayout4;
    QWidget *gridLayoutWidget_10;
    QGridLayout *powerlayout3;
    QWidget *gridLayoutWidget_11;
    QGridLayout *powerlayout2;
    QWidget *gridLayoutWidget_12;
    QGridLayout *powerlayout1;
    QLabel *Name_3;
    QWidget *vol_vue;
    QPushButton *emergency_stop_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *horizon_layout;
    QWidget *gridLayoutWidget_5;
    QGridLayout *maplayout2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *batterylayout2;
    QWidget *gridLayoutWidget_8;
    QGridLayout *batterylayout2_2;
    QLabel *Name2;
    QLabel *Name2_2;
    QFrame *line;
    QWidget *gridLayoutWidget_13;
    QGridLayout *powerlayout4_2;
    QWidget *gridLayoutWidget_14;
    QGridLayout *powerlayout3_2;
    QWidget *gridLayoutWidget_15;
    QGridLayout *powerlayout2_2;
    QWidget *gridLayoutWidget_16;
    QGridLayout *powerlayout1_2;
    QLabel *Name_4;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 580);
        MainWindow->setMinimumSize(QSize(966, 0));
        widget_principal = new QWidget(MainWindow);
        widget_principal->setObjectName(QString::fromUtf8("widget_principal"));
        Onglet = new QTabWidget(widget_principal);
        Onglet->setObjectName(QString::fromUtf8("Onglet"));
        Onglet->setGeometry(QRect(0, 0, 1000, 560));
        Onglet->setLayoutDirection(Qt::LeftToRight);
        Onglet->setAutoFillBackground(false);
        Onglet->setTabPosition(QTabWidget::North);
        Onglet->setTabShape(QTabWidget::Rounded);
        Onglet->setElideMode(Qt::ElideLeft);
        Onglet->setDocumentMode(false);
        Onglet->setTabsClosable(false);
        Onglet->setMovable(true);
        vol_immersif = new QWidget();
        vol_immersif->setObjectName(QString::fromUtf8("vol_immersif"));
        VideoStreaming = new QPushButton(vol_immersif);
        VideoStreaming->setObjectName(QString::fromUtf8("VideoStreaming"));
        VideoStreaming->setGeometry(QRect(30, 480, 361, 31));
        emergency_stop = new QPushButton(vol_immersif);
        emergency_stop->setObjectName(QString::fromUtf8("emergency_stop"));
        emergency_stop->setGeometry(QRect(760, 480, 221, 31));
        emergency_stop->setAutoDefault(false);
        gridLayoutWidget = new QWidget(vol_immersif);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 0, 681, 471));
        cameralayout = new QGridLayout(gridLayoutWidget);
        cameralayout->setSpacing(6);
        cameralayout->setContentsMargins(11, 11, 11, 11);
        cameralayout->setObjectName(QString::fromUtf8("cameralayout"));
        cameralayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_4 = new QWidget(vol_immersif);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(740, 200, 241, 221));
        maplayout = new QGridLayout(gridLayoutWidget_4);
        maplayout->setSpacing(6);
        maplayout->setContentsMargins(11, 11, 11, 11);
        maplayout->setObjectName(QString::fromUtf8("maplayout"));
        maplayout->setContentsMargins(0, 0, 0, 0);
        Photo = new QPushButton(vol_immersif);
        Photo->setObjectName(QString::fromUtf8("Photo"));
        Photo->setGeometry(QRect(420, 480, 191, 31));
        gridLayoutWidget_6 = new QWidget(vol_immersif);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(870, 80, 121, 41));
        batterylayout = new QGridLayout(gridLayoutWidget_6);
        batterylayout->setSpacing(6);
        batterylayout->setContentsMargins(11, 11, 11, 11);
        batterylayout->setObjectName(QString::fromUtf8("batterylayout"));
        batterylayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_7 = new QWidget(vol_immersif);
        gridLayoutWidget_7->setObjectName(QString::fromUtf8("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(870, 130, 121, 41));
        batterylayout_2 = new QGridLayout(gridLayoutWidget_7);
        batterylayout_2->setSpacing(6);
        batterylayout_2->setContentsMargins(11, 11, 11, 11);
        batterylayout_2->setObjectName(QString::fromUtf8("batterylayout_2"));
        batterylayout_2->setContentsMargins(0, 0, 0, 0);
        Name = new QLabel(vol_immersif);
        Name->setObjectName(QString::fromUtf8("Name"));
        Name->setGeometry(QRect(770, 100, 81, 21));
        Name_2 = new QLabel(vol_immersif);
        Name_2->setObjectName(QString::fromUtf8("Name_2"));
        Name_2->setGeometry(QRect(770, 150, 81, 21));
        line_2 = new QFrame(vol_immersif);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(710, 20, 20, 471));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget_9 = new QWidget(vol_immersif);
        gridLayoutWidget_9->setObjectName(QString::fromUtf8("gridLayoutWidget_9"));
        gridLayoutWidget_9->setGeometry(QRect(940, 10, 20, 51));
        powerlayout4 = new QGridLayout(gridLayoutWidget_9);
        powerlayout4->setSpacing(6);
        powerlayout4->setContentsMargins(11, 11, 11, 11);
        powerlayout4->setObjectName(QString::fromUtf8("powerlayout4"));
        powerlayout4->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_10 = new QWidget(vol_immersif);
        gridLayoutWidget_10->setObjectName(QString::fromUtf8("gridLayoutWidget_10"));
        gridLayoutWidget_10->setGeometry(QRect(920, 20, 20, 41));
        powerlayout3 = new QGridLayout(gridLayoutWidget_10);
        powerlayout3->setSpacing(6);
        powerlayout3->setContentsMargins(11, 11, 11, 11);
        powerlayout3->setObjectName(QString::fromUtf8("powerlayout3"));
        powerlayout3->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_11 = new QWidget(vol_immersif);
        gridLayoutWidget_11->setObjectName(QString::fromUtf8("gridLayoutWidget_11"));
        gridLayoutWidget_11->setGeometry(QRect(900, 30, 20, 31));
        powerlayout2 = new QGridLayout(gridLayoutWidget_11);
        powerlayout2->setSpacing(6);
        powerlayout2->setContentsMargins(11, 11, 11, 11);
        powerlayout2->setObjectName(QString::fromUtf8("powerlayout2"));
        powerlayout2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_12 = new QWidget(vol_immersif);
        gridLayoutWidget_12->setObjectName(QString::fromUtf8("gridLayoutWidget_12"));
        gridLayoutWidget_12->setGeometry(QRect(880, 40, 20, 21));
        powerlayout1 = new QGridLayout(gridLayoutWidget_12);
        powerlayout1->setSpacing(6);
        powerlayout1->setContentsMargins(11, 11, 11, 11);
        powerlayout1->setObjectName(QString::fromUtf8("powerlayout1"));
        powerlayout1->setContentsMargins(0, 0, 0, 0);
        Name_3 = new QLabel(vol_immersif);
        Name_3->setObjectName(QString::fromUtf8("Name_3"));
        Name_3->setGeometry(QRect(770, 50, 121, 21));
        Onglet->addTab(vol_immersif, QString());
        vol_vue = new QWidget();
        vol_vue->setObjectName(QString::fromUtf8("vol_vue"));
        emergency_stop_2 = new QPushButton(vol_vue);
        emergency_stop_2->setObjectName(QString::fromUtf8("emergency_stop_2"));
        emergency_stop_2->setGeometry(QRect(760, 480, 201, 31));
        emergency_stop_2->setAutoDefault(false);
        gridLayoutWidget_2 = new QWidget(vol_vue);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 30, 681, 471));
        horizon_layout = new QGridLayout(gridLayoutWidget_2);
        horizon_layout->setSpacing(6);
        horizon_layout->setContentsMargins(11, 11, 11, 11);
        horizon_layout->setObjectName(QString::fromUtf8("horizon_layout"));
        horizon_layout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_5 = new QWidget(vol_vue);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(740, 200, 241, 221));
        maplayout2 = new QGridLayout(gridLayoutWidget_5);
        maplayout2->setSpacing(6);
        maplayout2->setContentsMargins(11, 11, 11, 11);
        maplayout2->setObjectName(QString::fromUtf8("maplayout2"));
        maplayout2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_3 = new QWidget(vol_vue);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(870, 80, 121, 41));
        batterylayout2 = new QGridLayout(gridLayoutWidget_3);
        batterylayout2->setSpacing(6);
        batterylayout2->setContentsMargins(11, 11, 11, 11);
        batterylayout2->setObjectName(QString::fromUtf8("batterylayout2"));
        batterylayout2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_8 = new QWidget(vol_vue);
        gridLayoutWidget_8->setObjectName(QString::fromUtf8("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(870, 130, 121, 41));
        batterylayout2_2 = new QGridLayout(gridLayoutWidget_8);
        batterylayout2_2->setSpacing(6);
        batterylayout2_2->setContentsMargins(11, 11, 11, 11);
        batterylayout2_2->setObjectName(QString::fromUtf8("batterylayout2_2"));
        batterylayout2_2->setContentsMargins(0, 0, 0, 0);
        Name2 = new QLabel(vol_vue);
        Name2->setObjectName(QString::fromUtf8("Name2"));
        Name2->setGeometry(QRect(770, 100, 81, 21));
        Name2_2 = new QLabel(vol_vue);
        Name2_2->setObjectName(QString::fromUtf8("Name2_2"));
        Name2_2->setGeometry(QRect(770, 150, 81, 21));
        line = new QFrame(vol_vue);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(710, 20, 20, 471));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget_13 = new QWidget(vol_vue);
        gridLayoutWidget_13->setObjectName(QString::fromUtf8("gridLayoutWidget_13"));
        gridLayoutWidget_13->setGeometry(QRect(940, 10, 20, 51));
        powerlayout4_2 = new QGridLayout(gridLayoutWidget_13);
        powerlayout4_2->setSpacing(6);
        powerlayout4_2->setContentsMargins(11, 11, 11, 11);
        powerlayout4_2->setObjectName(QString::fromUtf8("powerlayout4_2"));
        powerlayout4_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_14 = new QWidget(vol_vue);
        gridLayoutWidget_14->setObjectName(QString::fromUtf8("gridLayoutWidget_14"));
        gridLayoutWidget_14->setGeometry(QRect(920, 20, 20, 41));
        powerlayout3_2 = new QGridLayout(gridLayoutWidget_14);
        powerlayout3_2->setSpacing(6);
        powerlayout3_2->setContentsMargins(11, 11, 11, 11);
        powerlayout3_2->setObjectName(QString::fromUtf8("powerlayout3_2"));
        powerlayout3_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_15 = new QWidget(vol_vue);
        gridLayoutWidget_15->setObjectName(QString::fromUtf8("gridLayoutWidget_15"));
        gridLayoutWidget_15->setGeometry(QRect(900, 30, 20, 31));
        powerlayout2_2 = new QGridLayout(gridLayoutWidget_15);
        powerlayout2_2->setSpacing(6);
        powerlayout2_2->setContentsMargins(11, 11, 11, 11);
        powerlayout2_2->setObjectName(QString::fromUtf8("powerlayout2_2"));
        powerlayout2_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_16 = new QWidget(vol_vue);
        gridLayoutWidget_16->setObjectName(QString::fromUtf8("gridLayoutWidget_16"));
        gridLayoutWidget_16->setGeometry(QRect(880, 40, 20, 21));
        powerlayout1_2 = new QGridLayout(gridLayoutWidget_16);
        powerlayout1_2->setSpacing(6);
        powerlayout1_2->setContentsMargins(11, 11, 11, 11);
        powerlayout1_2->setObjectName(QString::fromUtf8("powerlayout1_2"));
        powerlayout1_2->setContentsMargins(0, 0, 0, 0);
        Name_4 = new QLabel(vol_vue);
        Name_4->setObjectName(QString::fromUtf8("Name_4"));
        Name_4->setGeometry(QRect(770, 50, 121, 21));
        Onglet->addTab(vol_vue, QString());
        MainWindow->setCentralWidget(widget_principal);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 27));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        Onglet->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        Onglet->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        VideoStreaming->setText(QApplication::translate("MainWindow", "START/STOP VIDEO STREAMING", 0, QApplication::UnicodeUTF8));
        emergency_stop->setText(QApplication::translate("MainWindow", "EMERGENCY STOP", 0, QApplication::UnicodeUTF8));
        Photo->setText(QApplication::translate("MainWindow", "TAKE PICTURE", 0, QApplication::UnicodeUTF8));
        Name->setText(QApplication::translate("MainWindow", "BASE", 0, QApplication::UnicodeUTF8));
        Name_2->setText(QApplication::translate("MainWindow", "DRONE", 0, QApplication::UnicodeUTF8));
        Name_3->setText(QApplication::translate("MainWindow", "SIGNAL RF", 0, QApplication::UnicodeUTF8));
        Onglet->setTabText(Onglet->indexOf(vol_immersif), QApplication::translate("MainWindow", "Vol immersif", 0, QApplication::UnicodeUTF8));
        emergency_stop_2->setText(QApplication::translate("MainWindow", "EMERGENCY STOP", 0, QApplication::UnicodeUTF8));
        Name2->setText(QApplication::translate("MainWindow", "BASE", 0, QApplication::UnicodeUTF8));
        Name2_2->setText(QApplication::translate("MainWindow", "DRONE", 0, QApplication::UnicodeUTF8));
        Name_4->setText(QApplication::translate("MainWindow", "SIGNAL RF", 0, QApplication::UnicodeUTF8));
        Onglet->setTabText(Onglet->indexOf(vol_vue), QApplication::translate("MainWindow", "Vol \303\240 vue", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
