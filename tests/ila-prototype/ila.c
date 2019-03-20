#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BUFF_SIZE 64
#define ADDR_BIT_WIDTH 32
#define DATA_BIT_WIDTH 32

/* Architectural states
 *  - arr: memory of size BUFF_SIZE
 *  - ptr: bv type state
 *  - sum: bv type state
 *  - div: bv type state
 *  - inp: bv type input
 */

struct ArchSts {
  uint32_t ptr;
  uint32_t sum;
  uint32_t div;
};

void RESET(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {
  sts->ptr = 0;
  sts->sum = 0;
  return;
}

void SET_DIV(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {
  sts->div = inp;
  return;
}

void ADD(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {

  sts->sum = sts->sum + arr[sts->ptr];
  sts->ptr = sts->ptr + 1;
  return;
}

void SUB(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {
  sts->sum = sts->sum - arr[sts->ptr];
  sts->ptr = sts->ptr + 1;
  return;
}

void DIV(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {
  sts->sum = sts->sum >> sts->div;
  return;
}

void MUL(uint32_t* arr, struct ArchSts* sts, uint32_t inp) {
  sts->sum = sts->sum << sts->div;
  return;
}

uint32_t template(uint32_t* arr, uint32_t div, const uint32_t* svs) {
  struct ArchSts sts;

  RESET(arr, &sts, div + svs[0]);

  SET_DIV(arr, &sts, div + svs[1]);

#if 1
  if (svs[3] == 0) {
    for (uint32_t i = 0; i < BUFF_SIZE; i++) {
      ADD(arr, &sts, div);
    }
  } else {
    for (uint32_t i = 0; i < BUFF_SIZE; i++) {
      SUB(arr, &sts, div);
    }
  }
#else
  for (uint32_t i = 0; i < BUFF_SIZE; i++) {
    if (svs[3] == 0) {
      ADD(arr, &sts, div);
    } else {
      SUB(arr, &sts, div);
    }
  }
#endif

  if (svs[2] == 0) {
    DIV(arr, &sts, div);
  } else {
    MUL(arr, &sts, div);
  }

  return sts.sum;
}

uint32_t answer(uint32_t* arr, uint32_t div) {
  struct ArchSts sts;

  RESET(arr, &sts, div);

  SET_DIV(arr, &sts, div);

  for (uint32_t i = 0; i < BUFF_SIZE; i++) {
    ADD(arr, &sts, div);
  }
  DIV(arr, &sts, div);

  return sts.sum;
}

uint32_t reference(uint32_t* arr, uint32_t div) {

  uint32_t sum = 0;

  for (uint32_t i = 0; i < BUFF_SIZE; i++) {
    sum += arr[i];
  }

  uint32_t res = sum >> div;

  return res;
}

int main() {
  uint32_t div = 16;
  uint32_t arr[BUFF_SIZE];
  for (uint32_t i = 0; i < BUFF_SIZE; i++) {
    arr[i] = 0;
  }
  arr[1] = 2147483648;

  uint32_t ref_res = reference(arr, div);
  uint32_t tem_res = answer(arr, div);

#if 1
  printf("%u\n", ref_res);
  printf("%u\n", tem_res);
#endif

  return 0;
}
