#include "w_main.hpp"
#include "w_active_pt.hpp"

#include <QPainter>

w_main::w_main(QWidget* parent) : QWidget(parent)
{
    resize(400, 400);
    w_child = new w_active_pt(this);
    w_child->show();
}

void w_main::paintEvent(QPaintEvent*)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.translate(width() / 2, height() / 2);
    // painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::black);
    // painter.setBrush(Qt::black);

    // painter.save();
    // painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    // painter.drawConvexPolygon(hourHand, 4);
    // painter.restore();

    painter.drawRect(20, 20, 360, 360);
    painter.drawLine(20, 20, 380, 380);
    painter.drawLine(20, 380, 380, 20);
}
