#include <stdint.h>

uint32_t foo(uint32_t a) { return a * 6; }

uint32_t simple(uint32_t x, uint32_t y) {
  uint32_t a = x + y;
  uint32_t b = a * 5;
  uint32_t c = foo(b);
  return c >> 2;
}
