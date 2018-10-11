#include <stdio.h>
// Includes for the forks
#include <sys/types.h>
#include <unistd.h>
// Include for the shared memory functions
#include <sys/shm.h>
// Include for wait
#include <sys/wait.h>
#include <stdlib.h>

#define PERMS 0600
#define NB_PROCESSES 3

int main(int argc, char **argv) {
	// 0 Variables
	// Creation of a stream variable for pipe communication
	FILE * stream;
	// Variable in which each process will store the result of
	// its computation
	int result;
	int childResult;

	// Generation of the first pipe
	int pipe1[2];
	pipe(pipe1);
	// Creation of the child processes
	if (fork() == 0) {
		/*
			We are in the child process.
			This child process will generate yet another child and will make the first
			computation.

			We use pipe1 to communicate the result of the computation to the parent
			process.
			This process will get the result from its child using pipe2.
		*/
		int pipe2[2];
		pipe(pipe2);
		// Generate yet another fork
		if (fork() == 0) {
			// Pipe1 will not be needed here, close it right away
			close(pipe1[0]);
			close(pipe1[1]);
			// Close the read end of the pipe
			close(pipe2[0]);
			// Opening the stream to write into the pipe
			stream = fdopen(pipe2[1], "w");
			// Make the calculation
			result = 3 - 4;
			// Send the result through the pipe
			fprintf(stream, "%i\n", result);
			fflush(stream);
			// Close the pipe
			close(pipe2[1]);
		}
		else{
			// Close the right ends of the pipes
			// Close the write end of pipe2
			close(pipe2[1]);
			// Close the read end of pipe1
			close(pipe1[0]);
			// Make the calculation required
			result = 1 + 2;
			// Open the stream on pipe2 to receive the result from
			// child process
			stream = fdopen(pipe2[0], "r");
			fscanf(stream, "%i", &childResult);
			printf("Result from the first child : %i\n", childResult);
			// Combine the two results
			result *= childResult;

			// Close the reading stream to open the writing stream
			fclose(stream);
			// Open a stream to pipe1
			stream = fdopen(pipe1[1], "w");
			// Send the result through the pipe
			fprintf(stream, "%i\n", result);
			fflush(stream);
			fclose(stream);
		}
	}
	else {
		close(pipe1[1]);
		// Make the calculation
		result = 5 + 6;

		stream = fdopen(pipe1[0], "r");
		fscanf(stream, "%i", &childResult);
		printf("Result from the second child : %i\n", childResult);
		// Combine the two results
		result += childResult;

		// Output the result to the screen. Our operation sums up to :
		// (1 + 2) * (3 - 4) + (5 + 6) = 8
		printf("The result of the operation is as follow : %i\n", result);

		// Close the pipe
		fclose(stream);
	}

	return 0;
}
