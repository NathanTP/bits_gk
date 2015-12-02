/* A benchmark intended to stress the branch-predictor as much as possible
   It uses a linear feedback shift register to compute a branch condition.
   the LFSR is taken from wikipedia:
   https://en.wikipedia.org/wiki/Linear_feedback_shift_register#Fibonacci_LFSRs
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include "util.h"

#define ITERATIONS 1024*1024*512
#define MID (UINT64_MAX / 2)

int main(int argc, char *argv[]) {
  uint32_t count = 0;
  int64_t rv = 0;
  volatile pid_t pid;

IT1:
  /* Only check count here to reduce the number of predictable branches.
     This means we might do ITERATIONS or ITERATIONS+1 iterations. */
  if(count >= ITERATIONS) {
    printf("Done\n");
    return EXIT_SUCCESS;
  }

  count++;
  rv = rand_lcg();
  if(rv < MID) {
    pid = syscall(SYS_getpid);
    goto IT1;
  } else {
    goto IT2;
  }

IT2:
  count++;  
  rv = rand_lcg();
  if(rv < MID) {
    goto IT1;
  } else {
    goto IT2;
  }
}
