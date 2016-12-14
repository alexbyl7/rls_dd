#ifndef TOOLS_H
#define TOOLS_H

#define HIST_INTERVALS_NUM 100
#define DATA_ACCUM_NUM 800
#define DATA_MIN_DIST 500
#define DATA_MAX_DIST 2000
#define SIGMA_NOISE 10000

#include <iostream>
#include <cmath>

using namespace std;

struct MeanAndDev {
  double mean;
  double dev;
};

inline const MeanAndDev calcMeanAndDev(const float a[], unsigned size)
{
  MeanAndDev md;
  md.mean = 0;
  md.dev = 0;

  for (unsigned i = 0; i < size; ++i) {
    md.mean += a[i];
  }
  if (size) md.mean /= size;

  for (unsigned i = 0; i < size; ++i) {
    md.dev += (a[i] - md.mean) * (a[i] - md.mean);
  }
  md.dev = sqrt(md.dev);
  if (size) md.dev /= size;

  return md;
}

#endif // TOOLS_H
