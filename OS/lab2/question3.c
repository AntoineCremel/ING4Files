#include <stdio.h>
// Includes for the forks
#include <sys/types.h>
#include <unistd.h>
// Include for the shared memory functions
#include <sys/shm.h>
// Include for wait
#include <sys/wait.h>

#define PERMS 0600

int main(int argc, char **argv) {
	// Variable which will hold the ids of each shared memory zone
	int id;
	// Variable which will hold the addresses of
	// each shared memory zone
	int * ptr;

	// Creation of each shared memory zones
	id = shmget(0, sizeof(int), IPC_CREAT | PERMS);
	ptr = shmat(id, NULL, 0);

	// Creation of the child processes
	if (fork() == 0) {
		// Make the calculation
		*ptr = 3 + 4;
	}
	else {
		// Creation of a local variable to store the result of the operation
		int result;
		// Make the calculation required
		result = 1 + 2;
		// Wait for the end of the first operation, then multiply the 2
		wait(NULL);
		*ptr = *ptr - result;

		// Print out the result to the screen
		// Our result should be : 
		// (1 + 2) - (3 + 4) = 4
		printf("Le resultat du calcul est : %i\n", *ptr);

		// Free thee zone of shared memory
		shmctl(id, IPC_RMID, NULL);
	}

	return 0;
}
