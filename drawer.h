#ifndef DRAWER_H
#define DRAWER_H

#include <QThread>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "parser.h"

struct Coeffs {
  Coeffs(double a,
         double b,
         double c)
  {
    A = a; B = b; C = c;
  }

  double A, B, C;
};

class Drawer : public QObject
{
  Q_OBJECT
  signals:
    void updateScreen( QPixmap* );

  public:
    Drawer();
    ~Drawer();
    void startProcess(double);
    void increaseScaleFactor() {scale_factor += 0.01;}
    void decreaseScaleFactor() {scale_factor -= 0.01;}
    void setCenter(const QPoint& cent) {center = cent;}
    void setCoeffs(const Coeffs& coef) {coeffs = coef;}
    double getScaleFactor() {return scale_factor;}

  public slots:
    void process();
    void clearScreen();
    void resetScaleToDefault();

  private:
    Parser   *parser;
    QPixmap  *pixmap;
    QPainter painter;
    QTimer   timer;

    QPoint center;
    Coeffs coeffs;
    double scale_factor;
};

#endif // DRAWER_H
