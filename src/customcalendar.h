#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QCalendarWidget>
#include <QPainter>
#include <QRect>
#include <QDate>

class CustomCalendar : public QCalendarWidget
{
    using QCalendarWidget::QCalendarWidget;

private:
    void paintCell(QPainter *, const QRect &, QDate) const;
};

#endif // CUSTOMCALENDAR_H
