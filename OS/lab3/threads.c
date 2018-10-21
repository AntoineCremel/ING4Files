#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/resource.h>


// Definition of the variable to hold the result
int result;

/// Define one fonction for each thread
void * thread1(void * params){
	/*
	This thread will be tasked with making the first computation.
	 */
	// No need to lock the mutex.
	result += 3 - 4;

	pthread_exit((void*) 0);
}

void * thread2(void * params){
	/*
	This thread is tasked with making the second computation, then join with the
	first thread and store in result the multiplication between its own result
	and the result from the first thread.
	Params contains the pointer towards thread1.
	 */
	// Conversion of the parameter
	pthread_t * param;
	param = params;

	int results = 1 + 2;
	pthread_join(*param, NULL);
	// No need to lock the mutex, since all threads trying to access it are closed
	result = results * result;

	pthread_exit((void*) 0);
}

void * thread3(void * params){
	/*
	Same as previously, this thread joins with thread 2 and puts all results
	together
	 */
	// Conversion of the parameter
	pthread_t * param;
	param = params;

	int results = 5 + 6;
	pthread_join(*param, NULL);

	result += results;

	pthread_exit((void*) 0);
}

int main(int argc, char **argv){
	// We get the start time
	clock_t start_time = clock();
	
	// Creation of threads
	pthread_t operations[3];

	pthread_create(&operations[0], NULL, thread1, NULL);
	pthread_create(&operations[1], NULL, thread2, &operations[0]);
	pthread_create(&operations[2], NULL, thread3, &operations[1]);

	// Close thread
	pthread_join(operations[2], NULL);
	

	printf("The result is : %i\n",  result);

	// Print the execution time :
	clock_t end_time = clock();
	printf("Execution time : %i\n", (int)((end_time - start_time)));
	// Print the resource usage
	struct rusage usage;
	getrusage(RUSAGE_SELF, &usage);
	printf("RESOURCES USED :\n\tuser CPU time : \t%i seconds,\
 %i microseconds \n\tsystem CPU time : \t%i seconds, %i microseconds\n\
 \tPage faults no IO :\t%i\n\
 \tPage faults IO : \t%i\n\
 \tNumber of voluntary context switches :\t%i\n\
 \tNumber of involuntary context switches :\t%i\n", 
		(int)usage.ru_utime.tv_sec, (int)usage.ru_utime.tv_usec,
		(int)usage.ru_stime.tv_sec, (int)usage.ru_stime.tv_usec,
		(int)usage.ru_minflt, (int)usage.ru_majflt,
		(int)usage.ru_nvcsw, (int)usage.ru_nivcsw);

	return 0;
}
