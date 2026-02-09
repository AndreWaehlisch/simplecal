#include "mainwindow.h"
#include "holidays.h"

#include <QGridLayout>
#include <QDate>
#include <QFont>
#include <QTextCharFormat>
#include <QPushButton>
#include <QSettings>

MainWindow::MainWindow(): QWidget(nullptr)
{
    QSettings settings;
    QGridLayout *const layout = new QGridLayout(this);
    QPushButton *const nowButton = new QPushButton("+", this);
    theIcon = QIcon(":/icon.ico");

    const QDate today = QDate::currentDate();
    const int curYear = today.year();
    const int curMon = today.month();

    setWindowIcon(theIcon);

    QTextCharFormat headerFontFormat;
    headerFontFormat.setFontWeight(QFont::Bold);
    QTextCharFormat weekendFontFormat;
    weekendFontFormat.setForeground(QColor(Qt::blue));
    QTextCharFormat holidayFontFormat;
    holidayFontFormat.setForeground(QColor(Qt::red));
    holidayFontFormat.setFontWeight(QFont::Bold);
    holidayFontFormat.setFontUnderline(true);

    for (int i_cal = 0; i_cal < 3; i_cal++) {
        CustomCalendar *cal = new CustomCalendar(this);
        cals[i_cal] = cal;
        cal->setFirstDayOfWeek(Qt::Monday);
        cal->setSelectionMode(QCalendarWidget::NoSelection);
        cal->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        cal->setHeaderTextFormat(headerFontFormat);
        cal->setWeekdayTextFormat(Qt::Saturday, weekendFontFormat);
        cal->setWeekdayTextFormat(Qt::Sunday, weekendFontFormat);
        cal->setMinimumDate(QDate(1900, 1, 1));
        cal->setMaximumDate(QDate(3000, 1, 1));
        cal->setGridVisible(true);
        cal->setNavigationBarVisible(true);
    }

    if (curMon == 1) {
        cals[0]->setCurrentPage(curYear - 1, 12);
    } else {
        cals[0]->setCurrentPage(curYear, curMon - 1);
    }

    cals[1]->setCurrentPage(curYear, curMon);

    if (curMon == 12) {
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else {
        cals[2]->setCurrentPage(curYear, curMon + 1);
    }

    {
        /*
         *  add repeating holidays
         *  for details see, for example:
         *  https://github.com/KDE/kholidays/blob/master/holidays/plan2/holiday_de-be_de
         *  https://en.wikipedia.org/wiki/Date_of_Easter#Anonymous_Gregorian_algorithm
         */
        QDate Easter, Karfreitag, Ostermontag, ChristiHimmelfahrt, Pfingstmontag;
        int a, b, c, d, e, f, g, h, i, k, l, m, n, o;
        for (int year = 1990; year < 2090; ++year) {
            a = year % 19;
            b = qFloor(year / 100.);
            c = year % 100;
            d = qFloor(b / 4.);
            e = b % 4;
            f = qFloor((b + 8) / 25.);
            g = qFloor((b - f + 1) / 3.);
            h = (19 * a + b - d - g + 15) % 30;
            i = qFloor(c / 4.);
            k = c % 4;
            l = (32 + 2 * e + 2 * i - h - k) % 7;
            m = qFloor((a + 11 * h + 22 * l) / 451.);
            n = qFloor((h + l - 7 * m + 114) / 31.);
            o = (h + l - 7 * m + 114) % 31;
            Easter = QDate(year, n, o + 1);
            Karfreitag = Easter.addDays(-2);
            Ostermontag = Easter.addDays(1);
            ChristiHimmelfahrt = Easter.addDays(39);
            Pfingstmontag = Easter.addDays(50);

            holidayList.append(QDate(year, 1, 1)); // Neujahr
            if (year >= 2019) {
                holidayList.append(QDate(year, 3, 8)); // Frauentag
            }
            holidayList.append(Karfreitag);
            holidayList.append(Ostermontag);
            holidayList.append(QDate(year, 5, 1)); // Tag der Arbeit
            holidayList.append(ChristiHimmelfahrt);
            holidayList.append(Pfingstmontag);
            holidayList.append(QDate(year, 10, 3)); // Tag der Deutschen Einheit
            holidayList.append(QDate(year, 12, 25)); // 1. Weihnachtstag
            holidayList.append(QDate(year, 12, 26)); // 2. Weihnachtstag
        }
    }

    for (int i_cal = 0; i_cal < 3; ++i_cal) {
        foreach (QDate i_holiday, holidayList) {
            cals[i_cal]->setDateTextFormat(i_holiday, holidayFontFormat);
        }

        layout->addWidget(cals[i_cal], 0, i_cal);
    }

    layout->addWidget(nowButton, 1, 1);
    layout->setHorizontalSpacing(60);

    setLayout(layout);

    setMinimumSize(1050, 250);
    resize(settings.value("width", 1600).toInt(), settings.value("height", 500).toInt());

    connect(cals[0], &CustomCalendar::currentPageChanged, this, &MainWindow::dateChanged1);
    connect(cals[1], &CustomCalendar::currentPageChanged, this, &MainWindow::dateChanged2);
    connect(cals[2], &CustomCalendar::currentPageChanged, this, &MainWindow::dateChanged3);
    connect(nowButton, &QAbstractButton::clicked, this, &MainWindow::setNow);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    QSettings settings;
    settings.setValue("width", width());
    settings.setValue("height", height());
}

void MainWindow::dateChanged1(int curYear, int curMon)
{
    if (curMon == 11) {
        cals[1]->setCurrentPage(curYear, 12);
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else if (curMon == 12) {
        cals[1]->setCurrentPage(curYear + 1, 1);
        cals[2]->setCurrentPage(curYear + 1, 2);
    } else {
        cals[1]->setCurrentPage(curYear, curMon + 1);
        cals[2]->setCurrentPage(curYear, curMon + 2);
    }
}

void MainWindow::dateChanged2(int curYear, int curMon)
{
    if (curMon == 1) {
        cals[0]->setCurrentPage(curYear - 1, 12);
        cals[2]->setCurrentPage(curYear, 2);
    } else if (curMon == 12) {
        cals[0]->setCurrentPage(curYear, 11);
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else {
        cals[0]->setCurrentPage(curYear, curMon - 1);
        cals[2]->setCurrentPage(curYear, curMon + 1);
    }
}

void MainWindow::dateChanged3(int curYear, int curMon)
{
    if (curMon == 1) {
        cals[1]->setCurrentPage(curYear - 1, 12);
        cals[0]->setCurrentPage(curYear - 1, 11);
    } else if (curMon == 2) {
        cals[1]->setCurrentPage(curYear, 1);
        cals[0]->setCurrentPage(curYear - 1, 12);
    } else {
        cals[1]->setCurrentPage(curYear, curMon - 1);
        cals[0]->setCurrentPage(curYear, curMon - 2);
    }
}

void MainWindow::setNow()
{
    cals[1]->showToday();
    dateChanged2(cals[1]->yearShown(), cals[1]->monthShown());
}
