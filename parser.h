#ifndef DATA_DRAWER_H
#define DATA_DRAWER_H

#define DATA_OFFSET 0

#include <QObject>
#include <fstream>

#include "rls_header.h"

class Parser : public QObject
{
  Q_OBJECT

public:
  Parser();
  ~Parser() {}

  void openFile();
  DATA_PACKAGE_AD getData();

private:
  DATA_PACKAGE_AD rls_data;
  std::ifstream file;
  unsigned length;

public slots:
  void stop() {}

signals:
  void finished();
};

#endif // DATA_DRAWER_H
