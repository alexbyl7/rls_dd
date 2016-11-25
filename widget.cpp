#include "widget.h"
#include "ui_widget.h"

#include <iostream>

using namespace std;

Widget::Widget(Parser *pars) :
  ui(new Ui::Widget),
  parser(pars)
{
  ui->setupUi(this);

  pixmap = new QPixmap(width(), height());
  pixmap->fill(Qt::white);
  length = qMin(pixmap->width(), pixmap->height()) / 3;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), SLOT(paintEvent()));
  timer->start(1000);
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
  double s = 0.1;
  painter.scale(s, s);

  DATA_PACKAGE_AD data = parser->getData();
  painter.rotate(360.0 * data.data.line_pos.pos / 4096);

  // Для сжатия:
  double a = 50,
         b = 0,
         c = 0.4;

  int step = 1;
  for (int i = 0; i < DATA_LEN_SPECTR_4K_16B; i++) {
    float x = data.data.out_data.spectr[i];
    int col = pow(a*x+b, c);
    if (col > 255) col = 255;
    painter.setPen( QPen(QColor(col,col,col), 30.0, Qt::SolidLine) );
    painter.drawLine(i*step,i*step, (i+1)*step,(i+1)*step);
  }

  ui->label->setPixmap(*pixmap);

  painter.end();
}
