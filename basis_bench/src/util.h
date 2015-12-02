#ifndef _UTIL_H_
#define _UTIL_H_

static inline uint64_t rand_lfsr(void) {
  static uint64_t rand = 0xDEADBEEF;
  uint64_t bit = 0;

  bit  = ((rand >> 0) ^ (rand >> 1) ^ (rand >> 3) ^ (rand >> 4) ) & 1;
  rand =  (rand >> 1) | (bit << 63);

  return rand;
}

static inline uint64_t rand_lcg(void) {
  static uint64_t rand = 0xDEADBEEF;
  uint64_t a = 6364136223846793005;
  uint64_t c = 1442695040888963407;

  rand = a*rand + c;
  return rand;
}

#endif
