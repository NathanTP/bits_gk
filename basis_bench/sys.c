/* A benchmark for stressing the system-call interface.
   Calls gettimeofday in a tight loop.
 */
#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ITERATIONS (1024*1024*24)

int main(int argc, char *argv[]) {
  volatile pid_t pid;

  for(int64_t i = 0; i < ITERATIONS; i++) {
    pid = syscall(SYS_getpid);
  }

  printf("Done\n");
  return EXIT_SUCCESS;
}
