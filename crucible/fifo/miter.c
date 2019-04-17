#include "lmac_reference.c"
#include "lmac_template.c"

uint32_t miter(PKT_DATA_T* pkt_arr, ADDR_T pkt_num) {

  uint32_t syn_arr[1];
  syn_arr[0] = 0;

  LmacTxReference(pkt_arr, pkt_num);
  LmacTxTemplate(pkt_arr, pkt_num, syn_arr);

#if 0
  bool res =
      (g_PHY_ARR[0] == TX_FIFO_BUFF[0]) && (g_PHY_ARR[1] == TX_FIFO_BUFF[1]) &&
      (g_PHY_ARR[2] == TX_FIFO_BUFF[2]) && (g_PHY_ARR[3] != TX_FIFO_BUFF[3]);
#else
  bool res = true;
  for (int i = 0; i < 8; i++) {
    res &= (g_PHY_ARR[i] == TX_FIFO_BUFF[i]);
  }
#endif

  if (res == false) {
    return 1;
  }

  return 0;
}
