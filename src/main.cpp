#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("AndreWaehlisch");
    QCoreApplication::setApplicationName("simplecal");
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
