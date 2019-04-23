#include "seahorn/seahorn.h"
#include "lmac_reference.c"

#define N 32

extern PKT_DATA_T nd();

int main () {

  PKT_DATA_T pkt[N];
  ADDR_T num = N;
  PHY_DATA_T out1[N / 2];
  PHY_DATA_T out2[N / 2];

  pkt[0] = 0;
  pkt[1] = N;
  for (int i = 2; i < N; i++) {
    pkt[i] = nd();
  }

  LmacTxReference (pkt, num, out1);
  LmacTxReference (pkt, num, out2);

  for (int i = 0; i < N / 2; i++) {
    sassert(out1[i] == out2[i]);
  }
 
  return 0;
}
