/* Example driver program for simple. */
/* Automatically generated by SBV. Edit as you see fit! */

#include <stdio.h>
#include "simple.h"

int main(void)
{
  const SWord32 __result = simple(0x070bb5efUL, 0x5cd15cb8UL);

  printf("simple(0x070bb5efUL, 0x5cd15cb8UL) = 0x%08"PRIx32"UL\n", __result);

  return 0;
}
