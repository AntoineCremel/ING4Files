#include <stdio.h>
#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define N_SEMAPHORES 3

int main(int argc, char *argv[]) {
	// 0 Variables
	int input;
	int i;
	sem_t sems[N_SEMAPHORES];

	// 1 Creating the semaphores
	for(i = 0; i < N_SEMAPHORES; i++) {
		// We initialise 3 semaphores whose value we set to -1
		if(sem_init(&sems[i], 1, 1) == -1) {
			perror("Error creating the semaphore");
			exit(EXIT_FAILURE);
		}
	}

	// 2. We make a menu asking the user to launch one of three programs
	// 2.0 We start by printing out a menu for the user
	printf(" XELLO MAIN FRAIND VICH PROGRAM YOU VANT\n");
	printf("\t1. Firefox\n\t2. Okular\n\t3. Emacs\n");
	// 2.1 Read the input from the user
	scanf("%d", &input);

	// 2.2 Run appropriate program
	switch(input) {
		case 1:
		system("firefox");
		break;
		case 2:
		system("okular");
		break;
		case 3:
		system("Emacs");
		break;
	}

	return 0;
}
