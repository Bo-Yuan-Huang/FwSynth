#include "lmac_reference.c"
#include "lmac_template.c"
#include <stdio.h>

int main() {
  ADDR_T pkt_num = 16;
  PKT_DATA_T pkt_arr[16];

  pkt_arr[0] = 0;
  pkt_arr[1] = 2;
  pkt_arr[2] = 0;
  pkt_arr[3] = 8;
  pkt_arr[4] = 1;
  pkt_arr[5] = 0;
  pkt_arr[6] = 1;
  pkt_arr[7] = 0;
  pkt_arr[8] = 0;
  pkt_arr[9] = 0;
  pkt_arr[10] = 0;
  pkt_arr[11] = 0;
  pkt_arr[12] = 0;
  pkt_arr[13] = 0;
  pkt_arr[14] = 0;
  pkt_arr[15] = 0;

  uint32_t syn_arr[1];
  syn_arr[0] = 0;

  LmacTxReference(pkt_arr, pkt_num);
  LmacTxTemplate(pkt_arr, pkt_num, syn_arr);

  for (int i = 0; i < 8; i++) {
    printf("%d: %lu %lu\n", i, g_PHY_ARR[i], TX_FIFO_BUFF[i]);
  }

  return 0;
}
