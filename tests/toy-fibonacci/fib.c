#include <stdint.h>

#define BUFF_SIZE 10

// input arr with size 10
uint32_t fib_ref(uint32_t *arr, uint32_t a, uint32_t b) {
  arr[0] = a;
  arr[1] = b;
  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  uint32_t res = arr[9];
  return res;
}

uint32_t cmd_add(uint32_t a, uint32_t b) { return a + b; }

uint32_t cmd_sub(uint32_t a, uint32_t b) { return a - b; }

uint32_t fib_syn(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sym_0,
                 uint32_t sym_1, uint32_t sym_2, uint32_t sym_3,
                 uint32_t sym_4) {

  arr[sym_0] = a;
  arr[sym_1] = b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    if (sym_2 == 0) {
      arr[i] = cmd_add(arr[i - sym_3], arr[i - sym_4]);
    } else {
      arr[i] = cmd_sub(arr[i - sym_3], arr[i - sym_4]);
    }
  }

  return arr[9];
}

uint32_t fib_com(uint32_t *arr, uint32_t a, uint32_t b) {
  arr[0] = b;
  arr[1] = a;
  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  uint32_t res = arr[9];
  return res;
}

