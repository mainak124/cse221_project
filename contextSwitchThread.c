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
//	close(fd[0]);
//	for (n = 10; n > 0; n--) {
		now = rdtsc32();
		write(fd[1], (int *) &now, sizeof(now));
//	close(fd[1]);
		// printf("write[%d] = %u\n", n, now);
//	}		
	pthread_exit(0); /* exit */
}

void receiver(int *fd) {
	// sleep(1);
	int k, ntime;
	uint32_t curr, time;
	static int contextSwitchTime;
//	close(fd[1]);
//	for(k = 10; k > 0; k--) {
	ntime = read(fd[0], (int *) &time, sizeof(time));
	curr = rdtsc32();
	contextSwitchTime = curr - time;
//	printf("read[%d] = %u\n", k, time);
	printf("Context Switch Time = %u\n", contextSwitchTime);
//	close(fd[0]);
//	}
	pthread_exit(0); /* exit */
}

// void contextSwitch() {
int main() {
	int fd[2];
	pipe(fd);

//	uint32_t t1,t2;
	uint32_t curr, time, ntime;
	uint32_t contextSwitchTime;
	pthread_t thread1, thread2;  /* thread variables */

	pthread_attr_t t1;
int priority = 99;
struct sched_param param;
int ret;
	pthread_attr_init(&t1);
ret = pthread_attr_setschedpolicy(&t1, SCHED_RR);
pthread_attr_getschedparam(&t1, &param);
//printf("Old priority: %d\n",param.sched_priority);
param.sched_priority = priority;
	ret = pthread_attr_setschedparam (&t1, &param);
pthread_attr_getschedparam(&t1, &param);
	/* create threads 1 and 2 */    
//	t1 = rdtsc32();
	pthread_create (&thread1, &t1, (void *) &sender, (int *) &fd);
//	pthread_create (&thread2, NULL, (void *) &receiver, (int *) &fd);

//	close(fd[1]);
	ntime = read(fd[0], (int *) &time, sizeof(time));
	curr = rdtsc32();
	contextSwitchTime = curr - time;
	printf("Context Switch Time = %u\n", contextSwitchTime);

	/* Main block now waits for both threads to terminate, before it exits
	   If main block exits, both threads exit, even if the threads have not
	   finished their work */ 
	pthread_join(thread1, NULL);
//	pthread_join(thread2, NULL);
//	t2 = rdtsc32();
//	printf ( "Time for context_switch= %u\n",(t2-t1)/2);

	return 0;
}
