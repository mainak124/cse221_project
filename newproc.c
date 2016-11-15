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
	id = fork() ;
//	printf("id value : %d\n",id);
	if ( id == 0 )
	{
		t4 = rdtsc32();
		printf ( "Child : Time for Fork= %u\n",t4-t1);
	}
	else
	{
		t2 = rdtsc32();
		wait();
		printf ( "Parent : Time for OldProcess = %u\n", t2-t1);
	} 
return 0;
}
