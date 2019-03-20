// reference program for the LMAC transmit

#include "config.h"
#include <stdint.h>

/* LeWiz MAC core 2 transmit packet
 *  - take in a packet (pkt_arr and pkt_size) as input
 *  - move the packet to the abstracted PHY (phy_arr)
 *  - return the first CRC field value --> proof of concept
 */
DATA_T LmacTxReference(PKT_DATA_T* pkt_arr, DATA_T pkt_size,
                       PHY_DATA_T* phy_arr) {

  // move the packet, one-byte at a time, to the abstract PHY
  DATA_T scale = (PHY_DATA_BIT_WIDTH / PKT_DATA_BIT_WIDTH);
  DATA_T pkt_idx = 0;
  DATA_T phy_idx = 0;

  for (; pkt_idx < pkt_size;) {
    PHY_DATA_T qwrd = 0;

    // accumulate byte into qword
    for (DATA_T i = 0; i < scale; i++) {
      // XXX big-endian?
      qwrd = (qwrd << PKT_DATA_BIT_WIDTH) + pkt_arr[pkt_idx + i];
    }

    // write to abstracted PHY
    phy_arr[phy_idx] = qwrd;

    // update pointers
    pkt_idx += scale;
    phy_idx += 1;
  }

#if 0
  // calculate the CRC value
  DATA_T sum = 0;
  // TODO
  DATA_T crc = ComputeCrc(sum);
  return crc;
#endif
  return 0;
}
