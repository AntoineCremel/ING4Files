#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
	// 0 Variables 
	int pipefd[2];
	pid_t cpid;

	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0){
		/* Child process. Will be used to launch the more
		operation*/
		// Close the write end
		close(pipefd[1]);
		// Connect standard input to the read end
		dup2(pipefd[0], STDIN_FILENO);
		// Launch more
		system("more");
		close(pipefd[1]);
	}
	else {
		/* Parent process. Will be used to launch ps aux */
		// Close the read end
		close(pipefd[0]);
		// Connect the write end to standard output
		dup2(pipefd[1], STDOUT_FILENO);

		system("ps aux");
		close(pipefd[0]);

		wait(NULL);
	}

	return 0;
}
