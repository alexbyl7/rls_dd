#include "widget.h"
#include "drawer.h"
#include "reader.h"

#include <QApplication>
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  qRegisterMetaType<DataContainer>("DataContainer");

  Drawer drawer;
  QThread threadDrawer;

  Reader reader;
  QThread threadReader;

  Widget wgt(drawer);

  QObject::connect( &drawer, SIGNAL(updateScreen(QPixmap*)),
                    &wgt,    SLOT(onUpdateScreen(QPixmap*)) );

  QObject::connect( &reader, SIGNAL(eventDataReady(DataContainer)),
                    &drawer, SLOT(process(DataContainer)));

  drawer.moveToThread (&threadDrawer);
  threadDrawer.start();

  reader.moveToThread (&threadReader);
  threadReader.start();

  //double time_one_line_ms = 10.0;
  drawer.startProcess();

  wgt.show();

  return a.exec();
}
