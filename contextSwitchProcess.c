#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "armpmu_lib.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

// void contextSwitch() {
int main() {
	pid_t id;
	int fd[2];
	pipe(fd);
	id = fork();
	if (id == 0) {
		int n;
		uint32_t now;
		close(fd[0]);
		for (n = 10; n > 0; n--) {
			now = rdtsc32();
			write(fd[1], (int *) &now, sizeof(now));
			printf("write[%d] = %u\n", n, now);
		}		
	}
	else {
		int k, ntime;
		uint32_t curr, time;
		static int contextSwitchTime[10];
		close(fd[1]);
		for(k = 10; k > 0; k--) {
			ntime = read(fd[0], (int *) &time, sizeof(time));
			curr = rdtsc32();
			contextSwitchTime[k] = curr - time;
			printf("read[%d] = %u\n", k, time);
			printf("Context Switch Time[%d] = %u\n", k, contextSwitchTime[k]);
		}
	}
	return 0;
}
