#include <stdio.h>
#include <stdlib.h>

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
	struct hole *prev;
} hole_t;

typedef struct {
	byte_t mem[SIZE];
	hole_t * anchor; // List of holes
} mem_t;

typedef struct variable {
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
	printf("Start of the project \n");
	mem_t *mem = initMem();
	printf("InitMem successful\n");
	address_t adr1 = myAlloc(mem, 5);
	address_t adr2 = myAlloc(mem, 10);
	address_t adr3 = myAlloc(mem, 100);
	printf("Allocations successful\n");

	// Release memory for addresses 1 and 2
	myFree(mem, adr2, 10);
	myFree(mem, adr1, 5);

	printf("Memory freeing successful\n");

	myWrite(mem, adr3, 543); // write on the 1st byte
	myWrite(mem, adr3+9, 34); // write on the 10th byte

	printf("Mem write successful\n");

	byte_t val1 = myRead(mem, adr3);
	byte_t val2 = myRead(mem, adr3+9);

	printf("Memory read successful\n");

	return 0;
}

/// Basic functions
hole_t * initHole(int size, address_t adr, hole_t * next, hole_t * prev){
	hole_t * trou = (hole_t*)malloc(sizeof(hole_t));

	trou->size = size;
	trou->adr = adr;
	trou->next = next;
	trou->prev = prev;

	return trou;
}

/// Implement functions
mem_t *initMem(){
	// 0 Variables
	mem_t * retour = (mem_t*)malloc(sizeof(mem_t));

	// 1 Initialize its contents
	retour->anchor = initHole(SIZE, 0, NULL, NULL);

	return retour;
}

address_t myAlloc(mem_t *mem, int size){
	//0 Variables
	hole_t * cursor = mem->anchor;
	address_t retour = -1;

	// 1 Find the first available hole of the right size
	char found = 0;
	while(!found && cursor){
		if(cursor->size >= size){
			found = 1;
		} else {
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
			if(cursor->prev) {
				cursor->prev->next = cursor->next;
			} else {
				mem->anchor = cursor->next;
			}
			free(cursor);
		}
	}

	return retour;
}

void myFree(mem_t *mem, address_t address, int size){
	// 0 Variables
	hole_t * cursor = mem->anchor;
	hole_t * prec = NULL;
	hole_t * new = NULL;

	// 1 We find the first hole after that address
	char found = 0;
	while(!found && cursor){
		if(cursor->adr >= address){
			found = 1;
		}
		else{
			prec = cursor;
			cursor = cursor->next;
		}
	}
	if(found)
		printf("myFree : Found hole\n");

	// 2 From there, 2 options :
	// 2.a The cursor is directly after the memory space to free
	if(cursor){
		if(found && cursor->adr == address + size){
			printf("myFree : case a\n");
			// We can simply extend it
			cursor->adr -= size;
			cursor->size += size;
			// Clean up
			if(prec){
				if(prec->adr + prec->size == cursor->adr - 1){
					prec->size += cursor->size;
					prec->next = cursor->next;
					if(cursor->next){
						cursor->next->prev = prec;
					}
					free(cursor);
				}
			}
		}
		// 2.b There is another variable between the one to free and the cursor
		// or there wasn't any hole between space to free and end of mem
		else if(found){
			printf("myFree : case b\n");
			// Then we create a new one
			// Either we have a hole after space to free
			
			new = initHole(size, address, cursor, cursor->prev);
			prec->next = new;
			cursor->prev = new;
		
			
			// 2.b.1 Clean up
			if(prec->adr + prec->size == new->adr - 1){
				// If prec and new are touching, augment prec and erase new
				prec->size += new->size;
				prec->next = new->next;
				if(new->next){
					new->next->prev = prec;
				}
				free(new);
			}
		}
	}
	else if(found){
		new = initHole(size, address, NULL, prec);
		prec->next = new;

		if(prec->adr + prec->size == new->adr - 1){
			// If prec and new are touching, augment prec and erase new
			prec->size += new->size;
			prec->next = new->next;
			if(new->next){
				new->next->prev = prec;
			}
			free(new);
		}
	}
}

void myWrite(mem_t *mp, address_t p, byte_t val){
	mp->mem[p] = val;
}

byte_t myRead(mem_t *mp, address_t p){
	return mp->mem[p];
}
