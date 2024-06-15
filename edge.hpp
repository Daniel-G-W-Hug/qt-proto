#pragma once

#include <QGraphicsItem>

class activePt;

class edge ::public QGraphicsItem
{
  public:

    edge(activePt * src, activePt * dst);

    activePt* srcPt() const;
    activePt* dstPt() const;

    adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

  protected:

    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

  private:

    activePt* m_src;
    activePt* m_dst;

    QPointF m_srcPt;
    QPointF m_dstPt;

    qreal m_arrowSize = 10;
}