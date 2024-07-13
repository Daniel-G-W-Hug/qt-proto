//
// author: Daniel Hug, 2024
//

#include "active_plane.hpp"
#include "active_common.hpp"

#include <algorithm> // std::max

active_plane::active_plane(Coordsys* cs, w_Coordsys* wcs, active_pt* end,
                           QGraphicsItem* parent) :
    QGraphicsItem(parent), cs{cs}, wcs{wcs}, m_end{end}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    // setZValue(18);

    connect(wcs, &w_Coordsys::viewResized, m_end, &active_pt::viewChanged);

    connect(this, &active_plane::viewMoved, m_end, &active_pt::posChanged);
}

void active_plane::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{

    // clipping area is active area of coordsys
    painter->setClipRect(QRect(cs->x.nmin(), cs->y.nmax(), cs->x.nmax() - cs->x.nmin(),
                               cs->y.nmin() - cs->y.nmax()));


    // draw in item coordinate system
    painter->save();

    painter->setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine));
    painter->setBrush(Qt::black);

    if (m_mouse_hover && !m_mouse_l_pressed) {
        painter->setPen(QPen(QBrush(col_green), 2, Qt::SolidLine)); // hover: green
        painter->setBrush(col_green);
    }
    if (m_mouse_hover && m_mouse_l_pressed) {
        painter->setPen(QPen(QBrush(col_red), 2, Qt::SolidLine)); // pressed: red
        painter->setBrush(col_red);
    }

    QPointF beg_pos = QPointF(cs->x.a_to_w(0.0), cs->y.a_to_w(0.0));
    QPointF end_pos =
        QPointF(cs->x.a_to_w(scenePos_end().x()), cs->y.a_to_w(scenePos_end().y()));

    QPen pen = painter->pen();
    pen.setWidth(2);
    painter->drawPath(arrowLine(beg_pos, end_pos));

    // from here on we want to draw with a small pen to get a pointy vector head
    pen.setWidth(1);
    painter->drawPath(arrowHead(beg_pos, end_pos));

    pen.setWidth(2);
    painter->drawPath(
        planeLine(beg_pos, end_pos, std::max(cs->x.widget_size(), cs->y.widget_size())));

    // draw bounding box (optional for testing)
    // painter->setPen(col_yel);
    // painter->setBrush(col_yel);
    // painter->drawRect(boundingRect());

    // draw shape (optional for testing)
    // painter->setPen(col_yel);
    // painter->setBrush(col_yel);
    // painter->drawPath(shape());

    painter->restore();
}

QRectF active_plane::boundingRect() const
{
    // give bounding box in item coordinate system
    QPointF beg_pos = QPointF(cs->x.a_to_w(0.0), cs->y.a_to_w(0.0));
    QPointF end_pos =
        QPointF(cs->x.a_to_w(scenePos_end().x()), cs->y.a_to_w(scenePos_end().y()));
    return QRectF(beg_pos, end_pos).normalized();
}

QPainterPath active_plane::shape() const
{
    QPointF beg_pos = QPointF(cs->x.a_to_w(0.0), cs->y.a_to_w(0.0));
    QPointF end_pos =
        QPointF(cs->x.a_to_w(scenePos_end().x()), cs->y.a_to_w(scenePos_end().y()));
    return vectorShape(beg_pos, end_pos);
}

void active_plane::setScenePos_end(QPointF const& pos)
{
    if (pos != m_end->scenePos()) {
        prepareGeometryChange();
        m_end->setScenePos(pos);
    }
}

QPointF active_plane::scenePos_end() const { return m_end->scenePos(); }


void active_plane::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_plane::hoverEnterEvent.";
    m_mouse_hover = true;
    update();
}

void active_plane::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_plane::hoverLeaveEvent.";
    m_mouse_hover = false;
    update();
}

void active_plane::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_plane::mousePressEvent.";

    if (event->button() == Qt::LeftButton) {
        // qDebug() << "active_plane: Qt::LeftButton.";
        m_mouse_l_pressed = true;
    }
    if (event->button() == Qt::RightButton) {
        // qDebug() << "active_plane: Qt::RightButton.";
        m_mouse_r_pressed = true;
    }

    update();
    QGraphicsItem::mousePressEvent(event); // call default implementation
}

void active_plane::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_plane::mouseReleaseEvent.";

    // qDebug() << "active_plane::scenePos_beg():" << scenePos_beg();
    // qDebug() << "active_plane::scenePos_end():" << scenePos_end();

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

void active_plane::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_plane::mouseMoveEvent.";

    if (m_mouse_l_pressed) {

        QPointF delta = event->scenePos() - event->lastScenePos();

        if (delta != QPointF(0, 0)) {

            // qDebug() << "scenePos():" << event->scenePos();
            // qDebug() << "lastScenePos():" << event->lastScenePos();
            // qDebug() << "delta:" << delta;

            m_end->moveBy(delta.x(), delta.y());

            emit viewMoved();
        }
    }
}
