#include "AES.h"
#include <stdint.h>

uint32_t* out_c_bytes;

void AES(uint32_t* c_in_state, uint32_t* c_in_key) {

  for (int i = 0; i < 4; i++) {
    out_c_bytes[i] = c_in_state[i];
  }

  // execute
  encrypt_128_key_expand_inline_no_branch(out_c_bytes, c_in_key);

  return;
}

