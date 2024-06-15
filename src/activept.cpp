#include "activept.hpp"
#include "edge.hpp"
#include "w_gview.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QtWidgets>


activePt::activePt(w_gview* gview) : gview{gview}
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void activePt::addEdge(edge* edge)
{
    m_edge = edge;
    m_edge->adjust();
}

void activePt::calculate()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
}

bool activePt::advance()
{
    if (newPos == pos()) return false;

    setPos(newPos);
    return true;
}


QRectF activePt::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath activePt::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void activePt::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    }
    else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant activePt::itemChange(GraphicsItemChange change, const QVariant& value)
{
    switch (change) {
        case ItemPositionHasChanged:
            m_edge->adjust();   // inform linked vector to update itself
            gview->itemMoved(); // inform graphicsview of required update
            break;
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void activePt::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void activePt::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}