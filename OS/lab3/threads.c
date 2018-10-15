#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Constants

// Definition of the variable to hold the result
int resulta, resultb;

pthread_mutex_t mutexa = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexb = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexc = PTHREAD_MUTEX_INITIALIZER;

char joinThreads(pthread_t * threads, size){
	int i;
	// Variable that will hold the exit statuses of the different threads
	void * status;
	// Variable for return value
	int returnValue = 0;

	for(i = 0; i < size; i++){
		// Wait for threads to finish
		if(pthread_join(operations[i], &status) != 0)
			returnValue = 1;
	}
	return 1;
}

void * addition(void * params){
	// Convert the params to the appropriate type
	int * param = (int *)params;

	if(params[2] == 'A'){
		pthread_mutex_lock(&mutexa);
		resulta += param[0]+param[1];
		pthread_mutex_unlock(&mutexa);
	}
	else if(params[2] == 'B'){
		pthread_mutex_lock(&mutexb);
		resultb += param[0]+param[1];
		pthread_mutex_unlock(&mutexb);
	}
	else{
		pthread_mutex_lock(&mutexc);
		resultc += param[0]+param[1];
		pthread_mutex_unlock(&mutexc);
	}

	pthread_exit((void*) 0);
}

void * multiplication(int * params){
	
	if(params[2] == 'A'){
		pthread_mutex_lock(&mutexa);
		resulta += param[0]*param[1];
		pthread_mutex_unlock(&mutexa);
	}
	else if(params[2] == 'B'){
		pthread_mutex_lock(&mutexb);
		resultb += param[0]*param[1];
		pthread_mutex_unlock(&mutexb);
	}
	else{
		pthread_mutex_lock(&mutexc);
		resultc += param[0]*param[1];
		pthread_mutex_unlock(&mutexc);
	}

	pthread_exit((void*) 0);
}

int main(int argc, char **argv){
	
	// Creation of threads
	pthread_t operations[3];
	// Creation of parameters
	int pars[3][3];
	pars[0][0] = 1; pars[0][1] = 2; pars[0][2] = 'A';
	pars[1][0] = 3; pars[1][1] = 4; pars[1][2] = 'B';
	pars[2][0] = 5; pars[2][1] = 6; pars[2][2] = 'C';

	resulta = 0;
	resultb = 0;

	if(pthread_create(&operations[0], NULL, addition, pars[0])){
		perror("Error creating thread");
	}

	if(pthread_create(&operations[1], NULL, addition, pars[1])){
		perror("Error creating thread");
	}
	if(pthread_create(&operations[2], NULL, addition, pars[2])){
		perror("Error creating thread");
	}

	// Close threads
	joinThreads(operations, 3);

	// Create new threads to finish the calculation
	

	printf("The result is : %i\n",  result);

	return 0;
}
