#pragma once

#include <QGraphicsView>

class w_gview : public QGraphicsView {
    Q_OBJECT

  public:

    w_gview(QWidget* parent = nullptr);

    void itemMoved();

  public slots:
    void zoomIn();
    void zoomOut();

  protected:

    void keyPressEvent(QKeyEvent* event) override;
    // void wheelEvent(QWheelEvent* event) override;

    // void paintEvent(QPaintEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void scaleView(qreal scaleFactor);

    // private:
    //
    // stuff to be added later
    //
};