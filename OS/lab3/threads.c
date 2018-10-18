#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Definition of the variable to hold the result
int result;

/// Define one fonction for each thread
void * thread1(int * params){
	/*
	This thread will be tasked with making the first computation.
	 */
	// No need to lock the mutex.
	result += 3 - 4;

	pthread_exit((void*) 0);
}

void * thread2(pthread_t * params){
	/*
	This thread is tasked with making the second computation, then join with the
	first thread and store in result the multiplication between its own result
	and the result from the first thread.
	Params contains the pointer towards thread1.
	 */
	int results = 1 + 2;
	pthread_join(*params, NULL);
	// No need to lock the mutex, since all threads trying to access it are closed
	result = results * result;

	pthread_exit((void*) 0);
}

void * thread3(pthread_t * params){
	/*
	Same as previously, this thread joins with thread 2 and puts all results
	together
	 */
	int results = 5 + 6;
	pthread_join(*params, NULL);

	result += results;

	pthread_exit((void*) 0);
}

int main(int argc, char **argv){
	
	// Creation of threads
	pthread_t operations[3];

	if(pthread_create(&operations[0], NULL, thread1, NULL)){
		perror("Error creating thread");
	}

	if(pthread_create(&operations[1], NULL, thread2, &operations[0])){
		perror("Error creating thread");
	}
	if(pthread_create(&operations[2], NULL, thread3, &operations[1])){
		perror("Error creating thread");
	}

	// Close thread
	pthread_join(operations[2], NULL);
	

	printf("The result is : %i\n",  result);

	return 0;
}
