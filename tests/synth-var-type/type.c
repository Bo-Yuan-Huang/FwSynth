#include <stdbool.h>
#include <stdint.h>

#define BUFF_SIZE 5

uint32_t type_ref(uint32_t *arr, uint32_t a, uint32_t b) {
  arr[0] = a;
  arr[1] = b;

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  return arr[BUFF_SIZE - 1];
}

uint32_t type_free_bv(uint32_t *arr, uint32_t a, uint32_t b, uint32_t sbv0,
                      uint32_t sbv1, uint32_t sbv2) {
  if (sbv0 == 0) {
    arr[1] = (arr[0] != 0) ? a : arr[0];
  } else {
    arr[1] = (arr[0] != 0) ? b : arr[0];
  }

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  if (sbv1 == 0) {
    return arr[sbv2];
  } else {
    return arr[0];
  }
}

uint32_t type_lump_bv(uint32_t *arr, uint32_t a, uint32_t b, uint32_t *sbvs) {
  if (sbvs[0] == 0) {
    arr[1] = (arr[0] != 0) ? a : arr[0];
  } else {
    arr[1] = (arr[0] != 0) ? b : arr[0];
  }

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  if (sbvs[1] == 0) {
    return arr[sbvs[2]];
  } else {
    return arr[0];
  }
}

uint32_t type_free_bool(uint32_t *arr, uint32_t a, uint32_t b, bool sbit0,
                        bool sbit1, uint32_t sbv0) {
  if (sbit0) {
    arr[1] = (arr[0] != 0) ? a : arr[0];
  } else {
    arr[1] = (arr[0] != 0) ? b : arr[0];
  }

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  if (sbit1) {
    return arr[sbv0];
  } else {
    return arr[0];
  }
}

uint32_t type_lump_bool(uint32_t *arr, uint32_t a, uint32_t b, bool *sbits,
                        uint32_t *sbvs) {
  if (sbits[0]) {
    arr[1] = (arr[0] != 0) ? a : arr[0];
  } else {
    arr[1] = (arr[0] != 0) ? b : arr[0];
  }

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  if (sbits[1]) {
    return arr[sbvs[0]];
  } else {
    return arr[0];
  }
}

