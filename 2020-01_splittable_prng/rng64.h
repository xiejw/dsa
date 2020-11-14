#ifndef RNG64_H_
#define RNG64_H_

#include <stdint.h>

// The implementation is based on "Fast Splittable Pseudorandom Number
// Generators.
typedef struct {
  uint64_t seed_;
  uint64_t gamma_;
  uint64_t next_gamma_seed_;
} rng64t;

extern rng64t* rng64Create(uint64_t seed);
extern rng64t* sprng64_create_with_gamma(uint64_t seed, uint64_t gamma_seed);
extern void    sprng64_free(rng64t* prng);
extern rng64t* sprng64_split(rng64t* prng);

extern uint64_t sprng64_next_int64(rng64t* prng);
extern uint32_t sprng64_next_int32(rng64t* prng);
extern double   sprng64_next_double(rng64t* prng);

#endif
