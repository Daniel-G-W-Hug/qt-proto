#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>

class active_pt : public QGraphicsItem {
  public:

    active_pt(QPointF const& pos, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
    [[nodiscard]] QRectF boundingRect() const override;

  protected:

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  private:

    QPointF m_pos; // position of the center point of the item (as scene position)

    bool m_mouse_hover{false};   // mouse is hovering over the item
    bool m_mouse_pressed{false}; // mouse is pressed (for dragging the item)
};