#ifndef INTERFERENCE_H
#define INTERFERENCE_H

#include <vector>

#include "rls_header.h"
#include "tools.h"

enum InterfType {
  eShortInterf,
  eLongInterf
};

struct InterfInfo
{
  InterfType type;
  double mean,
         dev;
  double begin_dist,
         end_dist;
};
typedef std::vector<InterfInfo> InterfInfoContainer;

class InterferenceProcessor
{
  public:
    InterferenceProcessor();

    InterfInfoContainer getInterfInfo(const DATA_PACKAGE_AD&);

  private:
    InterfInfoContainer checkInterf(const DATA_PACKAGE_AD&, InterfType,
                                    double, double, double);
};

#endif // INTERFERENCE_H
