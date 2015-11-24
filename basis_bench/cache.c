/* A benchmark intended to stress the data caches.
   Touches every cache line in a page in random order.
   Touches pages in sequential order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ITERATIONS 1024
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
      res += page[ cache_pattern[0]*LN_SZ ];
      res += page[ cache_pattern[1]*LN_SZ ];
      res += page[ cache_pattern[2]*LN_SZ ];
      res += page[ cache_pattern[3]*LN_SZ ];
      res += page[ cache_pattern[4]*LN_SZ ];
      res += page[ cache_pattern[5]*LN_SZ ];
      res += page[ cache_pattern[6]*LN_SZ ];
      res += page[ cache_pattern[7]*LN_SZ ];
      res += page[ cache_pattern[8]*LN_SZ ];
      res += page[ cache_pattern[9]*LN_SZ ];
      res += page[ cache_pattern[10]*LN_SZ ];
      res += page[ cache_pattern[11]*LN_SZ ];
      res += page[ cache_pattern[12]*LN_SZ ];
      res += page[ cache_pattern[13]*LN_SZ ];
      res += page[ cache_pattern[14]*LN_SZ ];
      res += page[ cache_pattern[15]*LN_SZ ];
      res += page[ cache_pattern[16]*LN_SZ ];
      res += page[ cache_pattern[17]*LN_SZ ];
      res += page[ cache_pattern[18]*LN_SZ ];
      res += page[ cache_pattern[19]*LN_SZ ];
      res += page[ cache_pattern[20]*LN_SZ ];
      res += page[ cache_pattern[21]*LN_SZ ];
      res += page[ cache_pattern[22]*LN_SZ ];
      res += page[ cache_pattern[23]*LN_SZ ];
      res += page[ cache_pattern[24]*LN_SZ ];
      res += page[ cache_pattern[25]*LN_SZ ];
      res += page[ cache_pattern[26]*LN_SZ ];
      res += page[ cache_pattern[27]*LN_SZ ];
      res += page[ cache_pattern[28]*LN_SZ ];
      res += page[ cache_pattern[29]*LN_SZ ];
      res += page[ cache_pattern[30]*LN_SZ ];
      res += page[ cache_pattern[31]*LN_SZ ];
      res += page[ cache_pattern[32]*LN_SZ ];
      res += page[ cache_pattern[33]*LN_SZ ];
      res += page[ cache_pattern[34]*LN_SZ ];
      res += page[ cache_pattern[35]*LN_SZ ];
      res += page[ cache_pattern[36]*LN_SZ ];
      res += page[ cache_pattern[37]*LN_SZ ];
      res += page[ cache_pattern[38]*LN_SZ ];
      res += page[ cache_pattern[39]*LN_SZ ];
      res += page[ cache_pattern[40]*LN_SZ ];
      res += page[ cache_pattern[41]*LN_SZ ];
      res += page[ cache_pattern[42]*LN_SZ ];
      res += page[ cache_pattern[43]*LN_SZ ];
      res += page[ cache_pattern[44]*LN_SZ ];
      res += page[ cache_pattern[45]*LN_SZ ];
      res += page[ cache_pattern[46]*LN_SZ ];
      res += page[ cache_pattern[47]*LN_SZ ];
      res += page[ cache_pattern[48]*LN_SZ ];
      res += page[ cache_pattern[49]*LN_SZ ];
      res += page[ cache_pattern[50]*LN_SZ ];
      res += page[ cache_pattern[51]*LN_SZ ];
      res += page[ cache_pattern[52]*LN_SZ ];
      res += page[ cache_pattern[53]*LN_SZ ];
      res += page[ cache_pattern[54]*LN_SZ ];
      res += page[ cache_pattern[55]*LN_SZ ];
      res += page[ cache_pattern[56]*LN_SZ ];
      res += page[ cache_pattern[57]*LN_SZ ];
      res += page[ cache_pattern[58]*LN_SZ ];
      res += page[ cache_pattern[59]*LN_SZ ];
      res += page[ cache_pattern[60]*LN_SZ ];
      res += page[ cache_pattern[61]*LN_SZ ];
      res += page[ cache_pattern[62]*LN_SZ ];
      res += page[ cache_pattern[63]*LN_SZ ];
    }
  }

  volatile uint8_t trick = res;
  printf("Done\n");

  return EXIT_SUCCESS;
}
