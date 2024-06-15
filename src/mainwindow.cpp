#include "mainwindow.hpp"
#include "w_active_pt.hpp"
#include "w_myview.hpp"

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

    auto layout = new QVBoxLayout;
    layout->addWidget(view);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    myView* it = new myView(100, 100, 100, 20);
    scene->addItem(it);

    active_pt* pt = new active_pt(QPointF(120, 100));
    scene->addItem(pt);

    scene->addLine(0, 0, 120, 100);
}
