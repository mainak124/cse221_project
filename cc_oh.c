#include <stdio.h>
#include <stdint.h>
#include "armpmu_lib.h"

#define LOOP_FACTOR 10
#define LOOP_ITER 9


int main(){

uint32_t time_start = 0;
uint32_t time_end = 0;
uint32_t time = 0;
long long timeArr[9];
int i,j,h;

	for(i = 0; i < 9; i++) {
		timeArr[i] = 0;
	}

	for(i=0; i<10000; i++){
	
		time_start = rdtsc32();
		time_end = rdtsc32();
		time += (time_end - time_start);	
	}
		printf("10000 Runs: Time reading overhead = %u\n",time);
		
	printf("\n");

	for(i=0; i<10000; i++){
	
		time_start = rdtsc32();
		rdtsc32();
		time_end = rdtsc32();
		time += (time_end - time_start);	
	}
		printf("10000 Runs: Time reading overhead = %u\n",time);
		
	printf("\n");

	for(h=0; h<1000; h++){
		int k=1;
		for(i=0; i<LOOP_ITER; i++){
			time_start = rdtsc32();
			for(j=0;j<k;j++){
			}
			time_end = rdtsc32();
			timeArr[i] += (time_end-time_start);
			k = k*LOOP_FACTOR;
		}
	}
	for(i = 0; i < 9; i++) {
		printf("Count for %d loop iteration = %u\n", i, timeArr[i]/100);
	}
	printf("\n");
return 0;
}
