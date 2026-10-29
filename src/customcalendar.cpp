#include <QFont>

#include "customcalendar.h"

void CustomCalendar::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    // highlight current date
    // the standard setForeground() approach (e.g. used in mainwindow.cpp for holidays) gets overwritten by QCalendarWidget's internals when the day that is shown is a adjacent-month day, that is not within the currently shown month
    if (date == QDate::currentDate()) {
        QFont font = painter->font();
        font.setBold(true);

        painter->save();
        painter->setFont(font);
        painter->setBrush(Qt::gray);
        painter->drawRect(rect);
        painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString::number(date.day()));
        painter->restore();
    } else {
        QCalendarWidget::paintCell(painter, rect, date);
    }
}
