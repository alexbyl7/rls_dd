#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser()
{
  openFile();
}

void Parser::openFile() {
// file.open("/home/byldin/work/polinom/superpos/build/RLS_Data_New.b",
 file.open("/home/byldin/work/polinom/superpos/build/RLS_1_Data.b",
// file.open("/home/byldin/work/polinom/RLS_4_fileRLS_FFT_001.b",
 // file.open("/media/byldin/204E-EA5F/rls_data/regs/RLS_3_fileRLS_FFT_001.b",
 // file.open("/windows/Work/IANS/polinom/meteo_interf/RLS_4_fileRLS_FFT_001.b",
    ios_base::binary | ios_base::in);

  file.seekg (0, file.end);
  length = file.tellg();
  cout << "length = " << length << endl;
  file.seekg (DATA_OFFSET * sizeof(DATA_PACKAGE_AD), file.beg);
}

DATA_PACKAGE_AD Parser::getData()
{
  file.read((char*)&rls_data, sizeof(DATA_PACKAGE_AD));

#if 0
  unsigned *pa = (unsigned*)&rls_data;
  unsigned us_ = sizeof(DATA_PACKAGE_AD) / sizeof(unsigned);
  for (unsigned u=0; u<us_; u++, pa++) {
    printf("  %08X", *pa);
    if (u && (7 == u % 8))
      printf("\n");
  }

  cout << "size = "     << rls_data.size
       << ", time = "     << rls_data.time
       << ", sender = "   << rls_data.sender
       << ", type = "     << rls_data.type
       << ", mode = "     << rls_data.mode
       << ", line_num = " << rls_data.data.line_pos.line_num
       << ", pos = "      << rls_data.data.line_pos.pos
       << endl;

  for (unsigned i = 0; i < 4096; ++i)
    if (rls_data.data.out_data.spectr[i] > 0)
      cout << ", ampl = " << rls_data.data.out_data.spectr[i] << endl;

#endif

  return rls_data;
}
