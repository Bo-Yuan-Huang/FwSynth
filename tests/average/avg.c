#include <stdint.h>

uint32_t avg_ref(uint32_t a, uint32_t b) {
  uint32_t sum = a + b;
  uint32_t avg = sum / 2;
  return avg;
}

uint32_t cmd_add(uint32_t a, uint32_t b) {
  uint32_t sum = a + b;
  return sum;
}

uint32_t cmd_div(uint32_t a, uint32_t b) {
  uint32_t res = a / b;
  return res;
}

uint32_t avg_imp(uint32_t a, uint32_t b) {
  uint32_t sum = cmd_add(a, b);
  uint32_t avg = cmd_div(sum, 2);
  return avg;
}

uint32_t avg_syn(uint32_t a, uint32_t b, uint32_t cmd1, uint32_t cmd2) {
  uint32_t sum = 0;
  if (cmd1 == 1) {
    sum = cmd_add(a, b);
  } else {
    sum = cmd_div(sum, 2);
  }

  uint32_t res = 0;
  if (cmd2 == 1) {
    res = cmd_add(a, b);
  } else {
    res = cmd_div(sum, 2);
  }

  return res;
}
