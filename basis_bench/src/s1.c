/* A benchmark for stressing the system-call interface.
   Calls gettimeofday in a tight loop.
 */
#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ITERATIONS (1024*1024*16)
#define IN_ITER (94)

int main(int argc, char *argv[]) {
  struct timespec tv;
  volatile struct timespec tv_volt;
  int val[8] = {1};
  int out;
  volatile int res = 0;

  for(int64_t i = 0; i < ITERATIONS; i++) {
    syscall(SYS_clock_gettime, CLOCK_REALTIME, &tv);
    tv_volt = tv;
    /* Padd the IPC a bit to make it more "normal" */
    for(int j = 0; j < IN_ITER; j++) {
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
        : "=r" (out)
        : "m" (val[0]), "m" (val[1]), "m" (val[1]), "m" (val[3]),
          "m" (val[4]), "m" (val[5]), "m" (val[6]), "m" (val[7])
        : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r8"
        );
    }
  }

  res = out;
  printf("Done\n");
  return EXIT_SUCCESS;
}
