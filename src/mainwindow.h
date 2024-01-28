#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QCalendarWidget>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QCalendarWidget *cals[3];
    QIcon theIcon;

private slots:
    void dateChanged1(int curYear, int curMon);
    void dateChanged2(int curYear, int curMon);
    void dateChanged3(int curYear, int curMon);
    void setNow();

public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // MAINWINDOW_H
