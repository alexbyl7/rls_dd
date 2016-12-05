#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser()
{
  openFile();
}

void Parser::openFile() {
  file.open("/home/byldin/work/polinom/RLS_1_fileRLS_FFT_001.b",
 // file.open("/media/byldin/204E-EA5F/rls_data/regs/RLS_3_fileRLS_FFT_001.b",
    ifstream::binary);

  file.seekg (0, file.end);
  length = file.tellg();
  file.seekg (0, file.beg);
}

const DATA_PACKAGE_AD& Parser::getData()
{
  DATA_PACKAGE_AD rls_data;
  file.read((char*)&rls_data, sizeof(DATA_PACKAGE_AD));
  return rls_data;
}
