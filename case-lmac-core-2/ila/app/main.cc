// main.cc
//
// Entry point for the executable to generate LMAC-CORE-2 ILA.
//
// References:
// - https://github.com/lewiz-support/LMAC_CORE2

#include <iostream>
#include <lmac_core_2/lmac_core_2.h>

int main() {

  ExportLmacCore2ToFile("lmac_core_2.json");

  return 0;
}
