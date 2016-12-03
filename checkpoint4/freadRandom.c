#define _GNU_SOURCE

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

void disable_filecache() {
	int fd;
	char* data = "3";
	
	sync();
	fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
	write(fd, data, sizeof(char));
	close(fd);
}

int main(int argc, char **argv)
{
	unsigned start, end;
	int fd, i, j, r_idx;
	char *data, *fname, *buffer, *a_buffer;
	int fsize;
	FILE *res;
	int offset, pagesize;
	int num_of_runs;
	
	fname = "dump.txt";
	int log_fsize[15] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
	
	for (j=0; j<15; j++) {
		for (r_idx = 0; r_idx < 10; r_idx++) {
			fsize = 1 << log_fsize[j];
			num_of_runs = fsize / 4096;
			
			pagesize = getpagesize();
			buffer = malloc((sizeof(char) * fsize) + pagesize);
			a_buffer = ((((int unsigned)buffer + pagesize - 1) / pagesize) * pagesize);
			
			// open for read
			fd = open(fname, O_RDONLY | O_DIRECT | O_SYNC);
			if (fd < 0) {
			    printf("error: cannot open a file %s \n", fname);
			    exit(-1);
			}
			
			start = rdtsc32();
			for(i = 0; i < num_of_runs; i++)
			{
				lseek(fd, offset, SEEK_SET);
				read(fd, a_buffer, 4096);
				offset = (4096 * rand()) % fsize;
			}
			end = rdtsc32();
			disable_filecache();
			
			// res = fopen("./data/file_cache_random.txt", "a");
			// fprintf(res, "%d,%u\n", fsize, (end-start)/(num_of_runs));
			printf("%d, %u\n", fsize, (end-start)/(num_of_runs));
			close(fd);
			// fclose(res);
			free(buffer);
		}
	}
	
	return 0;
}
