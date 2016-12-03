#include <stdio.h>
#include <stdint.h>
#include "armpmu_lib.h"

#define LOOP_FACTOR 10
#define LOOP_ITER 6


int main(){

uint32_t time_start = 0;
uint32_t time_end = 0;
uint32_t time = 0;
long long timeArr[LOOP_ITER];
int i,j,h;

	for(i = 0; i < LOOP_ITER; i++) {
		timeArr[i] = 0;
	}

//	for(i=0; i<10000; i++){
	
		time_start = rdtsc32();
		time_end = rdtsc32();
		time = (time_end - time_start);	
//	}
		printf("0Rdtsc: Time reading overhead = %u\n",time);
		
//	printf("\n");

//	for(i=0; i<10000; i++){
	
		time_start = rdtsc32();
		rdtsc32();
		time_end = rdtsc32();
		time = (time_end - time_start);	
//	}
		printf("1Rdtsc: Time reading overhead = %u\n",time);
		
//	printf("\n");

//	for(h=0; h<1000; h++){
		int k=10;
		for(i=0; i<LOOP_ITER; i++){
			time_start = rdtsc32();
			for(j=0;j<k;j++){
			}
			time_end = rdtsc32();
			timeArr[i] = (time_end-time_start);
			k = k*LOOP_FACTOR;
		}
//	}
	for(i = 0; i < LOOP_ITER; i++) {
		printf("Count for %d loop iteration = %u\n", i, timeArr[i]);
	}
	printf("\n");
return 0;
}
