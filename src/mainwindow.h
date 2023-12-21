#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QDate>
#include <QFont>
#include <QTextCharFormat>
#include <QPushButton>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *widget;
    QGridLayout *layout;
    QCalendarWidget *calendar1;
    QCalendarWidget *calendar2;
    QCalendarWidget *calendar3;

private slots:
    void dateChanged1(int curYear, int curMon);
    void dateChanged2(int curYear, int curMon);
    void dateChanged3(int curYear, int curMon);
    void setNow();

public:
    MainWindow(QWidget *parent = nullptr);
    static QIcon theIcon;
};
#endif // MAINWINDOW_H
