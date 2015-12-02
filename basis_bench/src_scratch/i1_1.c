#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*1024

int main(int argc, char *argv[]) {
  int64_t count = 0;
  int val = 1;
  volatile int res = 0;
  while(count < ITERATIONS) {
    asm (
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
      : "=r" (val)
      : "0" (val)
      );
    count++;
  }

  res = val;
  printf("Done\n");
  return EXIT_SUCCESS;
}
