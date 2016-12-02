#include "drawer.h"
#include <iostream>

using namespace std;

Drawer::Drawer():
  coeffs(0.7, 0.0, 0.8)
{
  pixmap = // new QPixmap(ui->label->width(), ui->label->height());
    new QPixmap(600, 600);
  pixmap->fill(Qt::white);
  resetScaleToDefault();

  parser = new Parser();

  connect(&timer, SIGNAL(timeout()), SLOT(process()));
}

Drawer::~Drawer()
{
  delete pixmap;
  delete parser;
}

void Drawer::startProcess(double ms)
{
  timer.start(ms);
}

void Drawer::process()
{
  painter.begin(pixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(center);
  painter.scale(scale_factor, scale_factor);

  double line_width = 30; //ui->spinBox_linewidth->value();

  DATA_PACKAGE_AD data = parser->getData();
  painter.rotate(360.0 * data.data.line_pos.pos / 4096);

  // Для сжатия:
 /* double a = (double)ui->horizontalSlider_A->value() / 100,
         b = (double)ui->horizontalSlider_B->value(),
         c = (double)ui->horizontalSlider_C->value() / 100;
*/

  int step = 1;
  for (int i = 0; i < DATA_LEN_SPECTR_4K_16B; i++) {
    float x = data.data.out_data.spectr[i];
    int col = pow(coeffs.A * x + coeffs.B, coeffs.C);
    if (col > 255) col = 255;
    painter.setPen( QPen(QColor(col,col,col), line_width, Qt::SolidLine) );
    painter.drawLine(i*step,i*step, (i+1)*step,(i+1)*step);
  }

  emit updateScreen(pixmap);

  painter.end();

}

void Drawer::clearScreen()
{
  pixmap->fill();
}

void Drawer::resetScaleToDefault()
{
  center = QPoint(pixmap->width() / 2, pixmap->height() / 2);
  scale_factor = 0.1;
}
