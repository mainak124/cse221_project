#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../armpmu_lib.h"

#define CACHE_LINE_SIZE 64 //64 bytes
#define ARRAY_SIZE 2097152

void read_bw() {

	uint32_t time_start = 0;
	uint32_t time_end = 0;

	int i;
	int sum=0;
	int offset = CACHE_LINE_SIZE; //offset
	
	int *arr = (int *)malloc(sizeof(int) * ARRAY_SIZE);
	// memset(arr, 1, ARRAY_SIZE*4);
	
	time_start = rdtsc32();
	// sum = arr[offset];
	for(i=0; i<ARRAY_SIZE/32; i+=offset){
		sum = arr[(i*32)+(offset*0)];   
		sum = arr[(i*32)+(offset*1)]; 
		sum = arr[(i*32)+(offset*2)];
		sum = arr[(i*32)+(offset*3)];
		sum = arr[(i*32)+(offset*4)];
		sum = arr[(i*32)+(offset*5)];
		sum = arr[(i*32)+(offset*6)];
		sum = arr[(i*32)+(offset*7)];
		sum = arr[(i*32)+(offset*8)];
		sum = arr[(i*32)+(offset*9)];
		sum = arr[(i*32)+(offset*10)];
		sum = arr[(i*32)+(offset*11)];
		sum = arr[(i*32)+(offset*12)];
		sum = arr[(i*32)+(offset*13)];
		sum = arr[(i*32)+(offset*14)];
		sum = arr[(i*32)+(offset*15)];
		sum = arr[(i*32)+(offset*16)];
		sum = arr[(i*32)+(offset*17)];
		sum = arr[(i*32)+(offset*18)];
		sum = arr[(i*32)+(offset*19)];
		sum = arr[(i*32)+(offset*20)];
		sum = arr[(i*32)+(offset*21)];
		sum = arr[(i*32)+(offset*22)];
		sum = arr[(i*32)+(offset*23)];
		sum = arr[(i*32)+(offset*24)];
		sum = arr[(i*32)+(offset*25)];
		sum = arr[(i*32)+(offset*26)];
		sum = arr[(i*32)+(offset*27)];
		sum = arr[(i*32)+(offset*28)];
		sum = arr[(i*32)+(offset*29)];
		sum = arr[(i*32)+(offset*30)];
		sum = arr[(i*32)+(offset*31)];
	}
	time_end = rdtsc32();

	int bytes_read = (ARRAY_SIZE/offset)*4;
	int bytes_loaded = ARRAY_SIZE*4;
	uint32_t time = time_end - time_start;
	float bw = (float)bytes_loaded*900/(float)time;

	FILE *fp = fopen("results/mem_rd_bw.txt", "w");
	fprintf(fp, "%d, %u, %f\n", bytes_loaded, time, bw);
	fclose(fp);
	free(arr);
}

void write_bw() {

	uint32_t time_start = 0;
	uint32_t time_end = 0;

	int i;
	int sum=0;
	// int *arr;
	int offset = CACHE_LINE_SIZE; //offset
	
	int *arr = (int *)malloc(sizeof(int) * ARRAY_SIZE);
	// counter=ARRAY_SIZE;
	
	time_start = rdtsc32();
	for(i=0; i<ARRAY_SIZE/32; i+=offset){
		arr[(i*32)+(offset*0)]  = 1;   
		arr[(i*32)+(offset*1)]  = 1; 
		arr[(i*32)+(offset*2)]  = 1;
		arr[(i*32)+(offset*3)]  = 1;
		arr[(i*32)+(offset*4)]  = 1;
		arr[(i*32)+(offset*5)]  = 1;
		arr[(i*32)+(offset*6)]  = 1;
		arr[(i*32)+(offset*7)]  = 1;
		arr[(i*32)+(offset*8)]  = 1;
		arr[(i*32)+(offset*9)]  = 1;
		arr[(i*32)+(offset*10)] = 1; 
		arr[(i*32)+(offset*11)] = 1; 
		arr[(i*32)+(offset*12)] = 1; 
		arr[(i*32)+(offset*13)] = 1; 
		arr[(i*32)+(offset*14)] = 1; 
		arr[(i*32)+(offset*15)] = 1; 
		arr[(i*32)+(offset*16)] = 1; 
		arr[(i*32)+(offset*17)] = 1; 
		arr[(i*32)+(offset*18)] = 1; 
		arr[(i*32)+(offset*19)] = 1; 
		arr[(i*32)+(offset*20)] = 1; 
		arr[(i*32)+(offset*21)] = 1; 
		arr[(i*32)+(offset*22)] = 1; 
		arr[(i*32)+(offset*23)] = 1; 
		arr[(i*32)+(offset*24)] = 1; 
		arr[(i*32)+(offset*25)] = 1; 
		arr[(i*32)+(offset*26)] = 1; 
		arr[(i*32)+(offset*27)] = 1; 
		arr[(i*32)+(offset*28)] = 1; 
		arr[(i*32)+(offset*29)] = 1; 
		arr[(i*32)+(offset*30)] = 1; 
		arr[(i*32)+(offset*31)] = 1; 
	}
	time_end = rdtsc32();

	int bytes_written = (ARRAY_SIZE/offset)*4;
	int bytes_loaded = ARRAY_SIZE*4;
	uint32_t time = time_end - time_start;
	float bw = (float)bytes_loaded*900/(float)time;

	FILE *fp = fopen("results/mem_wr_bw.txt", "w");
	fprintf(fp, "%d, %u, %f\n", bytes_loaded, time, bw);
	fclose(fp);
	free(arr);
}

int main(int argc, char* argv[]) {
	read_bw();
	write_bw();
	return 0;
}
