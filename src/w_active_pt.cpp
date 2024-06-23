#include "w_active_pt.hpp"
#include "w_active_vec.hpp"

#include <utility> // std::unreachable()

static constexpr float RADIUS = 4;

active_pt::active_pt(QPointF const& pos, QGraphicsItem* parent) :
    QGraphicsItem(parent), m_pos{pos}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    setPos(pos.x(), pos.y()); // set item to scene coordinates
    emit scenePosChanged(m_pos);
    update();
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

    if (m_mouse_hover && !m_mouse_l_pressed) {
        painter->setPen(col_green);
        painter->setBrush(col_green); // hover: green
    }
    if (m_mouse_hover && m_mouse_l_pressed) {
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

QPainterPath active_pt::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void active_pt::setScenePos(QPointF const& pos)
{
    // qDebug() << "active_pt::setScenePos called.";

    if (m_pos != pos) {

        // qDebug() << "active_pt::setScenePos changed.";

        prepareGeometryChange();
        m_pos = pos;
        emit scenePosChanged(m_pos);
        update();
    }
}

QPointF active_pt::scenePos() { return m_pos; }

void active_pt::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_pt::hoverEnterEvent.";
    m_mouse_hover = true;
    update();
}

void active_pt::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_pt::hoverLeaveEvent.";
    m_mouse_hover = false;
    update();
}

void active_pt::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_pt::mousePressEvent.";

    if (event->button() == Qt::LeftButton) {
        // qDebug() << "active_pt: Qt::LeftButton.";
        m_mouse_l_pressed = true;
    }
    if (event->button() == Qt::RightButton) {
        // qDebug() << "active_pt: Qt::RightButton.";
        m_mouse_r_pressed = true;
    }
    update();

    QGraphicsItem::mousePressEvent(event); // call default implementation
}

void active_pt::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_pt::mouseReleaseEvent.";
    // qDebug() << "active_vec::scenePos:" << scenePos();

    if (event->button() == Qt::LeftButton) {
        // qDebug() << "active_pt: Qt::LeftButton.";
        m_mouse_l_pressed = false;
    }
    if (event->button() == Qt::RightButton) {
        // qDebug() << "active_pt: Qt::RightButton.";
        m_mouse_r_pressed = false;
    }
    update();

    QGraphicsItem::mouseReleaseEvent(event); // call default implementation
}

void active_pt::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_pt::mouseMoveEvent.";

    if (m_mouse_l_pressed) {

        // qDebug() << "pos():" << event->pos();
        // qDebug() << "scenePos():" << event->scenePos();
        // qDebug() << "m_pos:" << m_pos;

        // update internally stored scene position of the item
        // (corrected by gripping distance to the center pos)
        QPointF new_pos = event->scenePos() - event->pos();
        if (m_pos != new_pos) {
            setScenePos(new_pos);
        }
        update();
    }

    QGraphicsItem::mouseMoveEvent(event); // move the item normally
}