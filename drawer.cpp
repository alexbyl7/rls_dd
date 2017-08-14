#include "drawer.h"
#include <iostream>

using namespace std;

Drawer::Drawer():
  coeffs(0.7, 0.0, 0.8)
{
  pixmap = new QPixmap(600, 600);
  pixmap->fill(Qt::white);

  counter = DATA_OFFSET;

  line_width = 30;
  resetScaleToDefault();

  parser = new Parser();

 // connect(&timer, SIGNAL(timeout()), SLOT(process()));
}

Drawer::~Drawer()
{
  delete pixmap;
  delete parser;
}

void Drawer::startProcess()
{
  timer.start(200.0);
}

void Drawer::stopProcess()
{
  timer.stop();
}

void Drawer::process(DataContainer data_cont)
{
  painter.begin(pixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(center);
  painter.scale(scale_factor, scale_factor);

  //for (int n = 0; n < 200; ++n) {

  //cout << "Buf_size = " << udp->readBufferSize() << endl;

 // while (udp->hasPendingDatagrams()) {
   for (DataContainer::iterator it = data_cont.begin(); it != data_cont.end(); ++it) {

    counter++;

    DATA_PACKAGE_AD data;

    //data = parser->getData();

    //QByteArray

    //udp->readDatagram((char*)&data, sizeof(DATA_PACKAGE_AD));

    data = *it;

    InterfInfoContainer info_cont = interf_proc.getInterfInfo(data);

#if 0
    // Cut interference
    for (InterfInfoContainer::iterator it = info_cont.begin();
                                     it != info_cont.end(); ++it) {
      double begin, end;
      if (it->type == eLongInterf) {
        begin = 0; end = DATA_LEN_SPECTR_4K;
      } else {
        begin = it->begin_dist; end = it->end_dist;
      }
      for (int i = begin; i < end; ++i)
        data.data.out_data.spectr[i] = 0;
    }
#endif

    coeffs_est.processRlsData(data);

    if (!info_cont.empty()) cout << "counter = " << counter << endl;

    painter.rotate(360.0 * data.data.line_pos.pos / MAX_LINE_POS);

    Coeffs cfs = coeffs_est.getCoeffs();

    int step = 1;
    for (int i = 0; i < DATA_LEN_SPECTR_4K; i++) {
      float x = data.data.out_data.spectr[i];
      int col = pow(cfs.A * x + cfs.B, cfs.C);

      if (col < 0)   col = 0;
      if (col > 255) col = 255;

      painter.setPen( QPen(QColor(col,col,col), line_width, Qt::SolidLine) );

      painter.drawLine(i*step,i*step, (i+1)*step,(i+1)*step);
    }

#if 0
    // Draw interference
    for (InterfInfoContainer::iterator it = info_cont.begin();
            it != info_cont.end(); ++it) {

      switch(it->type) {
        case eShortInterf:
          cout << data.data.line_pos.line_num << " line, from "
               << it->begin_dist << " to " << it->end_dist << endl;

          painter.setPen(QPen(Qt::yellow, 2*line_width, Qt::SolidLine));
          painter.drawLine(it->begin_dist*step, it->begin_dist*step,
                           it->end_dist*step,   it->end_dist*step);
          break;
        case eLongInterf:
          cout << data.data.line_pos.line_num << " line, all dist " << endl;

          painter.setPen(QPen(Qt::red, 2*line_width, Qt::SolidLine));
          painter.drawLine(0,0, DATA_LEN_SPECTR_4K,DATA_LEN_SPECTR_4K);
          break;
        default: break;
      }
    }
#endif

    painter.rotate(- 360.0 * data.data.line_pos.pos / MAX_LINE_POS);
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
