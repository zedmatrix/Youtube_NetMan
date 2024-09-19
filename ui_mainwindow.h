/********************************************************************************
** Form generated from reading UI file 'mainwindowgQwAZA.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWGQWAZA_H
#define MAINWINDOWGQWAZA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *urlInput;
    QTextBrowser *urlOutput;
    QPushButton *quit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        urlInput = new QLineEdit(centralwidget);
        urlInput->setObjectName("urlInput");
        urlInput->setGeometry(QRect(10, 10, 471, 24));
        urlOutput = new QTextBrowser(centralwidget);
        urlOutput->setObjectName("urlOutput");
        urlOutput->setGeometry(QRect(10, 40, 781, 431));
        urlOutput->setOpenExternalLinks(false);
        quit = new QPushButton(centralwidget);
        quit->setObjectName("quit");
        quit->setGeometry(QRect(10, 530, 82, 28));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        quit->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        quit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWGQWAZA_H
