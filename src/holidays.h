#ifndef HOLIDAYS_H
#define HOLIDAYS_H

#include <QDate>
#include <QList>

/*
 *  add special/one-off holidays here - see, for example: https://github.com/KDE/kholidays/blob/master/holidays/plan2/holiday_de-be_de
 *  recurring holidays are added in mainwindow.cpp
 */

QList<QDate> holidayList = {
    QDate(2020, 5, 8), // 75. Jahrestag der Befreiung
    QDate(2025, 5, 8), // 80. Jahrestag der Befreiung
    QDate(2028, 6, 17), // 75. Jahrestag Volksaufstand DDR
};

#endif // HOLIDAYS_H
