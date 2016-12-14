#ifndef COEFFS_H
#define COEFFS_H

#include "rls_header.h"
#include "tools.h"

#include <iostream>

using namespace std;


struct Coeffs {
  Coeffs(double a, double b, double c):
    A(a), B(b), C(c)
  {}

  double A, B, C;
};

enum CoeffsModes {
  eCoeffsAuto,
  eCoeffsManual
};

enum CoeffsEstStates {
  eCE_FindMaxAmpl,
  eCE_FormHist,
  eCE_CalcCoeffs,
  eCE_Formed
};

class CoeffsEstimator
{
  public:
    CoeffsEstimator();

    const Coeffs& getCoeffs();
    void processRlsData(const DATA_PACKAGE_AD&);

    void setManA(int a) {man_coeffs.A = (double)a / 100;}
    void setManB(int b) {man_coeffs.B = (double)b;}
    void setManC(int c) {man_coeffs.C = (double)c / 100;}
    void setCoeffsMode(CoeffsModes m)
    {
      mode = m;
      cout << "Mode changed to " << mode << endl;
    }

  private:
    //std::deque<DATA_PACKAGE_AD> data_cont;
    float    max_ampl;
    unsigned data_counter;
    unsigned high_level_percent;
    double   k_lin;

    unsigned hist[HIST_INTERVALS_NUM];
    double   hist_int;
    double   high_level_amp;
    unsigned counts_in_hist;

    CoeffsModes     mode;
    CoeffsEstStates state;

    Coeffs man_coeffs,
           auto_coeffs;
};

#endif // COEFFS_H
