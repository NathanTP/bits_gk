/* A benchmark for stressing the system-call interface.
   Calls gettimeofday in a tight loop.
 */
#include <stdint.h>
#include <sys/syscall.h>
#include <linux/random.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ITERATIONS (1024*1024*2)

int main(int argc, char *argv[]) {
  uint8_t buf[64];
  volatile uint8_t volt;

  for(int64_t i = 0; i < ITERATIONS; i++) {
    syscall(SYS_getrandom, &buf, 64, 0);
    volt = buf[1];
  }

  printf("Done\n");
  return EXIT_SUCCESS;
}
