#include "widget.h"
#include "ui_widget.h"

#include <iostream>

using namespace std;

Widget::Widget(Parser *pars) :
  ui(new Ui::Widget),
  parser(pars)
{
  ui->setupUi(this);

  pixmap = new QPixmap(ui->label->width(), ui->label->height());
  pixmap->fill(Qt::white);
  length = qMin(pixmap->width(), pixmap->height()) / 3;

  fact_scale = 0.1;

  connect(ui->pushButton, SIGNAL (released()), this, SLOT (clearScreen()));

  //timer = new QTimer(this);
  //connect(timer, SIGNAL(timeout()), SLOT(update()));
  //timer->start(1000);
}

Widget::~Widget()
{
  delete parser;
  delete timer;
  delete pixmap;
  delete ui;
}

void Widget::paintEvent(QPaintEvent*) {
  painter.begin(pixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(pixmap->width() / 2, pixmap->height() / 2);

  double s = ui->doubleSpinBox_scale->value();
  painter.scale(fact_scale, fact_scale);
  double line_width = ui->spinBox_linewidth->value();

  DATA_PACKAGE_AD data = parser->getData();
  painter.rotate(360.0 * data.data.line_pos.pos / 4096);

  // Для сжатия:
  double a = (double)ui->horizontalSlider_A->value() / 100,
         b = (double)ui->horizontalSlider_B->value(),
         c = (double)ui->horizontalSlider_C->value() / 100;

  int step = 1;
  for (int i = 0; i < DATA_LEN_SPECTR_4K_16B; i++) {
    float x = data.data.out_data.spectr[i];
    int col = pow(a*x+b, c);
    if (col > 255) col = 255;
    painter.setPen( QPen(QColor(col,col,col), line_width, Qt::SolidLine) );
    painter.drawLine(i*step,i*step, (i+1)*step,(i+1)*step);
  }

  ui->label->setPixmap(*pixmap);

  painter.end();
}

void Widget::wheelEvent(QWheelEvent *event)
{
   int pos = 0;

   switch(event->modifiers())
   {
     case Qt::ControlModifier:
       fact_scale *= qPow(1.1, event->delta() / 100.0);
     default:
       break;
   }
   event->accept();
}

void Widget::clearScreen()
{
  pixmap->fill();
  cout << "Clear Screen" << endl;
}
