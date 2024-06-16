#pragma once

#include "w_active_pt.hpp"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>

class active_vec : public QGraphicsItem {

  public:

    active_vec(QPointF const& beg, QPointF const& end, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
    [[nodiscard]] QRectF boundingRect() const override;

    void setScenePos_beg(QPointF const& pos);
    void setScenePos_end(QPointF const& pos);
    QPointF scenePos_beg();
    QPointF scenePos_end();

  protected:

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  private:

    QPointF m_beg;
    QPointF m_end;

    active_pt* m_pt_beg; // active_pt at starting position of the item (as scene position)
    active_pt* m_pt_end; // active_pt at end position of the item (as scene position)

    bool m_mouse_hover{false};     // mouse is hovering over the item
    bool m_mouse_l_pressed{false}; // left button mouse is pressed
    bool m_mouse_r_pressed{false}; // right button mouse is pressed
};