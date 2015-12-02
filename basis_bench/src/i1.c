#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*1024*2l

int main(int argc, char *argv[]) {
  int64_t count = 0;
  int val[4] = {1};
  int out;
  volatile int res = 0;
  while(count < ITERATIONS) {
    asm (
       "mov %1, %%r8d\n"
       "mov %2, %%r9d\n"
       "add %%r8d, %%r8d\n"
       "add %%r9d, %%r9d\n"
       "mov %3, %%r10d\n"
       "mov %4, %%r11d\n"
       "add %%r10d, %%r10d\n"
       "add %%r11d, %%r11d\n"
      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3])
      : "%r8", "%r9", "%r10", "%r11"
      );
    count++;
  }

  res = out;
  printf("Done\n");
  return EXIT_SUCCESS;
}
