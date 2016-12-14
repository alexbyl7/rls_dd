#ifndef INTERFERENCE_H
#define INTERFERENCE_H

#include "rls_header.h"
#include "tools.h"

class InterferenceProcessor
{
  public:
    InterferenceProcessor();

    bool checkInterference(const DATA_PACKAGE_AD& data);
};

#endif // INTERFERENCE_H
