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

  ui->graphicsView->setScene(&scene);
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
         ui->graphicsView->scale(1.1, 1.1);
       }
       else {
         ui->graphicsView->scale(0.9, 0.9);
       }
     }
     default:
       break;
   }
   event->accept();
}

void Widget::onUpdateScreen(QPixmap* pixmap)
{
  scene.clear();
  scene.addPixmap(*pixmap);
}
