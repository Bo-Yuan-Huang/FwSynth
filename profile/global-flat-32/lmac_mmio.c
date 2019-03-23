// LMAC Core 2 + MMIO/DMA software model

#include "config.h"
#include <stdbool.h>

typedef bool BOOL_T;
#define BOOL_VALUE_TRUE true
#define BOOL_VALUE_FALSE false

/* Lmac Core 2 architectural states */
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

/* Lmac MMIO architectural states */
// inputs
// ADDR_T     MMIO_ADDR_IN
// PKT_DATA_T MMIO_DATA_IN
// BOOL_T     MMIO_WR

// states
PKT_DATA_T MMIO_LONG_0;
ADDR_T MMIO_COUNTER;

bool LmacDecodeTx(/* input */ BOOL_T TX_WE, /* input */ PHY_DATA_T TX_DATA) {
  return (TX_WE && (TX_FIFO_FULL == BOOL_VALUE_FALSE));
}

void LmacUpdateTx(/* input */ BOOL_T TX_WE, /* input */ PHY_DATA_T TX_DATA) {
  // helpers
  BOOL_T is_size_qwrd = (TX_PKT_WR_CNT == 0X0);
  BOOL_T is_last_qwrd = (TX_PKT_WR_CNT == 0X1);
  BOOL_T tx_complete = (TX_PKT_RD_CNT == 0x0);
  PHY_DATA_T in_data_val = TX_DATA;

  // TX_FIFO_FULL
  BOOL_T TX_FIFO_FULL_nxt = (is_last_qwrd || !tx_complete);

  // TX_PKT_WR_CNT
  ADDR_T down_shift = in_data_val >> 3;
  BOOL_T has_remainder = (down_shift != (down_shift >> 3));
  ADDR_T size_measured_in_steps = has_remainder ? (down_shift + 1) : down_shift;
  ADDR_T TX_PKT_WR_CNT_nxt =
      is_size_qwrd ? size_measured_in_steps : (TX_PKT_WR_CNT - 1);
  // TX_BUFF_WR_PTR
  ADDR_T TX_BUFF_WR_PTR_inc = TX_BUFF_WR_PTR + 1;
  ADDR_T TX_BUFF_WR_PTR_nxt = is_last_qwrd ? 0 : TX_BUFF_WR_PTR_inc;

  // TX_PKT_RD_CNT
  PHY_DATA_T size_load_from_buffer = TX_FIFO_BUFF[TX_BUFF_RD_PTR];
  ADDR_T TX_PKT_RD_CNT_nxt = is_last_qwrd ? size_load_from_buffer : 0;

  // TX_BUFF_RD_PTR
  ADDR_T TX_BUFF_RD_PTR_nxt = 0;

  // TX_FIFO_BUFF
  // memory update should be a function call, work around here

  /* Update states */
  TX_FIFO_BUFF[TX_BUFF_WR_PTR] = in_data_val;
  TX_FIFO_FULL = TX_FIFO_FULL_nxt;
  TX_PKT_WR_CNT = TX_PKT_WR_CNT_nxt;
  TX_BUFF_WR_PTR = TX_BUFF_WR_PTR_nxt;
  TX_PKT_RD_CNT = TX_PKT_RD_CNT_nxt;
  TX_BUFF_RD_PTR = TX_BUFF_RD_PTR_nxt;

  return;
}

bool LmacMmioDecodeInstr0(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 && MMIO_COUNTER == 0);
}

bool LmacMmioDecodeInstr1(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  return (MMIO_ADDR_IN == 0xff00 && MMIO_WR == 0x1 && MMIO_COUNTER == 1);
}

void LmacMmioUpdateInstr0(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  MMIO_LONG_0 = MMIO_DATA_IN;
  MMIO_COUNTER = MMIO_COUNTER + 1;
  return;
}

void LmacMmioUpdateInstr1(/* input */ ADDR_T MMIO_ADDR_IN,
                          /* input */ PKT_DATA_T MMIO_DATA_IN,
                          /* input */ BOOL_T MMIO_WR) {
  MMIO_COUNTER = 0;

  PHY_DATA_T chunk = MMIO_LONG_0;
  chunk = (chunk << PKT_DATA_BIT_WIDTH) || MMIO_DATA_IN;

  // trigger LmacTx (or other instructions in the future)
  if (LmacDecodeTx(0x1 /* TX_WE */, chunk /* TX_DATA */)) {
    LmacUpdateTx(0x1 /* TX_WE */, chunk /* TX_DATA */);
  }

  return;
}

void LmacMmioWriteL(/* input */ PKT_DATA_T data_in) {
  ADDR_T addr_in = 0xff00;

  if (LmacMmioDecodeInstr0(addr_in, data_in, true)) {
    LmacMmioUpdateInstr0(addr_in, data_in, true);
  } else if (LmacMmioDecodeInstr1(addr_in, data_in, true)) {
    LmacMmioUpdateInstr1(addr_in, data_in, true);
  }

  return;
}

