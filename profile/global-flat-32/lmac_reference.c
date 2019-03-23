// reference program for the LMAC transmit

#include "config.h"

// global variable
PHY_DATA_T* g_PHY_ARR;

/* LeWiz MAC core 2 transmit packet
 *  - take in a packet (pkt_arr and pkt_size) as input
 *  - move the packet to the abstracted PHY (phy_arr)
 */
void LmacTxReference(PKT_DATA_T* pkt_arr, ADDR_T pkt_num) {

  // move the packet, one-byte at a time, to the abstract PHY
  ADDR_T pkt_idx = 0;
  ADDR_T phy_idx = 0;

  for (; pkt_idx < pkt_num;) {
    PHY_DATA_T qwrd = 0;

    // accumulate byte into qword
    for (ADDR_T i = 0; i < SCALE; i++) {
      // big-endian
      qwrd = (qwrd << PKT_DATA_BIT_WIDTH) + pkt_arr[pkt_idx + i];
    }

    // write to abstracted PHY
    g_PHY_ARR[phy_idx] = qwrd;

    // update pointers
    pkt_idx += SCALE;
    phy_idx += 1;
  }

  return;
}

