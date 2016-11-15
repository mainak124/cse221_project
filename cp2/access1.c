#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>

#include <sys/timeb.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "armpmu_lib.h"

static int DEF_ITERATION = 100000;
// static int DEF_STRIDE = 128;
// static int DEF_SIZE = 1024*1024;

// static int* v;

// void workload_init(int STRIDE, int SIZE) {
// 	// Set up array
// 	v = (int*)malloc(sizeof(int)*SIZE);
// 	int i;
// 	for (i = STRIDE; i < SIZE; i += STRIDE) {
// 		v[i] = (int)&v[i-STRIDE];
// 	}
// 	v[0] = (int)&v[i-STRIDE];
// 
// 	// Warmup the memory
// 	int* p = v;
// 	do {
// 		p = (int*)*p;
// 	} while (p != (int*)v);
// }
// 
// void workload_finish() {
// 	free(v);
// }
// 
// uint32_t workload_body(int iteration, int STRIDE, int SIZE) {
// 
// 	int* p = v;
// 	int i;
// 
// 	uint32_t time_start = 0;
// 	uint32_t time_end = 0;
// 	uint32_t time = 0;
// 
// 	time_start = rdtsc32();// = rdtsc32();
// 	for (i = 0; i < iteration; i++) {
// 		p = (int*)*p; 
// 	}
// 	time_end = rdtsc32();// = rdtsc32();
// 	time = (time_end - time_start);	
// 	// printf("Rdtsc: Time reading overhead = %u\n",time);
// 	return time;
// 
// }

int main(int argc, char *argv[]) {

	FILE *fp = fopen("results/mem_latency.txt", "w");
	uint32_t time = 0;
	int DEF_SIZE=512;
	int DEF_STRIDE=16;

	for (DEF_STRIDE=16; DEF_STRIDE<=256; DEF_STRIDE=DEF_STRIDE*2) {
		for (DEF_SIZE=1<<8; DEF_SIZE<=1<<25; DEF_SIZE=DEF_SIZE*2) {
			int* v;

			v = (int*)malloc(sizeof(int)*DEF_SIZE);
			int i;
			for (i = DEF_STRIDE; i < DEF_SIZE; i += DEF_STRIDE) {
				v[i] = (int)&v[i-DEF_STRIDE];
			}
			v[0] = (int)&v[i-DEF_STRIDE];

			// Warmup the memory
			int* p = v;
			do {
				p = (int*)*p;
			} while (p != (int*)v);



			uint32_t time_start = 0;
			uint32_t time_end = 0;
			uint32_t time = 0;

			time_start = rdtsc32();// = rdtsc32();
			for (i = 0; i < DEF_ITERATION; i++) {
				p = (int*)*p; 
			}
			time_end = rdtsc32();// = rdtsc32();
			time = (time_end - time_start);	

			// printf("Rdtsc: Time reading overhead");
			// Run workload
			fprintf(fp, "%d, %d, %u\n", DEF_STRIDE, DEF_SIZE, time);	
			free(v);
		}
	}

 	fclose(fp);

	// Finish the ptart, end, exec);
	// workload_finish();
	
	return 0;
}
