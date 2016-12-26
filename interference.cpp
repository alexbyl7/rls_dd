#include "interference.h"

InterferenceProcessor::InterferenceProcessor()
{

}

InterfInfoContainer InterferenceProcessor::getInterfInfo(const DATA_PACKAGE_AD& data)
{
  InterfInfoContainer ic;

  ic = checkInterf(data, eLongInterf, 1000, 30, 0.03);

  if (ic.empty())
    ic = checkInterf(data, eShortInterf, 200, 30, 0.03);

  return ic;
}

InterfInfoContainer InterferenceProcessor::checkInterf(
       const DATA_PACKAGE_AD& data, InterfType type,
       double window_length, double min_mean, double md_coeff)
{
  InterfInfoContainer info_cont;
  InterfInfo info;
  MeanAndDev md;
  md.mean = md.dev = 0;

  bool int_on_prev_step = false,
       int_on_cur_step  = false;

  for (int beg = 100; beg < DATA_LEN_SPECTR_4K - window_length;
                                beg += window_length / 2) {
    md = calcMeanAndDev(&data.data.out_data.spectr[beg], window_length);

    int_on_prev_step = int_on_cur_step;
    int_on_cur_step = (md.mean > min_mean) && (md.dev < md.mean * md_coeff);

    if (int_on_cur_step) {
      if (md.mean > info.mean) info.mean = md.mean;
      if (md.dev  < info.dev)  info.dev  = md.dev;
      if (!int_on_prev_step) {
        info.begin_dist = beg;
        info.type = type;
      }
    }
    if ((int_on_prev_step && !int_on_cur_step) ||
         (int_on_cur_step && beg > DATA_LEN_SPECTR_4K - 3*window_length/2)) {
      info.end_dist = beg + window_length / 2;
      info_cont.push_back(info);
      int_on_prev_step = false;
      md.mean = 0;
      md.dev = 100;
    }
  }

  return info_cont;
}
