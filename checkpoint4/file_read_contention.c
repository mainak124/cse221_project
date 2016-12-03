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
#include <stdint.h>
#include "../armpmu_lib.h"

void disable_filecache() {
	int fd;
	char* data = "3";
	
	sync();
	fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
	write(fd, data, sizeof(char));
	close(fd);
}

void fileread(char *fname, int fsize, int isWrite) {
    unsigned start, end;
    int fd;
    char *data, *buffer, *a_buffer;
    FILE *res;
    int offset, pagesize;
    int i = 0;

    pagesize = getpagesize();
    buffer = malloc((sizeof(char) * fsize) + pagesize);
    // a_buffer = ((((int unsigned)buffer + pagesize - 1) / pagesize) * pagesize);
    a_buffer = ((((uintptr_t)buffer + pagesize - 1) / pagesize) * pagesize);
    
    // open for read
    fd = open(fname, O_RDONLY | O_DIRECT | O_SYNC);
    
    if (fd < 0) {
        printf("error: cannot open a file %s \n", fname);
        exit(-1);
    }  
    
    start = rdtsc32();
    for(offset = 0; offset < fsize; offset += 4096) {
        // lseek(fd, offset, SEEK_SET);
        
        if(read(fd, a_buffer, 4096) < 0) 
            fprintf(stderr, "error pread\n");
    }
    end = rdtsc32();
	disable_filecache();
    
	if (isWrite) {
    	FILE *res = fopen("results/file_cache_contention.txt", "w");	
    	fprintf(res, "%s, %d, %u\n", fname, fsize, (end-start)/(offset/4096));
    	fclose(res);
	}
    close(fd);
    free(buffer);
    // printf("Inside %s Read Process\n", fname);
}        

int main(int argc, char **argv) {
    // pid_t child_pid[10];
    // pid_t ppid, pid;
    // int i = 0;
    
    char* fname[10] = {"file_0", "file_1", "file_2", "file_3", "file_4", "file_5", "file_6", "file_7", "file_8", "file_9"};
    
    int fsize = 4194304;
    int x;
    
    if(fork()) // parent
        // if(fork()) // parent
            // if(fork()) // parent
                // if(fork()) // parent
                    // if(fork()) // parent
                        // if(fork()) // parent
                            // if(fork()) // parent
                                // if(fork()) // parent
                                	// if(fork()) // parent
                                    	// if(fork()) // parent
                                            x = 1;
                                    	// else // child9
                                        // 	fileread(fname[9], fsize, 1);
                                	// else // child8
                                    // 	fileread(fname[8], fsize, 1);
                                // else // child7
                                //     fileread(fname[7], fsize, 1);
                            // else // child6
                            //     fileread(fname[6], fsize, 0);
                        // else // child5
                        //     fileread(fname[5], fsize, 1);
                    // else // child4
                    //     fileread(fname[4], fsize, 1);
                // else // child3
                //     fileread(fname[3], fsize, 1);
            // else // child2
            //     fileread(fname[2], fsize, 1);
        // else // child1
        //     fileread(fname[1], fsize, 1);
    else // child0
        fileread(fname[0], fsize, 1);
                            
    return 0;
}
