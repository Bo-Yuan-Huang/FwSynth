#include "lmac_reference.c"
#include "lmac_template.c"

#include "verif_config.h"

uint32_t miter(PKT_DATA_T* pkt_arr, ADDR_T pkt_num) {

  uint32_t syn_arr[1];
  syn_arr[0] = 0;

  LmacTxReference(pkt_arr, pkt_num);
  LmacTxTemplate(pkt_arr, pkt_num, syn_arr);

  bool res = true;

  for (int i = 0; i < (PKT_NUM / SCALE); i++) {
    res &= (g_PHY_ARR[i] == TX_FIFO_BUFF[i]);
  }

  if (res == false) {
    return 1;
  }

  return 0;
};
