#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*512

int main(int argc, char *argv[]) {
  int64_t count = 0;
  volatile int val = 1;
  while(count < ITERATIONS) {
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    val++;
    count++;
  }

  printf("Done\n");
  return EXIT_SUCCESS;
}
