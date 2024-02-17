#pragma once

#include <QWidget>

class w_active_pt : public QWidget {
    Q_OBJECT

  public:

    w_active_pt(QWidget* parent = nullptr);

  protected:

    void paintEvent(QPaintEvent* event) override;
};