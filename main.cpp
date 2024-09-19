#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

QString MainWindow::apiFile;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (argc < 2) {
        qInfo() << "Usage:" << argv[0] << "{api file}";
        return 1;
    } else {

        MainWindow::apiFile = QString::fromUtf8(argv[1]);
        qDebug() << MainWindow::apiFile;
    }

    MainWindow window;
    window.show();

    return app.exec();
}
