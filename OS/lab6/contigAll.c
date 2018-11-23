#include <stdio.h>

#ifndef _MMU_H_
#define _MMU_H_
#endif

#define SIZE 65536


typedef short byte_t;
typedef int address_t;

typedef struct hole{
	address_t adr;
	int size;
	// Pointer for linked list
	struct hole *next;
} hole_t;

typedef struct {
	byte_t mem[SIZE];
	hole_t * anchor; // List of holes
} mem_t;

typedef variable{
	address_t adr;
	int size;
} variable_t;

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem();
// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAlloc(mem_t *mp, int size);
// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int size);
// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val);
// read memory from a byte
byte_t myRead(mem_t *mp, address_t p);


int main() {
	//0 Variables
	mem_t *mem = initMem();
	address_t adr1 = myAlloc(mem, 5);
	address_t adr2 = myAlloc(mem, 10);
	address_t adr3 = myAlloc(mem, 100);

	// Release memory for addresses 1 and 2
	myFree(mem, adr2, 10);
	myFree(mem, adr1, 5);

	myWrite(mem, adr3, 543); // write on the 1st byte
	myWrite(mem, adr3+9, 34); // write on the 10th byte

	byte_t val1 = myRead(mem, adr3);
	byte_t val2 = myRead(mem, adr3+9);

	return 0;
}

/// Basic functions
hole_t * initHole(int size, address_t adr, hole_t * next){
	hole_t * trou = (hole_t*)malloc(sizeof(hole_t));

	trou->size = size;
	trou->adr = adr;
	trou->next = next;

	return trou;
}

/// Implement functions
mem_t *initMem(){
	// 0 Variables
	mem_t * retour = (mem_t*)malloc(sizeof(mem_t));

	// 1 Initialize its contents
	retour->anchor = initHole(SIZE, 0, NULL);

	return retour;
}

address_t myAlloc(mem_t *mem, int size){
	//0 Variables
	hole_t * cursor = mem->anchor;
	hole_t * prec = NULL;
	address_t retour = -1;

	// 1 Find the first available hole of the right size
	char found = 0;
	while(!found && cursor){
		if(cursor->size >= size){
			found = 1;
		} else {
			prec = cursor;
			cursor = cursor->next;
		}
	}

	if(found){
		// 2 Store return address
		retour = cursor->adr;
		// 3 Reduce size of the hole
		cursor->adr += size;
		cursor->size -= size;

		// 4 If hole is now size 0 we erase it from the linked list
		if(cursor->size == 0){
			prec->next = cursor->next;
			free(cursor);
		}
	}

	return retour;
}

void myFree(mem_t *mem, address_t adress, int size){
	// 0 Variables

	// 1 We find the last hole before that address

	// 2 And extend it
}
