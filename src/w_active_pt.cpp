#include "w_active_pt.hpp"

#include <QPainter>

w_active_pt::w_active_pt(QWidget* parent) : QWidget(parent) { resize(10, 10); }

void w_active_pt::paintEvent(QPaintEvent*)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.translate(width() / 2, height() / 2);
    // painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawEllipse(100, 100, 10, 10);

    // painter.save();
    // painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    // painter.drawConvexPolygon(hourHand, 4);
    // painter.restore();
}