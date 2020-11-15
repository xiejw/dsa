#include <inttypes.h>  // PRIu64
#include <stdio.h>
#include "rng64.h"

// #define SIZE 4

int main() {
  rng64t* rng = rng64Create(456L);
  // double   got[SIZE];
  // srng_standard_normal(rng, SIZE, got);
  printf("rng int: %" PRIu64 "\n", rng64NextInt64(rng));
  rng64Free(rng);
  return 0;
}
