#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*1024
#define ARR_SZ (1024*1024)

int main(int argc, char *argv[]) {
  int64_t count = 0;
  int val = 1;
  volatile uint8_t *res = malloc(ARR_SZ);
  while(count < ITERATIONS) {
    asm (
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
        "add $1, %0\n"
      : "=r" (val)
      : "0" (val)
      );
    res[val % ARR_SZ]++;
    count++;
  }
  
  printf("Done\n");
  return EXIT_SUCCESS;
}
