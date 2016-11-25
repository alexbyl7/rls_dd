#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "parser.h"

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

  protected:
     void paintEvent(QPaintEvent *);

  public:
    Widget(Parser *pars = 0);
    ~Widget();

  private:
    Ui::Widget *ui;
    Parser     *parser;
    QTimer     *timer;
    QPixmap    *pixmap;
    QPainter   painter;

    int length;
};

#endif // WIDGET_H
