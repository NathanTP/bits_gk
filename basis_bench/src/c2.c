/* A benchmark intended to stress the data caches.
   Touches every cache line in a page in random order.
   Touches pages in sequential order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"

#define ITERATIONS 128
/* Size of test array (defines problem size, must be divisible by PG_SZ)*/
#define ARR_SZ (1024*1024*1024)

/* Size of a page (XXX should really use something more portable) */
#define PG_SZ (4*1024)

/* Size of an L1 d-cache line */
#define LN_SZ 64

int main(int argc, char *argv[]) {
  uint8_t *arr = malloc(ARR_SZ);
  uint8_t res = 0;
  int rv;

  // Multiple iterations
  for(int ix = 0; ix < ITERATIONS; ix++) {
    //For each page
    for(int pgx = 0; pgx < (ARR_SZ / PG_SZ); pgx++)
    {
      uint8_t *page = &arr[pgx*PG_SZ];
      for(int lnx = 0; lnx < LN_SZ; lnx++) {
        /* Implement a silly mod using branches for funsies */
        rv = rand_lcg() % 72;
        if(rv > 64) {
          res += page[ (rv - 64) * LN_SZ ];
        } else {
          res += page[ rv * LN_SZ];
        }
      }
    }
  }

  volatile uint8_t trick = res;
  printf("Done\n");

  return EXIT_SUCCESS;
}
