#include "coeffs.h"

CoeffsEstimator::CoeffsEstimator():
  man_coeffs(0.5, 0.0, 0.5),
  auto_coeffs(0.5, 0.0, 0.5),
  mode(eCoeffsManual)
{

}

void CoeffsEstimator::addRlsData(const DATA_PACKAGE_AD& data)
{

}

const Coeffs& CoeffsEstimator::getCoeffs()
{
  switch(mode) {
    case eCoeffsManual: {
      return man_coeffs;
    }
    case eCoeffsAuto: {
      return auto_coeffs;
    }
    default:
      break;
  }
  return man_coeffs;
}
