// template program for the LMAC transmit

#include "config.h"
#include "lmac_mmio.c"

/* LeWiz MAC core 2 transmit packet -- FW template
 *  - take in a packet (pkt_arr and pkt_size) as input
 *  - control the hardware module to move the packet to the abstracted PHY
 *    (phy_arr)
 */
void LmacTxTemplate(PKT_DATA_T* pkt_arr, ADDR_T pkt_num, uint32_t* syn_arr) {

  TX_FIFO_FULL = BOOL_VALUE_FALSE;
  TX_PKT_WR_CNT = 0;
  TX_BUFF_WR_PTR = 0;
  MMIO_COUNTER = 0;

  // start of the template
  // big-endian
  if (syn_arr[0] == 0) {

    for (ADDR_T i = 0; i < pkt_num; i += SCALE) {
      LmacMmioWriteL(pkt_arr[i + 0]);
      LmacMmioWriteL(pkt_arr[i + 1]);
    }

  } else { // little-endian

    for (ADDR_T i = 0; i < pkt_num; i += SCALE) {
      LmacMmioWriteL(pkt_arr[i + 1]);
      LmacMmioWriteL(pkt_arr[i + 0]);
    }
  }

  return;
}
