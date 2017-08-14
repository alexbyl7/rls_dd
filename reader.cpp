#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
  udp = new QUdpSocket(this);
  udp->bind(2424);

  connect(udp, SIGNAL(readyRead()), SLOT(read()));

  connect(&timer, SIGNAL(timeout()), SLOT(output()));

  timer.start(1000);
}

void Reader::read()
{
  while (udp->hasPendingDatagrams()) {

    DATA_PACKAGE_AD data;
    udp->readDatagram((char*)&data, sizeof(DATA_PACKAGE_AD));
    data_cont.push_back(data);
  }
}

void Reader::output()
{
  printf("data_cont size = %d\n", data_cont.size());

  emit eventDataReady(data_cont);
  data_cont.clear();
}
