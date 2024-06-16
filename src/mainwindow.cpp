#include "mainwindow.hpp"
#include "w_active_pt.hpp"
#include "w_active_vec.hpp"

#include <QPainter>
#include <QPointF>
#include <QVBoxLayout>

static constexpr int WIDTH = 500;
static constexpr int HEIGHT = 500;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(0, 0, WIDTH, HEIGHT));

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    auto layout = new QVBoxLayout;
    layout->addWidget(view);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    active_pt* pt = new active_pt(QPointF(120, 100));
    scene->addItem(pt);

    scene->addLine(0, 0, 120, 100);

    active_vec* v = new active_vec(QPointF(130, 120), QPointF(270, 160));
    scene->addItem(v);
}
