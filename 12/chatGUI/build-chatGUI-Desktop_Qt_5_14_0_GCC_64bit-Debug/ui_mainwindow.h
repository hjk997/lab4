/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *connectbtn;
    QPushButton *exitbtn;
    QPushButton *sendbtn;
    QTextEdit *Entry;
    QTextEdit *chat;
    QPushButton *Sync;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 367);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        connectbtn = new QPushButton(centralwidget);
        connectbtn->setObjectName(QString::fromUtf8("connectbtn"));
        connectbtn->setGeometry(QRect(400, 10, 89, 25));
        exitbtn = new QPushButton(centralwidget);
        exitbtn->setObjectName(QString::fromUtf8("exitbtn"));
        exitbtn->setGeometry(QRect(400, 40, 89, 25));
        sendbtn = new QPushButton(centralwidget);
        sendbtn->setObjectName(QString::fromUtf8("sendbtn"));
        sendbtn->setGeometry(QRect(400, 290, 89, 25));
        Entry = new QTextEdit(centralwidget);
        Entry->setObjectName(QString::fromUtf8("Entry"));
        Entry->setGeometry(QRect(10, 290, 381, 31));
        chat = new QTextEdit(centralwidget);
        chat->setObjectName(QString::fromUtf8("chat"));
        chat->setGeometry(QRect(10, 10, 381, 271));
        chat->setReadOnly(true);
        Sync = new QPushButton(centralwidget);
        Sync->setObjectName(QString::fromUtf8("Sync"));
        Sync->setGeometry(QRect(400, 100, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(exitbtn, SIGNAL(clicked()), MainWindow, SLOT(exitslot()));
        QObject::connect(connectbtn, SIGNAL(clicked()), MainWindow, SLOT(connectslot()));
        QObject::connect(sendbtn, SIGNAL(clicked()), MainWindow, SLOT(sendslot()));
        QObject::connect(Sync, SIGNAL(clicked()), MainWindow, SLOT(readslot()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        connectbtn->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        exitbtn->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        sendbtn->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        Sync->setText(QCoreApplication::translate("MainWindow", "Sync", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
