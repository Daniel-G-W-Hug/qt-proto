#pragma once

#include <QWidget>

class w_main : public QWidget {
    Q_OBJECT

  public:

    w_main(QWidget* parent = nullptr);

  protected:

    void paintEvent(QPaintEvent* event) override;
};