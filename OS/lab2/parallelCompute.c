#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definition of the variable to hold the result
int result;

pthread_mutex_t sum;

void * addition(void * params){
	int * param = (int *)params;

	printf("I am a thread, here is my result : %i", param[0]+param[1]);

	pthread_mutex_lock(&sum);
	result += param[0]+param[1];
	pthread_mutex_unlock(&sum);

	pthread_exit((void*) 0);
}

int main(int argc, char **argv){
	void * status;
	// Creation of threads
	pthread_t operations[2];
	// Creation of parameters
	int pars[2];
	int pars2[2];

	result = 0;

	pars[0] = 1;
	pars[1] = 2;
	if(pthread_create(&operations[0], NULL, addition, pars)){
		perror("Error creating thread");
	}
	pars2[0] = 3;
	pars2[1] = 4;
	if(pthread_create(&operations[1], NULL, addition, pars2)){
		perror("Error creating thread");
	}

	// Wait for other threads to finish
	pthread_join(operations[0], &status);
	pthread_join(operations[1], &status);

	printf("The result is : %i",  result);

	return 0;
}
