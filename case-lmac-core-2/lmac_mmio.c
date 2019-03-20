// LMAC Core 2 + MMIO/DMA software model

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint64_t ADDR_T;
typedef bool BOOL_T;
#define BOOL_VALUE_TRUE true
#define BOOL_VALUE_FALSE false

struct LmacArchStates {
  // inputs
  // BOOL_t     TX_WE
  // PHY_DATA_T TX_DATA

  // states
  BOOL_T TX_FIFO_FULL;
  ADDR_T TX_PKT_WR_CNT;
  ADDR_T TX_PKT_RD_CNT;
  ADDR_T TX_BUFF_WR_PTR;
  ADDR_T TX_BUFF_RD_PTR;
  PHY_DATA_T* TX_FIFO_BUFF;
};

struct LmacMmioArchStates {
  // inputs
  // ADDR_T     MMIO_ADDR_IN
  // PKT_DATA_T MMIO_DATA_IN
  // BOOL_T     MMIO_WR

  // states
  PKT_DATA_T MMIO_BYTE_0;
  PKT_DATA_T MMIO_BYTE_1;
  PKT_DATA_T MMIO_BYTE_2;
  PKT_DATA_T MMIO_BYTE_3;
  PKT_DATA_T MMIO_BYTE_4;
  PKT_DATA_T MMIO_BYTE_5;
  PKT_DATA_T MMIO_BYTE_6;
  DATA_T MMIO_COUNTER;

  struct LmacArchStates LMAC_STS;
};

struct LmacMmioArchStates LMAC_MMIO_STS;

#if 0
bool LmacDecodeTx(/* state */ struct LmacMmioArchStates* sts,
                  /* state */ PHY_DATA_T* LMAC_TX_FIFO_BUFF,
                  /* input */ BOOL_T tx_we, /* input */ PHY_DATA_T tx_data) {
  return (tx_we && (sts->lmac_sts.TX_FIFO_FULL == false));
}
#endif

bool LmacDecodeTx(/* input */ BOOL_T TX_WE, /* input */ PHY_DATA_T TX_DATA) {
  return (TX_WE && (LMAC_MMIO_STS.LMAC_STS.TX_FIFO_FULL == BOOL_VALUE_FALSE));
}

void LmacUpdateTx(/* input */ BOOL_T TX_WE, /* input */ PHY_DATA_T TX_DATA) {
  // helpers
  BOOL_T is_size_qwrd = (LMAC_MMIO_STS.LMAC_STS.TX_PKT_WR_CNT == 0X0);
  BOOL_T is_last_qwrd = (LMAC_MMIO_STS.LMAC_STS.TX_PKT_WR_CNT == 0X1);
  BOOL_T tx_complete = (LMAC_MMIO_STS.LMAC_STS.TX_PKT_RD_CNT == 0x0);
  PHY_DATA_T in_data_val = TX_DATA;

  // TX_FIFO_FULL
  BOOL_T TX_FIFO_FULL_nxt = (is_last_qwrd || !tx_complete);

  // TX_PKT_WR_CNT
  ADDR_T down_shift = in_data_val >> 3;
  BOOL_T has_remainder = (down_shift != (down_shift >> 3));
  ADDR_T size_measured_in_steps = has_remainder ? (down_shift + 1) : down_shift;
  ADDR_T TX_PKT_WR_CNT_nxt = is_size_qwrd
                                 ? size_measured_in_steps
                                 : (LMAC_MMIO_STS.LMAC_STS.TX_PKT_WR_CNT - 1);
  // TX_BUFF_WR_PTR
  ADDR_T TX_BUFF_WR_PTR_inc = LMAC_MMIO_STS.LMAC_STS.TX_BUFF_WR_PTR + 1;
  ADDR_T TX_BUFF_WR_PTR_nxt = is_last_qwrd ? 0 : TX_BUFF_WR_PTR_inc;

  // TX_PKT_RD_CNT
  PHY_DATA_T size_load_from_buffer =
      LMAC_MMIO_STS.LMAC_STS
          .TX_FIFO_BUFF[LMAC_MMIO_STS.LMAC_STS.TX_BUFF_RD_PTR];
  ADDR_T TX_PKT_RD_CNT_nxt = is_last_qwrd ? size_load_from_buffer : 0;

  // TX_BUFF_RD_PTR
  ADDR_T TX_BUFF_RD_PTR_nxt = 0;

  // TX_FIFO_BUFF
  // memory update should be a function call, work around here

  /* Update states */
  LMAC_MMIO_STS.LMAC_STS.TX_FIFO_BUFF[LMAC_MMIO_STS.LMAC_STS.TX_BUFF_WR_PTR] =
      in_data_val;
  LMAC_MMIO_STS.LMAC_STS.TX_FIFO_FULL = TX_FIFO_FULL_nxt;
  LMAC_MMIO_STS.LMAC_STS.TX_PKT_WR_CNT = TX_PKT_WR_CNT_nxt;
  LMAC_MMIO_STS.LMAC_STS.TX_BUFF_WR_PTR = TX_BUFF_WR_PTR_nxt;
  LMAC_MMIO_STS.LMAC_STS.TX_PKT_RD_CNT = TX_PKT_RD_CNT_nxt;
  LMAC_MMIO_STS.LMAC_STS.TX_BUFF_RD_PTR = TX_BUFF_RD_PTR_nxt;

  return;
}

bool LmacMmioDecodeInstr0(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 0);
}

bool LmacMmioDecodeInstr1(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 1);
}

bool LmacMmioDecodeInstr2(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 2);
}

bool LmacMmioDecodeInstr3(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 3);
}

bool LmacMmioDecodeInstr4(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 4);
}

bool LmacMmioDecodeInstr5(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 5);
}

bool LmacMmioDecodeInstr6(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 6);
}

bool LmacMmioDecodeInstr7(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 &&
          LMAC_MMIO_STS.MMIO_COUNTER == 7);
}

#if 0
void LmacMmioUpdateInstr0(struct LmacMmioArchStates* sts, PHY_DATA_T addr_in,
                          PKT_DATA_T data_in, bool wr) {
  sts->byte_0 = data_in;
  sts->counter = sts->counter + 1;
  return;
}
#endif

void LmacMmioUpdateInstr0(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_0 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr1(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_1 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr2(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_2 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr3(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_3 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr4(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_4 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr5(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_5 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr6(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_BYTE_6 = MMIO_DATA_IN;
  LMAC_MMIO_STS.MMIO_COUNTER = LMAC_MMIO_STS.MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr7(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  LMAC_MMIO_STS.MMIO_COUNTER = 0;

  PHY_DATA_T chunk = 0;
  chunk = LMAC_MMIO_STS.MMIO_BYTE_0;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_1;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_2;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_3;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_4;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_5;
  chunk = (chunk << 8) || LMAC_MMIO_STS.MMIO_BYTE_6;
  chunk = (chunk << 8) || MMIO_DATA_IN;
#if 0
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_0 << 56);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_1 << 48);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_2 << 40);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_3 << 32);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_4 << 24);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_5 << 16);
  chunk = chunk || (LMAC_MMIO_STS.MMIO_BYTE_6 << 8);
  chunk = chunk || MMIO_DATA_IN;
#endif

#if 1
  // trigger LmacTx (or other instructions in the future)
  if (LmacDecodeTx(0x1 /* TX_WE */, chunk /* TX_DATA */)) {
    LmacUpdateTx(0x1 /* TX_WE */, chunk /* TX_DATA */);
  }
#endif

  return;
}

void LmacMmioWriteByte(/* input */ PKT_DATA_T data_in) {
  ADDR_T addr_in = 0xff00;
#if 1
  if (LmacMmioDecodeInstr0(addr_in, data_in, true)) {
    LmacMmioUpdateInstr0(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr1(addr_in, data_in, true)) {
    LmacMmioUpdateInstr1(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr2(addr_in, data_in, true)) {
    LmacMmioUpdateInstr2(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr3(addr_in, data_in, true)) {
    LmacMmioUpdateInstr3(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr4(addr_in, data_in, true)) {
    LmacMmioUpdateInstr4(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr5(addr_in, data_in, true)) {
    LmacMmioUpdateInstr5(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr6(addr_in, data_in, true)) {
    LmacMmioUpdateInstr6(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr7(addr_in, data_in, true)) {
    LmacMmioUpdateInstr7(addr_in, data_in, true);
  }
#endif

  return;
}

