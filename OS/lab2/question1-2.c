#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY 4567
#define PERMS 0660

/* 
1. From what we understand from the output, we modify i and *ptr in the child
	process first and print them. In the parent process, we wait for the execution
	of the child, then we print i and *ptr.
	Since i was modified into the child process, its value remained unchanged on
	the output of the main process. However, *ptr is a pointer to a shared memory
	zone, and therefore its modification has an effect on the parent process.
*/

int main(int argc, char **argv) {
	// 0 Variable declaration
	int id;
	int i;
	int *ptr; // Pointer

	// 1 Run a program to show information about shared memory
	// The -m option is to show only the active shared memory
	system("ipcs -m");

	// 2 Create some shared memory space of key 4567 (or 0x11d7), of size 4B
	// and of permission 660 (-rw-rw----)
	id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
	system("ipcs -m");

	// 3 Put the address of the shared memory segment of id id in the pointer
	ptr = (int *) shmat(id, NULL, 0);
	// 4 Change the value of the shared memory segment to 54
	*ptr = 42;
	i = 42;
	if (fork() == 0) {
		// Change the content of the shared memory
		(*ptr)++;
		i++;
		printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
		exit(0);
	} else {
		wait(NULL);
		/* When we print the value of ptr it should be the same as in the child,
		because we changed it in the shared memory, whereas the i was only 
		changed locally in the child */
		printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
		// Remove the shared memory segment
		shmctl(id, IPC_RMID, NULL);
	}
}