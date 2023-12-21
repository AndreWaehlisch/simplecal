#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images); // init resources (needed for static build)
    QApplication app(argc, argv);
    MainWindow::theIcon = QIcon(":/icon.ico");
    MainWindow win;
    win.show();
    return app.exec();
}
