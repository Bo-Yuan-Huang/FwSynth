// example to test uninterpreted function

#include <stdint.h>

uint32_t BlackBox(uint32_t a) { return a; }

uint32_t Reference(uint32_t a, uint32_t b) {
  uint32_t c = 2 * a;
  uint32_t d = 2 * b;
  uint32_t e = c + d;
  uint32_t res = BlackBox(e);
  return res;
}

uint32_t Target(uint32_t a, uint32_t b) {
  uint32_t c = a + b;
  uint32_t d = 2 * c;
  uint32_t res = BlackBox(d);
  return res;
}

