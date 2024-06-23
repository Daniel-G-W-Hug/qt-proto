#include "w_active_vec.hpp"

static constexpr float MARGIN = 12.0;
static constexpr float ARROWSIZE = 12.0;

active_vec::active_vec(QPointF const& beg, QPointF const& end, QGraphicsItem* parent) :
    QGraphicsItem(parent), m_beg{beg}, m_end{end}, m_pt_beg{new active_pt(beg, this)},
    m_pt_end{new active_pt(end, this)}
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    connect(m_pt_beg, &active_pt::scenePosChanged, this, &active_vec::begScenePosChanged);
    connect(m_pt_end, &active_pt::scenePosChanged, this, &active_vec::endScenePosChanged);
}

void active_vec::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                       QWidget* widget)
{

    QColor const col_blue = QColor(0, 0, 255, 127);
    QColor const col_green = QColor(0, 255, 0, 127);
    QColor const col_red = QColor(255, 0, 0, 127);
    QColor const col_yel = QColor(255, 255, 0, 127);

    // draw in item coordinate system
    painter->save();

    // // draw bounding box (optional for testing)
    // painter->setPen(col_yel);
    // painter->setBrush(col_yel);
    // painter->drawRect(boundingRect());

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

    qreal dy = (m_end - m_beg).y();
    qreal dx = (m_end - m_beg).x();
    qreal angle = std::atan2(-dy, dx);

    QPainterPath arrowLine;
    arrowLine.moveTo(mapFromScene(m_beg));
    arrowLine.lineTo(mapFromScene(m_end) -
                     QPointF(sin(angle + M_PI / 2) * 0.6 * ARROWSIZE,
                             cos(angle + M_PI / 2) * 0.6 * ARROWSIZE));

    QPen pen = painter->pen();
    pen.setWidth(2);
    painter->drawPath(arrowLine);

    QPainterPath arrowHead;
    arrowHead.moveTo(mapFromScene(m_end));
    arrowHead.lineTo(mapFromScene(m_end) - QPointF(sin(angle + M_PI / 2.5) * ARROWSIZE,
                                                   cos(angle + M_PI / 2.5) * ARROWSIZE));
    arrowHead.lineTo(mapFromScene(m_end) -
                     QPointF(sin(angle + M_PI / 2) * 0.7 * ARROWSIZE,
                             cos(angle + M_PI / 2) * 0.7 * ARROWSIZE));
    arrowHead.lineTo(mapFromScene(m_end) -
                     QPointF(sin(angle + M_PI - M_PI / 2.5) * ARROWSIZE,
                             cos(angle + M_PI - M_PI / 2.5) * ARROWSIZE));
    arrowHead.closeSubpath();

    // from here on we want to draw with a small pen to get a pointy vector head
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawPath(arrowHead);

    // // draw shape (optional for testing)
    // painter->setPen(col_yel);
    // painter->setBrush(col_yel);
    // painter->drawPath(shape());

    painter->restore();
}

QRectF active_vec::boundingRect() const
{
    // give bounding box in item coordinate system
    return QRectF(mapFromScene(m_beg), mapFromScene(m_end)).normalized();
}

QPainterPath active_vec::shape() const
{

    qreal dy = (m_end - m_beg).y();
    qreal dx = (m_end - m_beg).x();
    qreal angle = std::atan2(-dy, dx);

    QPainterPath path;
    path.moveTo(mapFromScene(m_beg) -
                QPointF(sin(angle + M_PI / 2) * MARGIN, cos(angle + M_PI / 2) * MARGIN) -
                QPointF(-cos(angle + M_PI / 2) * MARGIN, sin(angle + M_PI / 2) * MARGIN));
    path.lineTo(mapFromScene(m_end) +
                QPointF(sin(angle + M_PI / 2) * MARGIN, cos(angle + M_PI / 2) * MARGIN) -
                QPointF(-cos(angle + M_PI / 2) * MARGIN, sin(angle + M_PI / 2) * MARGIN));
    path.lineTo(mapFromScene(m_end) +
                QPointF(sin(angle + M_PI / 2) * MARGIN, cos(angle + M_PI / 2) * MARGIN) +
                QPointF(-cos(angle + M_PI / 2) * MARGIN, sin(angle + M_PI / 2) * MARGIN));
    path.lineTo(mapFromScene(m_beg) -
                QPointF(sin(angle + M_PI / 2) * MARGIN, cos(angle + M_PI / 2) * MARGIN) +
                QPointF(-cos(angle + M_PI / 2) * MARGIN, sin(angle + M_PI / 2) * MARGIN));
    path.closeSubpath();
    return path;
}

void active_vec::setScenePos_beg(QPointF const& pos)
{
    if (pos != m_beg) {
        prepareGeometryChange();
        m_beg = pos;
        m_pt_beg->setScenePos(pos);
    }
}
void active_vec::setScenePos_end(QPointF const& pos)
{
    if (pos != m_end) {
        prepareGeometryChange();
        m_end = pos;
        m_pt_end->setScenePos(pos);
    }
}

QPointF active_vec::scenePos_beg() { return m_beg; }
QPointF active_vec::scenePos_end() { return m_end; }


void active_vec::begScenePosChanged(QPointF newPos)
{
    if (newPos != m_beg) {
        prepareGeometryChange();
        m_beg = newPos;
        update();
    }
}

void active_vec::endScenePosChanged(QPointF newPos)
{
    if (newPos != m_end) {
        prepareGeometryChange();
        m_end = newPos;
        update();
    }
}


void active_vec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_vec::hoverEnterEvent.";
    m_mouse_hover = true;
    update();
}

void active_vec::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)

    // qDebug() << "active_vec::hoverLeaveEvent.";
    m_mouse_hover = false;
    update();
}

void active_vec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_vec::mousePressEvent.";

    if (event->button() == Qt::LeftButton) {
        // qDebug() << "active_vec: Qt::LeftButton.";
        m_mouse_l_pressed = true;
    }
    if (event->button() == Qt::RightButton) {
        // qDebug() << "active_vec: Qt::RightButton.";
        m_mouse_r_pressed = true;
    }
    update();

    QGraphicsItem::mousePressEvent(event); // call default implementation
}

void active_vec::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_vec::mouseReleaseEvent.";

    // qDebug() << "active_vec::scenePos_beg():" << scenePos_beg();
    // qDebug() << "active_vec::scenePos_end():" << scenePos_end();

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

void active_vec::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug() << "active_vec::mouseMoveEvent.";

    if (m_mouse_l_pressed) {

        // qDebug() << "pos():" << event->pos();
        // qDebug() << "scenePos():" << event->scenePos();
        // qDebug() << "lastScenePos():" << event->lastScenePos();
        // qDebug() << "scenePos_beg():" << scenePos_beg();
        // qDebug() << "scenePos_end():" << scenePos_end();

        // update internally stored scene position of the item
        QPointF difference = event->scenePos() - event->lastScenePos();

        if (difference != QPointF(0, 0)) {
            // update positions of vector and active points
            setScenePos_beg(scenePos_beg() + difference);
            setScenePos_end(scenePos_end() + difference);
        }
        update();
    }

    QGraphicsItem::mouseMoveEvent(event); // move the item normally
}
