#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv){
//	FILE * file1 = fopen("text1.txt", "r");
//	FILE * file2 = fopen("text2.txt", "w");

	int fd1 = open("text1.txt", O_RDONLY);
	int fd2 = open("text2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);

	dup2(fd2, fileno(stdout));

	char tmp;
	while (read(fd1, &tmp, 1) == 1) 
		write(1, &tmp, 1);
/*
	if(file1 && file2){
		// We point standard output to text2.txt
		dup2(fileno(file2), fileno(stdout));

		// Create a loop that prints file1 to standard output
		char read;
		while(!feof(file1)){
			read = fgetc(file1);
			fprintf(stdout, "%c", read);
		}
		fclose(file1);
		fclose(file2);
	}
	else{
		printf("Problem with file openings");
	}
*/
	return 0;
}