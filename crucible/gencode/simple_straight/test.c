/* File: "test.c". Automatically generated by SBV. Do not edit! */

#include "test.h"

SWord32 test(const SWord32 x0, const SWord32 x1)
{
  const SWord32 s0 = x0;
  const SWord32 s1 = x1;
  const SWord32 s2 = s0 + s1;
  const SWord32 s4 = s2 * 0x00000005UL;
  const SWord32 s6 = s4 >> 2;

  return s6;
}
