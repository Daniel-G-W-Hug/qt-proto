// #include "w_main.hpp"

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>

#include <iostream>

static constexpr int PPI = 254;  // MacOS Screenresolution in dots per inch
static constexpr int PPCM = 100; // MacOS Screenresolution in dots per cm

int main(int argc, char* argv[])
{

    try {
        QApplication app(argc, argv);

        QGraphicsView view;

        QGraphicsScene* scene = new QGraphicsScene(&view);
        scene->setBackgroundBrush(Qt::yellow);

        // scale screen resolution to get 100 pixels / cm
        // scene->setSceneRect(QRectF(QPointF(-10, -10), QPointF(110, 110)));

        view.setScene(scene);
        // view.scale(1, -1);


        QGraphicsLineItem* line1 = new QGraphicsLineItem(0, 0, 100, 100);
        scene->addItem(line1);

        QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, 100, 100);
        scene->addItem(rect);

        QGraphicsRectItem* rect2 = new QGraphicsRectItem(0, 0, 100, 100);
        scene->addItem(rect2);

        rect2->setRotation(15);

        QGraphicsTextItem* text = new QGraphicsTextItem("Hello world!");
        scene->addItem(text);


        view.setWindowTitle("Template");
        view.resize(400, 400);
        view.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
}
