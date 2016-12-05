#ifndef COEFFS_H
#define COEFFS_H

#include "rls_header.h"

struct Coeffs {
  Coeffs(double a,
         double b,
         double c)
  {
    A = a; B = b; C = c;
  }

  double A, B, C;
};

enum CoeffsMode {
  eCoeffsManual,
  eCoeffsAuto
};

class CoeffsEstimator
{
  public:
    CoeffsEstimator();

    const Coeffs& getCoeffs();
    void addRlsData(const DATA_PACKAGE_AD&);

    void setManA(int a) {man_coeffs.A = (double)a/100;}
    void setManB(int b) {man_coeffs.B = (double)b;}
    void setManC(int c) {man_coeffs.C = (double)c/100;}
    void setCoeffsMode(CoeffsMode m) {mode = m;}

  private:
    CoeffsMode mode;
    Coeffs     man_coeffs,
               auto_coeffs;

};

#endif // COEFFS_H
