#include "interference.h"

InterferenceProcessor::InterferenceProcessor()
{

}

bool InterferenceProcessor::checkInterference(const DATA_PACKAGE_AD& data)
{
  MeanAndDev md;

  bool have_int = false;

  for (int beg = 100; beg < 4000; beg += 50) {
    md = calcMeanAndDev(&data.data.out_data.spectr[beg], 100);

    if ((md.mean > 100) && (md.dev < 5)) {
      have_int = true;
      cout << "beg = " << beg
           << ", line =" << data.data.line_pos.pos
           << ", m = " << md.mean
           << ", d =" << md.dev
           << endl;
    }
  }
  /*if (have_int)
    for (int i = 0; i < DATA_LEN_SPECTR_4K; i++) {
    }
*/

  return have_int;
}
