#include <QFont>

#include "customcalendar.h"

void CustomCalendar::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
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
