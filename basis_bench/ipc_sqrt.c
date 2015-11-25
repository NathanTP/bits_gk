#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*32

typedef double double8_t __attribute__((vector_size(32)));

int main(int argc, char *argv[]) {
  int64_t count = 0;
  double8_t val = {1.0, 2.0, 3.0, 4.0};
  volatile double8_t res;
  while(count < ITERATIONS) {
    asm (
       "vmovapd (%0), %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vsqrtpd %%ymm0, %%ymm0\n"
       "vmovapd %%ymm0, (%0)\n"
      :
      : "r" (&val)
      : "%ymm0"
      );
    count++;
  }

  res = val;
  printf("Done\n");
  return EXIT_SUCCESS;
}
