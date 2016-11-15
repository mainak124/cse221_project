#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include "armpmu_lib.h"


/* struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
	int thread_no;
	uint32_t time_in;
	uint32_t time_out;
} thdata;

/* prototype for thread routine */
void print_message_function ( thdata *ptr );

int main()
{
	pthread_t thread1, thread2;  /* thread variables */
	thdata data1, data2;         /* structs to be passed to threads */
uint32_t time_total= 0;
	
	/* initialize data to pass to thread 1 */
	data1.thread_no = 1;
	data2.thread_no = 2;
	data1.time_out = 0;


	data1.time_in = rdtsc32();
//	data2.time_in = rdtsc32();
	
	/* initialize data to pass to thread 2 */
	
	/* create threads 1 and 2 */    
	pthread_create (&thread1, NULL, (void *) &print_message_function, &data1);
//	pthread_create (&thread2, NULL, (void *) &print_message_function, &data2);
	data2.time_in = rdtsc32();
	
	/* Main block now waits for both threads to terminate, before it exits
	   If main block exits, both threads exit, even if the threads have not
	   finished their work */ 
	pthread_join(thread1, NULL);
//	pthread_join(thread2, NULL);

	printf("Time :, %u, %u, %u\n",data1.time_in,data1.time_out,(data2.time_in-data1.time_in));
	/* exit */  
	return 0;
} /* main() */

void print_message_function ( thdata *ptr )
{
	uint32_t time_now,time_start;
	time_now = rdtsc32();
	thdata *data;            
	data = ptr;  /* type cast to a pointer to thdata */
	
	data->time_out = time_now - data->time_in;
	
	pthread_exit(0); /* exit */
}
