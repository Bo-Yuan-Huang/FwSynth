#include "stdint.h"

uint32_t g;
uint32_t v;

void ref(uint32_t x, uint32_t y) {
  v = x + y;
  return;
}

extern void update(uint32_t x, uint32_t y);

void imp(uint32_t x, uint32_t y) {
  update(x, y);
  return;
}

int miter(uint32_t x, uint32_t y) {
  ref(x, y);
  imp(x, y);
  return g - v;
}
