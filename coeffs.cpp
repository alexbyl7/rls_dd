#include "coeffs.h"

#include <cmath>
#include <iostream>

using namespace std;

CoeffsEstimator::CoeffsEstimator():
  man_coeffs(0.8, 0.0, 0.7),
  auto_coeffs(0.8, 0.0, 0.7),
  mode(eCoeffsManual)
{
  max_ampl = 0;
}

void CoeffsEstimator::addRlsData(const DATA_PACKAGE_AD& data)
{
  for (int i = 0; i < DATA_LEN_SPECTR_4K; i++) {
    float x = data.data.out_data.spectr[i];

    if ((i < 500)||(x > 1e8)) continue;

    if (x > max_ampl)
      max_ampl = x;
  }
  cout << "max_ampl = " << max_ampl << endl;
}

const Coeffs& CoeffsEstimator::getCoeffs()
{
  switch(mode) {
    case eCoeffsManual: {
      return man_coeffs;
    }
    case eCoeffsAuto: {
      auto_coeffs.A = 1.0;
      auto_coeffs.B = 0.0;
      auto_coeffs.C = 2 * log(255)/log(max_ampl);

      cout << "C = " << auto_coeffs.C << endl;

      return auto_coeffs;
    }
    default:
      break;
  }
  return man_coeffs;
}
