#include "w_myview.hpp"

#include <QPainter>

static constexpr float ANCHOR_RADIUS = 10;

myView::myView(float xPos, float yPos, float width, float height, QGraphicsItem* parent) :
    QGraphicsItem(parent), _width(width), _height(height), _viewState(VIEW)
{

    setPos(xPos, yPos);

    setFlag(ItemIsMovable);

    auto diameter = 2 * ANCHOR_RADIUS;
    _anchor1.setRect(0, 0, diameter, diameter);
    _anchor2.setRect(width - diameter, 0, diameter, diameter);
}

void myView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                   QWidget* widget)
{

    auto diameter = 2 * ANCHOR_RADIUS;
    _anchor1.setRect(0, 0, diameter, diameter);
    _anchor2.setRect(_width - diameter, 0, diameter, diameter);

    // Anchor 1 and 2 coordinate
    auto c1 = _anchor1.center();
    auto c2 = _anchor2.center();

    painter->drawLine(static_cast<int>(c1.x()), static_cast<int>(c1.y()),
                      static_cast<int>(c2.x()), static_cast<int>(c2.y()));

    painter->drawEllipse(_anchor1);
    painter->drawEllipse(_anchor2);
}

QRectF myView::boundingRect() const
{
    return {0, 0, static_cast<qreal>(_width), static_cast<qreal>(_height)};
}

void myView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    _tapPoint = event->pos();

    auto cp1 = _anchor1.center(); // get center point of anchor 1
    auto cp2 = _anchor2.center(); // get center point of anchor 2

    // Anchor 1 clicked
    if (_anchor1.contains(_tapPoint)) {
        setTransformOriginPoint(cp2.x(), cp2.y()); // set rotation anchor to anchor 2
        _viewState = ANCHOR1;
    }
    // anchor 2 clicked
    else if (_anchor2.contains(_tapPoint)) {
        setTransformOriginPoint(cp1.x(), cp1.y()); // set rotation anchor to anchor 1
        _viewState = ANCHOR2;
    }
    // View clicked
    else {
        QGraphicsItem::mousePressEvent(event);
        _viewState = VIEW;
    }
}

void myView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    auto p = event->pos();

    switch (_viewState) {
        case ANCHOR1: {
            // calculate the angle of the rotation based on the mouse touch
            auto angle = qRadiansToDegrees(qAtan2(p.y() - _anchor2.y(), _width));
            setRotation(rotation() - angle); // rotate the item around anchor 2
            break;
        }
        case ANCHOR2: {
            // calculate the angle of the rotation based on the mouse touch
            auto angle = qRadiansToDegrees(qAtan2(p.y() - _anchor1.y(), _width));
            setRotation(rotation() + angle); // rotate the item around anchor 1
            break;
        }
        default:
            QGraphicsItem::mouseMoveEvent(event); // move the item normally
    }
}