#include "coeffs.h"

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

CoeffsEstimator::CoeffsEstimator():
  man_coeffs(0.8, 0.0, 0.7),
  auto_coeffs(0.8, 0.0, 0.7),
  mode(eCoeffsManual),
  state(eCE_FindMaxAmpl)
{
  high_level_percent = 75;
  k_lin = 0.5;

  max_ampl = 0;
  high_level_amp = 0;
  hist_int = 0;
  counts_in_hist = 0;
  data_counter = 0;

  memset(hist, 0, sizeof(hist));
}

void CoeffsEstimator::processRlsData(const DATA_PACKAGE_AD& data)
{
  data_counter++;

  switch(state) {
    case eCE_FindMaxAmpl: {
      for (int i = DATA_MIN_DIST; i < DATA_MAX_DIST; i++) {
        float x = data.data.out_data.spectr[i];

        if ((x < SIGMA_NOISE) && (x > 1e8)) continue;

        if (x > max_ampl) max_ampl = x;
      }
      if (data_counter >= DATA_ACCUM_NUM) {
        data_counter = 0;
        hist_int = (max_ampl - SIGMA_NOISE) / HIST_INTERVALS_NUM;

        cout << "max_ampl = " << max_ampl << endl;

        state = eCE_FormHist;
      }
      break;
    }
    case eCE_FormHist: {
      for (int i = DATA_MIN_DIST; i < DATA_MAX_DIST; i++) {
        float x = data.data.out_data.spectr[i];

        if ((x < SIGMA_NOISE) && (x > 1e8)) continue;

        for (unsigned i = 0; i < HIST_INTERVALS_NUM; ++i) {
          if ((x > (SIGMA_NOISE +   i   * hist_int)) &&
              (x < (SIGMA_NOISE + (i+1) * hist_int))) {
            counts_in_hist++;
            hist[i]++;
            break;
          }
        }
      }
      if (data_counter >= DATA_ACCUM_NUM) {
        data_counter = 0;
        state = eCE_CalcCoeffs;
      }
      break;
    }
    case eCE_CalcCoeffs: {
      unsigned sum = 0;

      for (unsigned i = 0; i < HIST_INTERVALS_NUM; ++i)
        cout << hist[i] << endl;

      for (unsigned i = 0; i < HIST_INTERVALS_NUM; ++i) {
        sum += hist[i];
        cout << "sum = " << sum << " " << " "
             << counts_in_hist << " "
             <<  hist[0] << " " << hist[1] << " " << hist[2] << endl;

        if (sum > (counts_in_hist) * high_level_percent / 100)
        {
          high_level_amp = (i+1) * hist_int;

          cout << i << " " << high_level_amp << endl;

          auto_coeffs.A = 1.0 / k_lin;
          auto_coeffs.B = 0.0;
          auto_coeffs.C = 2 * log(255)/log(high_level_amp / k_lin);

          cout << auto_coeffs.A << " "
               << auto_coeffs.B << " "
               << auto_coeffs.C << endl;

          state = eCE_Formed;
          break;
        }
      }
      break;
    }
    case eCE_Formed: {
      break;
    }
  }
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
