// template program for the LMAC transmit

#include "config.h"
#include "lmac_mmio.c"
#include <stdint.h>

/* LeWiz MAC core 2 transmit packet -- FW template
 *  - take in a packet (pkt_arr and pkt_size) as input
 *  - control the hardware module to move the packet to the abstracted PHY
 *    (phy_arr)
 *  - return the first CRC field value --> proof of concept
 */
DATA_T LmacTxTemplate(PKT_DATA_T* pkt_arr, DATA_T pkt_size) {
  // PHY_DATA_T* phy_arr , uint32_t* svs) {

  // LMAC_MMIO_STS.LMAC_STS.TX_FIFO_BUFF = phy_arr;
  LMAC_MMIO_STS.LMAC_STS.TX_FIFO_BUFF = TX_FIFO_BUFF;

  // svs[0] = 0;

  // start of the template
#if 0
  if (svs[0] == 0) { // big-endian
#endif

  for (DATA_T i = 0; i < pkt_size; i += 8) {
    LmacMmioWriteByte(pkt_arr[i + 0]);
    LmacMmioWriteByte(pkt_arr[i + 1]);
    LmacMmioWriteByte(pkt_arr[i + 2]);
    LmacMmioWriteByte(pkt_arr[i + 3]);
    LmacMmioWriteByte(pkt_arr[i + 4]);
    LmacMmioWriteByte(pkt_arr[i + 5]);
    LmacMmioWriteByte(pkt_arr[i + 6]);
    LmacMmioWriteByte(pkt_arr[i + 7]);
  }

#if 0
  } else { // end-endian

    for (DATA_T i = 0; i < pkt_size; i += 8) {
      LmacMmioWriteByte(pkt_arr[i + 7]);
      LmacMmioWriteByte(pkt_arr[i + 6]);
      LmacMmioWriteByte(pkt_arr[i + 5]);
      LmacMmioWriteByte(pkt_arr[i + 4]);
      LmacMmioWriteByte(pkt_arr[i + 3]);
      LmacMmioWriteByte(pkt_arr[i + 2]);
      LmacMmioWriteByte(pkt_arr[i + 1]);
      LmacMmioWriteByte(pkt_arr[i + 0]);
    }
  }
#endif

#if 0
  DATA_T crc = lmac_mmio_sts.lmac_sts.lmac_Tx_crc_sts.TX_CRC_VALUE;
  return crc;
#endif
  return 0;
}
