#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#define ITERATIONS 1024*1024
#define ARR_SZ 1024*1024*1024

int main(int argc, char *argv[]) {
  char *arr = malloc(ARR_SZ);

  //Access the array in a page-aligned strided manner

}
