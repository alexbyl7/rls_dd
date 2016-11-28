#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QWheelEvent>
#include <QtMath>

#include "parser.h"

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
    Widget(Parser *pars = 0);
    ~Widget();

  public slots:
    void clearScreen();

  private:
    Ui::Widget *ui;
    Parser     *parser;
    QTimer     *timer;
    QPixmap    *pixmap;
    QPainter   painter;

    int length;
    double fact_scale;
};

#endif // WIDGET_H
