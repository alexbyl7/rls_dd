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
  connect(ui->checkBox, SIGNAL(clicked(bool)),
                  this, SLOT (changeCoeffsMode(bool)));

  connect(ui->horizontalSlider_A, SIGNAL(sliderMoved(int)),
                         &drawer, SLOT (setCoeff_A(int)));
  connect(ui->horizontalSlider_B, SIGNAL(sliderMoved(int)),
                         &drawer, SLOT (setCoeff_B(int)));
  connect(ui->horizontalSlider_C, SIGNAL(sliderMoved(int)),
                         &drawer, SLOT (setCoeff_C(int)));

  connect(ui->spinBox_linewidth, SIGNAL(valueChanged(int)),
                        &drawer, SLOT (setLineWidth(int)));

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

void Widget::changeCoeffsMode(bool is_auto)
{
  if (is_auto)
    drawer.setCoeffsAuto();
  else
    drawer.setCoeffsManual();
  ui->horizontalSlider_A->setEnabled(!is_auto);
  ui->horizontalSlider_B->setEnabled(!is_auto);
  ui->horizontalSlider_C->setEnabled(!is_auto);
}
