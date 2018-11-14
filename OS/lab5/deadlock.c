#include <stdio.h>
#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define N_SEMAPHORES 3

int main(int argc, char *argv[]) {
	// 0 Variables
	int i;
	sem_t sems[N_SEMAPHORES];

	// 1 Create the semaphores
	for(i = 0; i < N_SEMAPHORES; i++) {
		// We initialise 3 semaphores whose value we set to -1
		if(sem_init(&sems[i], 1, 0) == -1) {
			perror("Error creating the semaphore");
			exit(EXIT_FAILURE);
		}
	}

	// 2 We start forking the process
	if(fork() == 0) {
		/* In the child of the first process, we will fork once more */
		if(fork() == 0) {
			/* Child of the child
			 We will wait for sems[0] to be available.
			When it is, we will make sems[1] be available */
			sem_wait(&sems[0]);
			sem_post(&sems[1]);
			printf("Child child\n");
		} else {
			/* Parent of the child.
			We wait for sems[1] and free sems[2] */
			sem_wait(&sems[1]);
			sem_post(&sems[2]);
			printf("Child parent\n");
		}
	} else {
		/* Mega parent.
		We wait for sems[2] and post sems[0] */
		sem_wait(&sems[2]);
		sem_post(&sems[0]);
		printf("Parent\n");
	}

	return 0;
}
