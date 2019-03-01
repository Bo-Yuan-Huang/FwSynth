#include <stdint.h>

#define BUFF_SIZE 5

uint32_t array_ref(uint32_t *arr, uint32_t a) {
  // arr[0] symbolic
  if (arr[0] != 0)
    arr[1] = arr[0];
  else
    arr[1] = a;

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  return arr[BUFF_SIZE - 1];
}

uint32_t array_syn(uint32_t *arr, uint32_t a, uint32_t synv0, uint32_t synv1) {
  // arr[0] symbolic
  if (arr[0] != 0)
    arr[1] = arr[0];
  else
    arr[1] = (synv0 == 0) ? a : 0;

  for (int i = 2; i < BUFF_SIZE; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  if (synv1 == 0)
    return arr[BUFF_SIZE - 1];
  else
    return arr[0];
}

