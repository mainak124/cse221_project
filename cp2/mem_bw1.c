#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define CACHE_LINE_SIZE 64 //64 bytes
#define ARRAY_SIZE 2097152

#include "armpmu_lib.h"

// static inline unsigned ccnt_read(void)
// {
// unsigned cc;
// asm volatile ("mrc p15, 0, %0, c9, c13, 0" : "=r" (cc));
// return cc;
// }

void main(int argc, char* argv[]) {
  uint32_t start, end, exec;
  int i,counter;
  int temp;
  int *array;
  int offset = CACHE_LINE_SIZE; //offset
  FILE* fp;
 
  array=(int *)malloc(sizeof(int) * ARRAY_SIZE);
  counter=ARRAY_SIZE;

  for(i=0;i<counter;i+=offset){
    temp = array[i];
  }

  // // start = ccnt_read();
  start = rdtsc32();// = rdtsc32();
  temp = array[offset];
  // // end = ccnt_read();
  end = rdtsc32();// = rdtsc32();

  exec = end-start;
  fp = fopen("results/memory_bandwidth_read.csv", "a");
  fprintf(fp, "%u,%u,%u\n", start, end, exec);
  fclose(fp);
  free(array);
}
