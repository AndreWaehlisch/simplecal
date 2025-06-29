#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    app.setOrganizationName("AndreWaehlisch");
    app.setApplicationName("simplecal");
    MainWindow win;
    win.show();
    return app.exec();
}
