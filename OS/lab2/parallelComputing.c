#include <stdio.h>
// Includes for the forks
#include <sys/types.h>
#include <unistd.h>
// Include for the shared memory functions
#include <sys/shm.h>
// Include for wait
#include <sys/wait.h>

#define PERMS 0600
#define NB_PROCESSES 3

int main(int argc, char **argv) {
	// 0 Variables
	int i;
	// Variable which will hold the ids of each shared memory zone
	int id[NB_PROCESSES];
	// Variable which will hold the addresses of
	// each shared memory zone
	int * ptr[NB_PROCESSES];
	// Variable to store IDs of the first child process
	pid_t child1ID;

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
		printf("The result of the operation is as follow : %i\n", *ptr[0]);

		for(i=0; i < NB_PROCESSES; i++){
			shmctl(id[i], IPC_RMID, NULL);
		}
	}

	return 0;
}
