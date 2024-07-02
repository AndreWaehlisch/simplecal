#include "mainwindow.h"
#include "holidays.h"

#include <QGridLayout>
#include <QDate>
#include <QFont>
#include <QTextCharFormat>
#include <QPushButton>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QSettings settings;
    QWidget *const widget = new QWidget(this);
    QGridLayout *const layout = new QGridLayout(widget);
    QPushButton *const nowButton = new QPushButton("+", widget);
    theIcon = QIcon(":/icon.ico");

    const int curYear = QDate::currentDate().year();
    const int curMon = QDate::currentDate().month();

    this->setWindowIcon(theIcon);

    QTextCharFormat headerFontFormat;
    headerFontFormat.setFontWeight(QFont::Bold);
    QTextCharFormat weekendFontFormat;
    weekendFontFormat.setForeground(QColor(Qt::blue));
    QTextCharFormat holidayFontFormat;
    holidayFontFormat.setForeground(QColor(Qt::red));
    holidayFontFormat.setFontWeight(QFont::Bold);
    holidayFontFormat.setFontUnderline(true);

    for (int i_cal = 0; i_cal < 3; ++i_cal) {
        QCalendarWidget *cal = new QCalendarWidget;
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

    if ( curMon == 1 ) {
        cals[0]->setCurrentPage(curYear - 1, 12);
    } else {
        cals[0]->setCurrentPage(curYear, curMon - 1);
    }

    cals[1]->setCurrentPage(curYear, curMon);

    if ( curMon == 12 ) {
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else {
        cals[2]->setCurrentPage(curYear, curMon + 1);
    }

    for (int i_cal = 0; i_cal < 3; ++i_cal) {
        for (int i = 0; i < dateList.size(); i++) {
            cals[i_cal]->setDateTextFormat(dateList[i], holidayFontFormat);
        }

        layout->addWidget(cals[i_cal], 0, i_cal);
    }

    layout->addWidget(nowButton, 1, 1);
    layout->setHorizontalSpacing(60);

    this->setCentralWidget(widget);
    widget->setLayout(layout);

    this->setMinimumSize(1050, 250);
    this->resize(settings.value("width", 1600).toInt(), settings.value("height", 500).toInt());

    connect(cals[0], &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged1);
    connect(cals[1], &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged2);
    connect(cals[2], &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged3);
    connect(nowButton, &QAbstractButton::clicked, this, &MainWindow::setNow);
}

void MainWindow::resizeEvent(QResizeEvent *) {
    QSettings settings;
    settings.setValue("width", this->width());
    settings.setValue("height", this->height());
}

void MainWindow::dateChanged1(int curYear, int curMon) {
    if ( curMon == 11 ) {
        cals[1]->setCurrentPage(curYear, 12);
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else if ( curMon == 12 ) {
        cals[1]->setCurrentPage(curYear + 1, 1);
        cals[2]->setCurrentPage(curYear + 1, 2);
    } else {
        cals[1]->setCurrentPage(curYear, curMon + 1);
        cals[2]->setCurrentPage(curYear, curMon + 2);
    }
}

void MainWindow::dateChanged2(int curYear, int curMon) {
    if ( curMon == 1 ) {
        cals[0]->setCurrentPage(curYear - 1, 12);
        cals[2]->setCurrentPage(curYear, 2);
    } else if ( curMon == 12 ) {
        cals[0]->setCurrentPage(curYear, 11);
        cals[2]->setCurrentPage(curYear + 1, 1);
    } else {
        cals[0]->setCurrentPage(curYear, curMon - 1);
        cals[2]->setCurrentPage(curYear, curMon + 1);
    }
}

void MainWindow::dateChanged3(int curYear, int curMon) {
    if ( curMon == 1 ) {
        cals[1]->setCurrentPage(curYear - 1, 12);
        cals[0]->setCurrentPage(curYear - 1, 11);
    } else if ( curMon == 2 ) {
        cals[1]->setCurrentPage(curYear, 1);
        cals[0]->setCurrentPage(curYear - 1, 12);
    } else {
        cals[1]->setCurrentPage(curYear, curMon - 1);
        cals[0]->setCurrentPage(curYear, curMon - 2);
    }
}

void MainWindow::setNow() {
    cals[1]->showToday();
    this->dateChanged2(cals[1]->yearShown(), cals[1]->monthShown());
}
