#include <stdio.h>
#include <unistd.h>

int main(){
	int pid;

	if((pid = fork()) == 0)
	{
		printf("Process ID = %i\n", getpid());
		execl("/usr/bin/firefox", "duckduckgo.com", NULL);
	}
	printf("I'm the parent and my child is %i\n", pid);
	return 0;
}