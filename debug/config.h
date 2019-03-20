#ifndef LMAC_CONFIG_H__
#define LMAC_CONFIG_H__

#include <stdint.h>

/* design configuration */

// packet buffer
#define PKT_BYTE_NUM 64
#define PKT_DATA_T uint8_t
#define PKT_DATA_BIT_WIDTH 8
#define PKT_DATA_NUM ((PKT_BYTE_NUM * 8) / PKT_DATA_BIT_WIDTH)

// abstracted PHY buffer
#define PHY_BYTE_NUM PKT_BYTE_NUM
#define PHY_DATA_T uint64_t
#define PHY_DATA_BIT_WIDTH 64
#define PHY_DATA_NUM ((PHY_BYTE_NUM * 8) / PHY_DATA_BIT_WIDTH)

// general type
#define DATA_T PHY_DATA_T

// uninterpreted function of calculating CRC field
DATA_T ComputeCrc(DATA_T x) { return x; }

#endif // LMAC_CONFIG_H__
