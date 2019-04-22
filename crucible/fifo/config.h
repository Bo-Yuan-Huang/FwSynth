#ifndef LMAC_CONFIG_H__
#define LMAC_CONFIG_H__

#include <stdint.h>

/* design configuration */
#include "pkt_num.h"

// packet buffer
#define PKT_DATA_T uint32_t
#define PKT_DATA_BIT_WIDTH 32

// abstracted PHY buffer
#define PHY_DATA_T uint64_t
#define PHY_DATA_BIT_WIDTH 64

// general type
#define ADDR_T uint32_t
#define SCALE (PHY_DATA_BIT_WIDTH / PKT_DATA_BIT_WIDTH)

#endif // LMAC_CONFIG_H__
