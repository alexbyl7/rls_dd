#ifndef READER_H
#define READER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

#include "rls_header.h"

class Reader : public QObject
{
    Q_OBJECT
  public:
    explicit Reader(QObject *parent = 0);

  signals:
    void eventDataReady(DataContainer);

  protected slots:
    void read();
    void output();

  private:
    DataContainer data_cont;
    QTimer   timer;

    QUdpSocket* udp;
};

#endif // READER_H
