#include <stdio.h>
#include <stdlib.h>
#include "armpmu_lib.h"
#include <sys/mman.h>
#include <fcntl.h>

int main() {
	void *p;
	char buf[10];
	int len = 0;
	int filedesc = 0;
	int offset = 4096+ (1 << 15);
	uint32_t time_start = 0, time_end = 0;
//	printf("Page fault service time: %u, %u, %u\n", time_end-time_start, time_start, time_end);
	filedesc = open("faultfile.csv", O_RDONLY); 
	len = getpagesize();
//	printf("%u\n",len);
	p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, filedesc, 0);
	if (p == MAP_FAILED) {
		printf("Error!\n");
	}
	time_start = rdtsc32();
	sscanf((char *)p, "%s", &buf);
	//buf = ((uint32_t)p + 1<<5);
	// buf[0] = *((char*)p+1);
	time_end = rdtsc32();
//	printf("%c,%c,%c\n",buf[0],buf[1],buf[2]);
	printf("%u\n", time_end-time_start);
	close(filedesc);
	munmap(p, len);//, PROT_READ, MAP_SHARED, filedesc, 0);

//	filedesc = open("faultfile.csv", O_RDONLY); 
//	p = mmap(NULL, len, PROT_READ, MAP_SHARED, filedesc, offset);
//	if (p == MAP_FAILED) {
//		printf("Error!\n");
//	}
//	time_start = rdtsc32();
//	//sscanf((char *)p, "%s", &buf);
//	//buf = ((uint32_t)p + 1<<5);
//	buf[1] = *((char*)p);
//	time_end = rdtsc32();
//	printf("%c,%c,%c\n",buf[0],buf[1],buf[2]);
//	printf("Page fault service time: %u, %u, %u\n", time_end-time_start, time_start, time_end);
//	close(filedesc);
//	munmap(p, len);//, PROT_READ, MAP_SHARED, filedesc, 0);
	return 0;
}
