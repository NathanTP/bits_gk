#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1024*1024*1024

int main(int argc, char *argv[]) {
  int64_t count = 0;
  int val = 1;
  volatile int res = 0;
  while(count < ITERATIONS) {
    val = 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    val += 1;
    res = val;
    count++;
  }

  printf("Done\n");
}
