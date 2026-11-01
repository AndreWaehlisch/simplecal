#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QIcon>
#include <QSettings>

#include "customcalendar.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    CustomCalendar *cals[3];
    QIcon theIcon;
    QSettings theSettings;

private slots:
    void dateChanged1(const int, const int);
    void dateChanged2(const int, const int);
    void dateChanged3(const int, const int);
    void setNow();
    void resizeEvent(QResizeEvent *);

public:
    MainWindow();
};
#endif // MAINWINDOW_H
