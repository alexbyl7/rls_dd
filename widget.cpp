#include "widget.h"
#include "ui_widget.h"

#include <iostream>

using namespace std;

Widget::Widget(Drawer& drw) :
  ui(new Ui::Widget),
  drawer(drw)
{
  ui->setupUi(this);
  connect(ui->pushButtonClear, SIGNAL (released()),
                      &drawer, SLOT (clearScreen()));
  connect(ui->pushButtonDefaultScale, SIGNAL (released()),
                             &drawer, SLOT (resetScaleToDefault()));
}

Widget::~Widget()
{
  delete ui;
}

void Widget::paintEvent(QPaintEvent*) {
  /* void */
}

void Widget::wheelEvent(QWheelEvent *event)
{

   switch(event->modifiers())
   {
     case Qt::ControlModifier: {
       if (event->delta() > 0) {
         drawer.increaseScaleFactor();
       }
       else {
         drawer.decreaseScaleFactor();
       }
     }
     default:
       break;
   }
   event->accept();
}

void Widget::onUpdateScreen(QPixmap* pixmap)
{
  ui->label->setPixmap(*pixmap);
}
