/* A benchmark intended to stress the TLB and DRAM.
   Reads the first cache line from every page in random order
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/* Size of test array (defines problem size, must be divisible by PG_SZ)*/
#define ARR_SZ (4*1024L*1024L*1024L)

/* Size of a page (XXX should really use something more portable) */
#define PG_SZ (4*1024)

#define NPAGE (ARR_SZ / PG_SZ)
#define ITERATIONS (NPAGE*128)

/* Size of an L1 d-cache line */
#define LN_SZ 64

int main(int argc, char *argv[]) {
  srand(0xDEADBEEF);
  uint8_t *arr = malloc(ARR_SZ);
  assert(arr != NULL);
  uint8_t res = 0;

  // Multiple iterations
  for(int64_t ix = 0; ix < ITERATIONS; ix++) {
    /* Read a random page */
    uint8_t *page = &arr[ (rand() % NPAGE ) * PG_SZ ];
    for(int64_t lnx = 0; lnx < LN_SZ; lnx++) {
      /* Just read the first cache-line from the page to boost cache-hits */
      res += page[lnx];
    }
  }
  volatile uint8_t trick = res;
  printf("Done\n");

  return EXIT_SUCCESS;
}
