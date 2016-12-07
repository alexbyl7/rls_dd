#ifndef DRAWER_H
#define DRAWER_H

#include <QThread>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include <iostream>

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
    void setCoeffsMode(CoeffsModes m) {coeffs_est.setCoeffsMode(m);}
    void setCoeffsManual() {auto_coeffs = false;}

  public slots:
    void process();
    void clearScreen();
    void resetScaleToDefault();

    void setCoeff_A(int a) {coeffs_est.setManA(a);}
    void setCoeff_B(int b) {coeffs_est.setManB(b);}
    void setCoeff_C(int c) {coeffs_est.setManC(c);}

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
