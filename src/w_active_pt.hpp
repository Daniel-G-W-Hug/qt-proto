#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QWidget>

class active_pt : public QGraphicsItem {

  public:

    enum class parent_type { none, pt, vec_beg, vec_end };

    active_pt(QPointF const& pos, parent_type parent_t = active_pt::parent_type::none,
              QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void setScenePos(QPointF const& pos);
    QPointF scenePos();

    bool has_parent() { return m_p_type != active_pt::parent_type::none; }
    void update_parent_geometry();

  protected:

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  private:

    QPointF m_pos; // position of the center point of the item (as scene position)

    bool m_mouse_hover{false};     // mouse is hovering over the item
    bool m_mouse_l_pressed{false}; // left button mouse is pressed
    bool m_mouse_r_pressed{false}; // right button mouse is pressed

    parent_type m_p_type;
};