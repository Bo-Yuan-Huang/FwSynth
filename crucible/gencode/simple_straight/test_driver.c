/* Example driver program for test. */
/* Automatically generated by SBV. Edit as you see fit! */

#include <stdio.h>
#include "test.h"

int main(void)
{
  const SWord32 __result = test(0x38856c26UL, 0x9bff128cUL);

  printf("test(0x38856c26UL, 0x9bff128cUL) = 0x%08"PRIx32"UL\n", __result);

  return 0;
}