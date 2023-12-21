#include "mainwindow.h"
#include "holidays.h"

QIcon MainWindow::theIcon; // must construct QIcon object after QMainApplication, so do just that in main.cpp

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

    calendar1 = new QCalendarWidget;
    calendar1->setFirstDayOfWeek(Qt::Monday);
    calendar1->setSelectionMode(QCalendarWidget::SingleSelection);
    calendar1->setHorizontalHeaderFormat(QCalendarWidget::LongDayNames);
    calendar1->setHeaderTextFormat(headerFontFormat);
    calendar1->setWeekdayTextFormat(Qt::Saturday, weekendFontFormat);
    calendar1->setWeekdayTextFormat(Qt::Sunday, weekendFontFormat);
    calendar1->setMinimumDate(QDate(1900, 1, 1));
    calendar1->setMaximumDate(QDate(3000, 1, 1));
    calendar1->setGridVisible(true);
    if ( curMon == 1 ) {
        calendar1->setCurrentPage(curYear - 1, 12);
    } else {
        calendar1->setCurrentPage(curYear, curMon - 1);
    }

    calendar2 = new QCalendarWidget;
    calendar2->setFirstDayOfWeek(Qt::Monday);
    calendar2->setSelectionMode(QCalendarWidget::SingleSelection);
    calendar2->setHorizontalHeaderFormat(QCalendarWidget::LongDayNames);
    calendar2->setHeaderTextFormat(headerFontFormat);
    calendar2->setWeekdayTextFormat(Qt::Saturday, weekendFontFormat);
    calendar2->setWeekdayTextFormat(Qt::Sunday, weekendFontFormat);
    calendar2->setMinimumDate(QDate(1900, 1, 1));
    calendar2->setMaximumDate(QDate(3000, 1, 1));
    calendar2->setGridVisible(true);
    calendar2->setCurrentPage(curYear, curMon);

    calendar3 = new QCalendarWidget;
    calendar3->setFirstDayOfWeek(Qt::Monday);
    calendar3->setSelectionMode(QCalendarWidget::SingleSelection);
    calendar3->setHorizontalHeaderFormat(QCalendarWidget::LongDayNames);
    calendar3->setHeaderTextFormat(headerFontFormat);
    calendar3->setWeekdayTextFormat(Qt::Saturday, weekendFontFormat);
    calendar3->setWeekdayTextFormat(Qt::Sunday, weekendFontFormat);
    calendar3->setMinimumDate(QDate(1900, 1, 1));
    calendar3->setMaximumDate(QDate(3000, 1, 1));
    calendar3->setGridVisible(true);
    if ( curMon == 12 ) {
        calendar3->setCurrentPage(curYear + 1, 1);
    } else {
        calendar3->setCurrentPage(curYear, curMon + 1);
    }

    for (int i = 0; i < dateList.size(); i++) {
        calendar1->setDateTextFormat(dateList[i], holidayFontFormat);
        calendar2->setDateTextFormat(dateList[i], holidayFontFormat);
        calendar3->setDateTextFormat(dateList[i], holidayFontFormat);
    }

    QPushButton* nowButton = new QPushButton("+", this);
    layout = new QGridLayout;
    layout->addWidget(calendar1, 0, 0);
    layout->addWidget(calendar2, 0, 1);
    layout->addWidget(calendar3, 0, 2);
    layout->addWidget(nowButton, 1, 1);

    layout->setHorizontalSpacing(60);

    widget = new QWidget;
    this->setCentralWidget(widget);
    widget->setLayout(layout);

    resize(1600, 500);

    connect(calendar1, &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged1);
    connect(calendar2, &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged2);
    connect(calendar3, &QCalendarWidget::currentPageChanged, this, &MainWindow::dateChanged3);
    connect(nowButton, &QAbstractButton::clicked, this, &MainWindow::setNow);
}

void MainWindow::dateChanged1(int curYear, int curMon) {
    if ( curMon == 11 ) {
        calendar2->setCurrentPage(curYear, 12);
        calendar3->setCurrentPage(curYear + 1, 1);
    } else if ( curMon == 12 ) {
        calendar2->setCurrentPage(curYear + 1, 1);
        calendar3->setCurrentPage(curYear + 1, 2);
    } else {
        calendar2->setCurrentPage(curYear, curMon + 1);
        calendar3->setCurrentPage(curYear, curMon + 2);
    }
}

void MainWindow::dateChanged2(int curYear, int curMon) {
    if ( curMon == 1 ) {
        calendar1->setCurrentPage(curYear - 1, 12);
        calendar3->setCurrentPage(curYear, 2);
    } else if ( curMon == 12 ) {
        calendar1->setCurrentPage(curYear, 11);
        calendar3->setCurrentPage(curYear + 1, 1);
    } else {
        calendar1->setCurrentPage(curYear, curMon - 1);
        calendar3->setCurrentPage(curYear, curMon + 1);
    }
}

void MainWindow::dateChanged3(int curYear, int curMon) {
    if ( curMon == 1 ) {
        calendar2->setCurrentPage(curYear - 1, 12);
        calendar1->setCurrentPage(curYear - 1, 11);
    } else if ( curMon == 2 ) {
        calendar2->setCurrentPage(curYear, 1);
        calendar1->setCurrentPage(curYear - 1, 12);
    } else {
        calendar2->setCurrentPage(curYear, curMon - 1);
        calendar1->setCurrentPage(curYear, curMon - 2);
    }
}

void MainWindow::setNow() {
    calendar2->showToday();
    this->dateChanged2(calendar2->yearShown(), calendar2->monthShown());
}
