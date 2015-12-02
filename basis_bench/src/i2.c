#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS (1024*1024*1024)
#define ARR_SZ (1024*40)

int main(int argc, char *argv[]) {
  int64_t count = 0;
  int val[8] = {1};
  uint32_t out;
  volatile uint8_t *res = malloc(ARR_SZ);
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

       "add %%r8d, %0\n"
       "add %%r9d, %0\n"
       "add %%r10d, %0\n"
       "add %%r11d, %0\n"
      : "=r" (out)
      : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
        "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
      : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
      );
    res[out % ARR_SZ]++;
    count++;
  }

  printf("Done\n");
  return EXIT_SUCCESS;
}
