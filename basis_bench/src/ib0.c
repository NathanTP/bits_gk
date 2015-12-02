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
  int val[8] = {1};
  int out;
  volatile int res;

IT1:
  /* Only check count here to reduce the number of predictable branches.
     This means we might do ITERATIONS or ITERATIONS+1 iterations. */
  if(count >= ITERATIONS) {
    res = out;
    printf("Done\n");
    return EXIT_SUCCESS;
  }

  count++;
  bit  = ((rand >> 0) ^ (rand >> 2) ^ (rand >> 3) ^ (rand >> 5) ) & 1;
  rand =  (rand >> 1) | (bit << 15);
  if(rand < MID) {
    asm (
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"

      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
        "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
      : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
      );
    goto IT1;
  } else {
    asm (
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"

      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
        "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
      : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
      );
    goto IT2;
  }

IT2:
  count++;  
  bit  = ((rand >> 0) ^ (rand >> 2) ^ (rand >> 3) ^ (rand >> 5) ) & 1;
  rand =  (rand >> 1) | (bit << 15);
  if(rand < MID) {
    goto IT1;
    asm (
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"

      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
        "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
      : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
      );
  } else {
    asm (
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
       "mov %5, %%r12d\n"
       "mov %6, %%r13d\n"
       "add %%r12d, %%r12d\n"
       "add %%r13d, %%r13d\n"
       "mov %7, %%r14d\n"
       "mov %8, %%r15d\n"
       "add %%r14d, %%r14d\n"
       "add %%r15d, %%r15d\n"

      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
        "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
      : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
      );
    goto IT2;
  }
}
