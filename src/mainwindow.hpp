#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QWidget>

class MainWindow : public QMainWindow {
  public:

    explicit MainWindow(QWidget* parent = nullptr);

  private:

    QGraphicsView* view;
    QGraphicsScene* scene;
};