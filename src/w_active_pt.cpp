#include "w_active_pt.hpp"

static constexpr float RADIUS = 5;

active_pt::active_pt(QPointF const& pos, QGraphicsItem* parent) :
    QGraphicsItem(parent), m_pos{pos}
{
    setPos(pos.x(), pos.y()); // store scene position
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
}

void active_pt::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                      QWidget* widget)
{

    QColor const col_blue = QColor(0, 0, 255, 127);
    QColor const col_green = QColor(0, 255, 0, 127);
    QColor const col_red = QColor(255, 0, 0, 127);

    // draw in item coordinate system
    painter->save();

    painter->setPen(col_blue);
    painter->setBrush(col_blue); // selectable: blue (default)

    if (m_mouse_hover && !m_mouse_pressed) {
        painter->setPen(col_green);
        painter->setBrush(col_green); // hover: green
    }
    if (m_mouse_hover && m_mouse_pressed) {
        painter->setPen(col_red);
        painter->setBrush(col_red); // selected: red
    }

    painter->drawEllipse(QRectF(QPointF(-RADIUS, -RADIUS), QPointF(RADIUS, RADIUS)));

    painter->restore();
}

QRectF active_pt::boundingRect() const
{
    return QRectF(QPointF(-RADIUS, -RADIUS), QPointF(RADIUS, RADIUS));
}

void active_pt::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    qDebug() << "active_pt::hoverEnterEvent.";
    // qDebug() << "mouse(" << event->pos().x << "," << event->pos().y << ").\n";

    m_mouse_hover = true;
    update();
}

void active_pt::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    qDebug() << "active_pt::hoverLeaveEvent.";
    // qDebug() << "mouse(" << event->pos().x << "," << event->pos().y << ").\n";

    m_mouse_hover = false;
    update();
}

void active_pt::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "active_pt::mousePressEvent.";

    m_mouse_pressed = true;
    update();

    QGraphicsItem::mousePressEvent(event); // call default implementation
}

void active_pt::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "active_pt::mouseReleaseEvent.";
    qDebug() << "m_pos:" << m_pos;

    m_mouse_pressed = false;
    update();

    QGraphicsItem::mouseReleaseEvent(event); // call default implementation
}

void active_pt::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "active_pt::mouseMoveEvent.";
    // qDebug() << "pos():" << event->pos();
    // qDebug() << "scenePos():" << event->scenePos();

    // update internally stored scene position of the item
    // corrected by gripping distance to the center pos
    QPointF new_pos = event->scenePos() - event->pos();
    if (m_pos != new_pos) {
        m_pos = new_pos;
    }

    QGraphicsItem::mouseMoveEvent(event); // move the item normally
}