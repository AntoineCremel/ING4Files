#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t processId;
	int status;
	int i = 5;
	
	processId = fork();

	if(processId != 0){
		i++;
		printf("I'm the parent. My id is %i, and my parent's idea is %i, i = %i\n", getpid(), getppid(), i);
		wait(&status);
		printf("Wait status : %i\n", status);
	}
	else{
		processId = fork();
		printf("I'm the child. My id is %i, and my parent's idea is %i, i = %i\n", getpid(), getppid(), i);
		wait(&status);
	}
	

	return 0;
}