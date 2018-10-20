#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N_LOOP 16

struct timespec wait_time;

void * inc(void * params){
	int i;
	struct timespec remaining;
	for(i=0; i < N_LOOP; i++){
		printf("1");
		remaining = wait_time;
		nanosleep(&wait_time, &remaining);
	}
	pthread_exit((void*) 0);
}
void * dec(void * params){
	int i;
	struct timespec remaining;
	for(i=0; i < N_LOOP; i++){
		printf("0");
		remaining = wait_time;
		nanosleep(&wait_time, &remaining);
	}
	pthread_exit((void*) 0);
}

int main(){
	wait_time.tv_sec = 0;
	wait_time.tv_nsec = 1000;

	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, inc, NULL);
	pthread_create(&t2, NULL, dec, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("\n");

	return 0;
}