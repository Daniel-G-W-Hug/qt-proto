#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include <QRectF>
#include <QVariant>
#include <QWidget>

class edge;
class w_gview;

class activePt : public QGraphicsItem {
  public:

    activePt(w_gview* gview);

    void addEdge(edge* edge);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculate();
    bool advance();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

  protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  private:

    edge* m_edge;
    QPointF newPos;
    w_gview* gview;
};