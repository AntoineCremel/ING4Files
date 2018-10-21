#include <stdio.h>
// Includes for the forks
#include <sys/types.h>
#include <unistd.h>
// Include for the shared memory functions
#include <sys/shm.h>
// Include for wait
#include <sys/wait.h>
// For time measurement
#include <time.h>
#include <sys/resource.h>


#define PERMS 0600
#define NB_PROCESSES 3

int main(int argc, char **argv) {
	clock_t start_time = clock();
	// 0 Variables
	int i;
	// Variable which will hold the ids of each shared memory zone
	int id[NB_PROCESSES];
	// Variable which will hold the addresses of
	// each shared memory zone
	int * ptr[NB_PROCESSES];

	// Creation of each shared memory zones
	for (i = 0; i < NB_PROCESSES; i++) {
		id[i] = shmget(0, sizeof(int), IPC_CREAT | PERMS);
		ptr[i] = shmat(id[i], NULL, 0);
	}

	// Creation of the child processes
	if (fork() == 0) {
		// Generate yet another fork
		if (fork() == 0) {
			// Make the calculation
			*ptr[1] = 3 - 4;
		}
		else{
			// Make the calculation required
			*ptr[0] = 1 + 2;
			// Wait for the end of the first operation, then multiply the 2
			wait(NULL);
			*ptr[0] = *ptr[0] * (*ptr[1]);
		}
	}
	else {
		// Make the calculation
		*ptr[2] = 5 + 6;
		// Wait for all child processes
		wait(NULL);

		*ptr[0] = *ptr[0] + (*ptr[2]);

		// Output the result to the screen. Our operation sums up to :
		// (1 + 2) * (3 - 4) + (5 + 6) = 8
		printf("The result is : %i\n", *ptr[0]);

		// Free the shared memory spaces
		for(i=0; i < NB_PROCESSES; i++){
			shmctl(id[i], IPC_RMID, NULL);
		}
		clock_t end_time = clock();
		printf("Execution time : %i\n", (int)((end_time - start_time)));
		// Print the resource usage
		struct rusage self_usage;
		struct rusage child_usage;
		getrusage(RUSAGE_SELF, &self_usage);
		getrusage(RUSAGE_CHILDREN, &child_usage);
		printf("RESOURCES USED :\n\tuser CPU time : \t%i seconds,\
 %i microseconds\n\tsystem CPU time : \t%i seconds, %i microseconds\n\
 \tPage faults no IO :\t%i\n\
 \tPage faults IO : \t%i\n\
 \tNumber of voluntary context switches :\t%i\n\
 \tNumber of involuntary context switches :\t%i\n", 
			(int)(self_usage.ru_utime.tv_sec + child_usage.ru_utime.tv_sec),
			(int)(self_usage.ru_utime.tv_usec + child_usage.ru_utime.tv_usec),
			(int)(self_usage.ru_stime.tv_sec + child_usage.ru_stime.tv_sec),
			(int)(self_usage.ru_stime.tv_usec + child_usage.ru_stime.tv_usec),
			(int)(self_usage.ru_minflt + child_usage.ru_minflt),
			(int)(self_usage.ru_majflt + child_usage.ru_majflt),
			(int)(self_usage.ru_nvcsw + child_usage.ru_nvcsw),
			(int)(self_usage.ru_nivcsw + child_usage.ru_nivcsw));
	}

	return 0;
}
