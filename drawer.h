#ifndef DRAWER_H
#define DRAWER_H

#include <QThread>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "parser.h"
#include "coeffs.h"

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
    void setCoeffsAuto() {auto_coeffs = true;}
    void setCoeffsManual() {auto_coeffs = false;}

  public slots:
    void process();
    void clearScreen();
    void resetScaleToDefault();

    void setCoeff_A(int a) {coeffs.A = (double)a/100;}
    void setCoeff_B(int b) {coeffs.B = (double)b;}
    void setCoeff_C(int c) {coeffs.C = (double)c/100;}

    void setLineWidth(int w) {line_width = w;}

  private:
    Parser   *parser;
    QPixmap  *pixmap;
    QPainter painter;
    QTimer   timer;

    QPoint center;
    Coeffs coeffs;
    CoeffsEstimator coeffs_est;

    double scale_factor;
    int    line_width;
    bool   auto_coeffs;
};

#endif // DRAWER_H
