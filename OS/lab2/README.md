# Lab 2

## Description of the files

### questions1-2.c

This file contains the code that was given in the subject, with the answer to
question 1 in a comment block just before the main and comments for each part
of the code as required by question 2.

### sharedMemory.c

This file contains the code for section 2 of the lab, using shared memmory spaces
to communicate between processes.
Synchronization between processes is achieved using
`wait(NULL);`
in the parent process to wait for the exectuion of the childs before accessing shared
memory spaces.

### pipes.c

This file contains the code for section 2 of the lab, this time using pipes to insure
both communication and synchronization between processes.
