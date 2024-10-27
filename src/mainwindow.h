#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QIcon>

#include "customcalendar.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    CustomCalendar *cals[3];
    QIcon theIcon;

private slots:
    void dateChanged1(int, int);
    void dateChanged2(int, int);
    void dateChanged3(int, int);
    void setNow();
    void resizeEvent(QResizeEvent *);

public:
    MainWindow();
};
#endif // MAINWINDOW_H
