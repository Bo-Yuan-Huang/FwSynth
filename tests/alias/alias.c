// example to test array aliasing

#include <stdint.h>

struct Placeholder {
  uint32_t* buff_ptr;
  uint32_t bias;
} sts;

void UpdateBias(uint32_t addr_in, uint32_t data_in) {
  sts.bias = data_in;
  return;
}

void UpdateBuff(uint32_t addr_in, uint32_t data_in) {
  sts.buff_ptr[addr_in] = data_in + sts.bias;
  return;
}

void Target(uint32_t* arr, uint32_t a, uint32_t b) {
  sts.buff_ptr = arr;

  UpdateBias(0x0, b);

  for (uint32_t i = 0; i < 10; i++) {
    UpdateBuff(i, a);
  }
  return;
}

void Reference(uint32_t* arr, uint32_t a, uint32_t b) {
  for (uint32_t i = 0; i < 10; i++) {
    arr[i] = a + b;
  }
  return;
}

#if 0
void UpdateBias(struct Placeholder* sts, uint32_t addr_in, uint32_t data_in) {
  sts->bias = data_in;
}

void UpdateBuff(struct Placeholder* sts, uint32_t addr_in, uint32_t data_in) {
  sts->buff_ptr[addr_in] = data_in + sts->bias;
}

void Reference(uint32_t* arr, uint32_t a, uint32_t b) {

  // do we want to make the state as symbolic input or not
  // if not, we cannot allocate/parametrized the array size
  // can we try global variable?
  // the best option is to have global variable, and can be parameterized when
  // doing symbolic execution? this may incur much effort in symbolic execution
  // However, you need to pay this effort even when passing it as input

  sts->buff_ptr = arr;

  UpdateBias(a);

  uint32_t res = arr[0];
  return res;
}

uint32_t Target(uint32_t a, uint32_t b) {
  uint32_t c = a + b;
  uint32_t d = 2 * c;
  uint32_t res = BlackBox(d);
  return res;
}
#endif
