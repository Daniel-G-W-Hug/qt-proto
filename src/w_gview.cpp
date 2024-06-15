#include "w_gview.hpp"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPainter>
#include <QPointF>
#include <QRectF>

w_gview::w_gview(QWidget* parent) : QGraphicsView(parent)
{

    // create an initial scene
    QGraphicsScene* scene = new QGraphicsScene(this);

    // only if animations become too slow
    // scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // QRectF( QPointF(ToPLeft), QPointF(BottomRight) )
    // scene->setSceneRect(QRectF(QPointF(-1.1, 1.1), QPointF(1.1, -1.1)));

    // alternate approach:
    scene->setSceneRect(-200, -200, 400, 400);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setMinimumSize(400, 400);
}

// void w_gview::paintEvent(QPaintEvent*)
// {

//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);
//     // painter.translate(width() / 2, height() / 2);
//     // painter.scale(side / 200.0, side / 200.0);

//     painter.setPen(Qt::black);
//     // painter.setBrush(Qt::black);

//     // painter.save();
//     // painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
//     // painter.drawConvexPolygon(hourHand, 4);
//     // painter.restore();

//     painter.drawRect(20, 20, 360, 360);
//     painter.drawLine(20, 20, 380, 380);
//     painter.drawLine(20, 380, 380, 20);
// }
