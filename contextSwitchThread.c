#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "armpmu_lib.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>      /* Errors */
#include <pthread.h>    /* POSIX Threads */

void sender(int *fd) {
	int n;
	uint32_t now;
	// close(fd[0]);
	for (n = 10; n > 0; n--) {
		now = rdtsc32();
		write(fd[1], (int *) &now, sizeof(now));
		printf("write[%d] = %u\n", n, now);
	}		
	pthread_exit(0); /* exit */
}

void receiver(int *fd) {
	// sleep(1);
	int k, ntime;
	uint32_t curr, time;
	static int contextSwitchTime[10];
	// close(fd[1]);
	for(k = 10; k > 0; k--) {
		ntime = read(fd[0], (int *) &time, sizeof(time));
		curr = rdtsc32();
		contextSwitchTime[k] = curr - time;
		printf("read[%d] = %u\n", k, time);
		printf("\nContext Switch Time[%d] = %u\n", k, contextSwitchTime[k]);
	}
	pthread_exit(0); /* exit */
}

// void contextSwitch() {
int main() {
	int fd[2];
	pipe(fd);

	pthread_t thread1, thread2;  /* thread variables */
	
	/* create threads 1 and 2 */    
	pthread_create (&thread1, NULL, (void *) &sender, (int *) &fd);
	pthread_create (&thread2, NULL, (void *) &receiver, (int *) &fd);
	
	/* Main block now waits for both threads to terminate, before it exits
	   If main block exits, both threads exit, even if the threads have not
	   finished their work */ 
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	return 0;
}
