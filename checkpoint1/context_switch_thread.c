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
	now = rdtsc32();
	write(fd[1], (int *) &now, sizeof(now));
	pthread_exit(0); /* exit */
}

void receiver(int *fd) {
	// sleep(1);
	int k, ntime;
	uint32_t curr, time;
	static int contextSwitchTime;
	ntime = read(fd[0], (int *) &time, sizeof(time));
	curr = rdtsc32();
	contextSwitchTime = curr - time;
	printf("Context Switch Time = %u\n", contextSwitchTime);
	pthread_exit(0); /* exit */
}

// void contextSwitch() {
int main() {
	int fd[2];
	pipe(fd);

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
	param.sched_priority = priority;
	ret = pthread_attr_setschedparam (&t1, &param);
	pthread_attr_getschedparam(&t1, &param);
	pthread_create (&thread1, &t1, (void *) &sender, (int *) &fd);

	ntime = read(fd[0], (int *) &time, sizeof(time));
	curr = rdtsc32();
	contextSwitchTime = curr - time;
	printf("Context Switch Time = %u\n", contextSwitchTime);

	/* Main block now waits for both threads to terminate, before it exits
	   If main block exits, both threads exit, even if the threads have not
	   finished their work */ 
	pthread_join(thread1, NULL);

	return 0;
}
