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
    setWindowTitle(tr("Graphics View Test"));

    activePt* ap1 = new activePt(this);
    activePt* ap2 = new activePt(this);
    scene->addItem(ap1);
    scene->addItem(ap2);
    ap1->setPos(10, 10);
    ap2->setPos(50, 50);

    edge* e = new edge(ap1, ap2);
    scene->addItem(e);
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

void w_gview::itemMoved()
{
    if (!timerId) timerId = startTimer(1000 / 25);
}

void w_gview::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);

    // QList<Node*> nodes;
    // const QList<QGraphicsItem*> items = scene()->items();
    // for (QGraphicsItem* item : items) {
    //     if (Node* node = qgraphicsitem_cast<Node*>(item)) nodes << node;
    // }

    // for (Node* node : std::as_const(nodes))
    //     node->calculateForces();

    ap->calculate();

    bool itemsMoved = false;
    if (ap->advance()) itemsMoved = true;
    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void w_gview::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4, sceneRect.width() - 4,
                    sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void w_gview::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            ap->moveBy(0, -20);
            break;
        case Qt::Key_Down:
            ap->moveBy(0, 20);
            break;
        case Qt::Key_Left:
            ap->moveBy(-20, 0);
            break;
        case Qt::Key_Right:
            ap->moveBy(20, 0);
            break;
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void w_gview::scaleView(qreal scaleFactor)
{
    qreal factor =
        transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100) return;

    scale(scaleFactor, scaleFactor);
}


void w_gview::zoomIn() { scaleView(qreal(1.2)); }

void w_gview::zoomOut() { scaleView(1 / qreal(1.2)); }