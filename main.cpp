#include "widget.h"
#include "parser.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Parser *p = new Parser();
  Widget w(p);
  w.show();

  return a.exec();
}
