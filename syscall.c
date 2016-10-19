#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "armpmu_lib.h"

//void sysc() {
int main() {
	pid_t id,kid,pid ;

uint32_t t1,t2,t3,t4,t5,t6,t7;

	t1 = rdtsc32();
	id = getpid();
	//printf ( "Original PID: %d\n", getpid());
	t2 = rdtsc32();
	id = getpid();
	//printf ( "Original PID: %d\n", getpid());
	t3 = rdtsc32();
	printf("MAIN : Time for 1st GetPID = %u\nMAIN : Time for 2nd GetPID = %u\n", t2-t1,t3-t2);
	t3 = rdtsc32();
	id = fork() ;
//	printf("id value : %d\n",id);
	if ( id == 0 )
	{
		t4 = rdtsc32();
		printf ( "Child : Time for Fork= %u\n",t4-t3);
		t5 = rdtsc32();
		kid = getpid();
		t6 = rdtsc32();
		pid = getppid();
		t7 = rdtsc32();
		printf ( "Child : Time for GetPID = %u\nChild : Time for GetPPID = %u\n", t6-t5,t7-t6);
	}
	else
	{
		t1 = rdtsc32();
		pid = getpid();
		t2 = rdtsc32();
		printf ( "Parent : Time for GetPID = %u\n", t2-t1);
		wait();
	} 
return 0;
}
