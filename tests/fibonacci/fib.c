#include <stdint.h>

#define BUFF_SIZE 5
#define PROFILE_ARRAY 1

uint32_t fib_ref(uint32_t* arr, uint32_t a, uint32_t b) {
  arr[0] = a;
  arr[1] = b;
  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return arr[BUFF_SIZE - 1];
}

uint32_t cmd_add(uint32_t a, uint32_t b) { return a + b; }

uint32_t cmd_sub(uint32_t a, uint32_t b) { return a - b; }

uint32_t fib_syn(uint32_t* arr, uint32_t a, uint32_t b, uint32_t* svs) {
  arr[0] = (svs[0] == 0) ? a : b;
  arr[1] = (svs[1] == 0) ? a : b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
#ifdef PROFILE_ARRAY
    if (svs[2] == 0) {
      arr[i] = cmd_add(arr[i - svs[3]], arr[i - svs[4]]);
    } else {
      arr[i] = cmd_sub(arr[i - svs[3]], arr[i - svs[4]]);
    }
#else
    if (svs[2] == 0) {
      arr[i] = cmd_add(arr[i - 1], arr[i - 2]);
    } else {
      arr[i] = cmd_sub(arr[i - 1], arr[i - 2]);
    }
#endif
  }

#ifdef PROFILE_ARRAY
  return arr[svs[5]];
#else
  return arr[svs[3]];
#endif
}

#if 0
uint32_t fib_arr(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sym_0,
                 uint32_t sym_1, uint32_t sym_2) {
  arr[sym_0] = a;
  arr[sym_1] = b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - sym_2] + arr[i - 2];
  }

  return arr[9];
}

uint32_t fib_arr_bound(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sym_0,
                       uint32_t sym_1, uint32_t sym_2) {
  arr[sym_0] = a;
  arr[sym_1] = b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    if (i - sym_2 < BUFF_SIZE) {
      arr[i] = arr[i - sym_2] + arr[i - 2];
    }
  }

  return arr[9];
}

uint32_t fib_arr_bound_loose(uint32_t *arr, uint32_t a, uint32_t b,
                             uint32_t sym_0, uint32_t sym_1, uint32_t sym_2) {
  arr[sym_0] = a;
  arr[sym_1] = b;

  if (sym_2 < BUFF_SIZE) {
    for (uint32_t i = 2; i < BUFF_SIZE; i++) {
      arr[i] = arr[i - sym_2] + arr[i - 2];
    }
  }

  return arr[9];
}
uint32_t fib_arr_top(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sym_0,
                     uint32_t sym_1, uint32_t sym_2) {
  arr[sym_0] = a;
  arr[sym_1] = b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  return arr[sym_2];
}

uint32_t fib_sel(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sym_0,
                 uint32_t sym_1, uint32_t sym_2) {
  arr[0] = (sym_0 == 0) ? a : b;
  arr[1] = (sym_1 == 0) ? a : b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    if (sym_2 == 0) {
      arr[i] = arr[i - 1] + arr[i - 2];
    } else {
      arr[i] = arr[i - 1] - arr[i - 2];
    }
  }

  return arr[9];
}

uint32_t fib_type(uint32_t *arr, uint32_t a, uint32_t b, bool sbl_0, bool sbl_1,
                  bool sbl_2) {
  arr[0] = (sbl_0 == 0) ? a : b;
  arr[1] = (sbl_1 == 0) ? a : b;

  for (uint32_t i = 2; i < BUFF_SIZE; i++) {
    if (sbl_2 == 0) {
      arr[i] = arr[i - 1] + arr[i - 2];
    } else {
      arr[i] = arr[i - 1] - arr[i - 2];
    }
  }

  return arr[9];
}
#endif
