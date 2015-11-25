/* A benchmark intended to stress the branch-predictor as much as possible
   It uses a linear feedback shift register to compute a branch condition.
   the LFSR is taken from wikipedia:
   https://en.wikipedia.org/wiki/Linear_feedback_shift_register#Fibonacci_LFSRs
*/
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>

#define ITERATIONS 1024*1024*1024
#define MID (UINT16_MAX / 2)

int main(int argc, char *argv[]) {
  uint16_t rand = 0xFAEBu;
  uint16_t bit = 0;
  uint32_t count = 0;

IT1:
  /* Only check count here to reduce the number of predictable branches.
     This means we might do ITERATIONS or ITERATIONS+1 iterations. */
  if(count >= ITERATIONS) {
    printf("Done\n");
    return EXIT_SUCCESS;
  }

  count++;
  bit  = ((rand >> 0) ^ (rand >> 2) ^ (rand >> 3) ^ (rand >> 5) ) & 1;
  rand =  (rand >> 1) | (bit << 15);
  if(rand < MID) {
    goto IT1;
  } else {
    goto IT2;
  }

IT2:
  count++;  
  bit  = ((rand >> 0) ^ (rand >> 2) ^ (rand >> 3) ^ (rand >> 5) ) & 1;
  rand =  (rand >> 1) | (bit << 15);
  if(rand < MID) {
    goto IT1;
  } else {
    goto IT2;
  }
}
