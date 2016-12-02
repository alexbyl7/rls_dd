#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>

#include "drawer.h"

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

  protected:
     void paintEvent(QPaintEvent *);
     void wheelEvent(QWheelEvent *);

  public:
    Widget(Drawer& drw);
    ~Widget();

  public slots:
    void onUpdateScreen(QPixmap*);

  private:
    Ui::Widget *ui;
    Drawer& drawer;
};

#endif // WIDGET_H
