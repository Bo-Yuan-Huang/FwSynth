//#include "seahorn/seahorn.h"
#include "lmac_reference.c"
#include "lmac_template.c"
#include <stdio.h>

#define N 16

extern PKT_DATA_T nd();

int main() {

  PKT_DATA_T pkt[N];
  ADDR_T num = N;
  PHY_DATA_T out1[N / 2];
  PHY_DATA_T out2[N / 2];
  uint32_t syn[1];
  //syn[0] = nd();
  syn[0] = 0;

  for (uint32_t i = 0; i < N; i++) {
    pkt[i] = nd();
  }

#if 0
  LmacTxReference(pkt, num, out1);
#else
  LmacTxTemplate(pkt, num, out1, syn);
#endif

  LmacTxTemplate(pkt, num, out2, syn);

  for (uint32_t i = 0; i < N / 2; i++) {
    if (out1[i] != out2[i]) {
      printf("%lu != %lu\n", out1[i], out2[i]);
    }
  }

  printf("Compare %d entries\n", N);

  return 0;
};

int __seahorn_get_value_i32(int idx, int* arr, int bound) {
  return arr[idx];
}
