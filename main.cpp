#include "widget.h"
#include "drawer.h"

#include <QApplication>
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Drawer drawer;
  QThread thread;
  Widget wgt(drawer);

  QObject::connect( &drawer, SIGNAL(updateScreen(QPixmap*)),
                    &wgt,    SLOT(onUpdateScreen(QPixmap*)) );

  drawer.moveToThread (&thread);
  thread.start();

  //double time_one_line_ms = 10.0;
  drawer.startProcess();

  wgt.show();

  return a.exec();
}
