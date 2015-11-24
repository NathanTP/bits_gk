/* A benchmark intended to stress the data caches.
   Touches every cache line in a page in random order.
   Touches pages in sequential order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
  const int cache_pattern[LN_SZ] = {
                       15, 12, 8, 5, 54, 61, 2, 40, 21, 31, 30, 42, 48, 36,
                       52, 57, 39, 11, 44, 23, 33, 47, 41, 45, 60, 28, 22,
                       17, 58, 4, 56, 55, 53, 0, 24, 6, 10, 38, 37, 7, 49,
                       59, 46, 35, 43, 27, 20, 9, 50, 18, 1, 51, 62, 34, 16,
                       25, 26, 19, 3, 29, 13, 14, 63, 32
                      };

  // Multiple iterations
  for(int ix = 0; ix < ITERATIONS; ix++) {
    //For each page
    for(int pgx = 0; pgx < (ARR_SZ / PG_SZ); pgx++)
    {
      uint8_t *page = &arr[pgx*PG_SZ];
      /* For each line in the page */
      for(int lnx = 0; lnx < LN_SZ; lnx++) {
        res += page[ cache_pattern[lnx]*LN_SZ ];
      }
    }
  }

  volatile uint8_t trick = res;
  printf("Done\n");

  return EXIT_SUCCESS;
}
