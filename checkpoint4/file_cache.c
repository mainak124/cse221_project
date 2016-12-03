#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../armpmu_lib.h"

int main(int argc, char **argv)
{
    unsigned start_time, end_time;
    int fd, i, j;
    char *data, *fname, *buffer;
    FILE *res;
	
	fname = "dump.txt";

	// res = fopen("results/fileCacheSize.txt", "w");
	int fsize[30] = {1000000, 4000000, 8000000, 16000000, 24000000, 32000000, 48000000, 64000000, 80000000, 100000000, 
					120000000, 140000000, 160000000, 180000000, 190000000, 195000000, 200000000, 210000000, 220000000, 240000000, 270000000, 300000000, 350000000, 400000000, 450000000, 500000000, 550000000, 600000000, 650000000, 700000000};
	for (i = 25; i < 26; i++) {
		for (j = 0; j < 1; j++) {
    		buffer = malloc(sizeof(char) * fsize[i]);

    		// open for read
    		fd = open(fname, O_RDONLY);
    		if (fd < 0) {
    			printf("error: cannot open a file %s \n", fname);
    			exit(-1);
    		}  
 
    		// Warmup buffer cache
    		if(read(fd, buffer, fsize[i]) < 0)
    		{
				fprintf(stderr, "error warming up file cache\n");
				return 1;
    		}

    		// set initial position
			if(lseek(fd, 0, SEEK_SET) < 0) {
				printf("error: could not seek to position 0 in file %s \n", fname);
			  	return 1;
			}
			  

			start_time = rdtsc32();
			read(fd, buffer, fsize[i]);
			end_time = rdtsc32();
			
			// fprintf(res, "%d, %u\n", fsize[i], end_time - start_time);
			
			close(fd);
			//free(buffer);
		}
	}

	// fclose(res);
    return 0;
}

