#include <stdio.h>
#include <stdlib.h>

#ifndef _MMU_H_
#define _MMU_H_
#endif

#define SIZE 65536
#define PAGE_SIZE 128
#define TABLE_SIZE SIZE/PAGE_SIZE

// What allocation algorithm to use
#define FIRST_FIT 'A'
#define ALLOC_ALGO FIRST_FIT

/* ============= Data Strcutures ==================== */

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
	byte_t mem[PAGE_SIZE];
	hole_t * anchor; // List of holes
} mem_t;

typedef struct variable {
	address_t adr;
	int size;
	// What page this variable is located on
	address_t page;
} variable_t;

typedef struct table {
	/* This structure contains a table of correspondance
	between a "virtual memory" and a "physical memory" */
	address_t physical[TABLE_SIZE];
	// There is no page at the start, so each pointer to a page is NULL
	mem_t * virtual[TABLE_SIZE];
} table_t;

typedef struct pageSystem {
	/* Correspondance
	This structure implements a correspondance system between the
	virtual and physical memory using the table
	*/
	table_t table;
	byte_t physicalMemory[SIZE];
} pageSystem_t;


/* ================ Function prototypes =================*/

/*
	This section contains all of the public prototypes which are 
	allowed in the main
*/
// Dynamically allocate a page system
pageSystem_t * initPageSystem();
// Create a variable in the page system and return it
variable_t * allocateVariable(pageSystem_t * ps, int size);
// Free a variable
void freeMemory(pageSystem_t * ps, variable_t * variable);
// Read a variable
byte_t * readVariable(pageSystem_t * ps, variable_t variable);
// Write to a variable
void writeVariable(pageSystem_t * ps, byte_t * toWrite, variable_t variable);

/* 
	These are the "private functions" which will not be used in the main,
	but instead be called by the "public functions"
*/
// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem();
// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAlloc(mem_t *mp, int size);
// 
address_t myAllocFirstFit(mem_t *mem, int size);
// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int size);
// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val);
// read memory from a byte
byte_t myRead(mem_t *mp, address_t p);
//
mem_t * createPage(pageSystem_t * ps, int i);

int main() {
	//0 Variables
	byte_t toWrite[1] = {1};
	printf("Start of the program \n");
	pageSystem_t * ps = initPageSystem();

	printf("Initialization successful\n");
	variable_t * v1 = allocateVariable(ps, 1);
	variable_t * v2 = allocateVariable(ps, 120);
	variable_t * v3 = allocateVariable(ps, 40);
	printf("Allocations successful\n");
	if(!v1)
		printf("V1 is null\n");
	printf("V1 : %i\t%i\t%i\n", v1->adr, v1->size, v1->page);
	// Write into v1
	writeVariable(ps, toWrite, *v1);

	// Read v1
	printf("v1 == %i\n", *readVariable(ps, *v1));

	// Free variable
	freeMemory(ps, v1);

	// Read v1
	printf("v1 == %i\n", *readVariable(ps, *v1));

	return 0;
}

pageSystem_t * initPageSystem() {
	int i;

	pageSystem_t * ps = (pageSystem_t*)malloc(sizeof(pageSystem_t));

	for(i = 0; i < TABLE_SIZE; i++)
		ps->table.virtual[i] = NULL;

	return ps;
}

variable_t * allocateVariable(pageSystem_t * ps, int size) {
	// 0 Variables
	variable_t * variable = (variable_t*)malloc(sizeof(variable_t));
	variable->size = size;
	mem_t * page = NULL;
	address_t adr = -1;
	int i; // loop variable

	// 1 We look for space in one of the current pages to create the
	// variable
	for(i = 0; i < TABLE_SIZE; i++) {
		page = ps->table.virtual[i];

		if(page){
			adr = myAlloc(page, size);
			if(adr != -1) {
				// If adr is not -1, then myAlloc managed to find a page, and we can proceed
				break;
			}
		}
	}
	// 2 If we couldn't allocate our variable to any of the exitsting pages, 
	if(adr == -1) {
		// 2.0 We find the first NULL page pointer in the page tab
		char found = 0;
		for(i = 0; i < TABLE_SIZE; i++) {
			if(!ps->table.virtual[i]){
				found = 1;
				break;
			}
		}
		// If we haven't found any page with a big enough empty space, we give up
		if(!found) {
			printf("Haven't found any page :'( \n");
			return NULL;
		}
		// 2.1 We initialize a new page in the empty spot
		page = createPage(ps, i);
		// 2.2 We allocate the variable to it
		adr = myAlloc(page, size);
	}
	// 3 Now that we initialized our variable, we finish the return variable
	variable->adr = adr;
	variable->page = i;
	return variable;
}

void freeMemory(pageSystem_t * ps, variable_t * variable) {
	// We free the variable in the memory
	myFree(ps->table.virtual[variable->page], variable->adr, variable->size);
	// We turn its address to -1 to make sure 
	variable->adr = -1;
}

byte_t * readVariable(pageSystem_t * ps, variable_t variable) {
	// 0 Variables
	byte_t * returnVariable = (byte_t*)malloc(sizeof(variable.size));
	int i;

	// If the variable is not allocated, exit
	if(variable.adr == -1)
		return NULL;
	// 1 We fill the return variable with what we find in physical memory
	for(i = 0; i < variable.size; i++) {
		returnVariable[i] = ps->physicalMemory
			[variable.page * PAGE_SIZE + variable.adr + i];
	}

	return returnVariable;
}

void writeVariable(pageSystem_t * ps, byte_t * toWrite, variable_t variable) {
	int i;

	for(i = 0; i < variable.size; i++) {
		ps->physicalMemory[variable.page*PAGE_SIZE + variable.adr+ i]
			= toWrite[i];
	}
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
mem_t * initMem(){
	// 0 Variables
	mem_t * retour = (mem_t*)malloc(sizeof(mem_t));

	// 1 Initialize its contents
	retour->anchor = initHole(SIZE, 0, NULL, NULL);

	return retour;
}

address_t myAlloc(mem_t * mem, int size) {
	if(ALLOC_ALGO == FIRST_FIT) {
		return myAllocFirstFit(mem, size);
	}
}

address_t myAllocFirstFit(mem_t *mem, int size){
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
			if(cursor->next){
				cursor->next->prev = cursor->prev;
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
	

	// 2 From there, 2 options :
	// 2.a The cursor is directly after the memory space to free
	if(cursor && found){
		if(cursor->adr == address + size){
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
		else {
			// Then we create a new one
			// Either we have a hole after space to free
			
			new = initHole(size, address, cursor, prec);
			if(prec)
				prec->next = new;
			else
				mem->anchor = new;
			cursor->prev = new;
			
			// 2.b.1 Clean up
			if(prec){
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
	}
	// If we didn't find any hole after the memory space to delete, we create one
	else{
		new = initHole(size, address, NULL, prec);
		if(prec){
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
}

void myWrite(mem_t *mp, address_t p, byte_t val){
	mp->mem[p] = val;
}

byte_t myRead(mem_t *mp, address_t p){
	return mp->mem[p];
}

// 
mem_t * createPage(pageSystem_t * ps, int i) {
	ps->table.virtual[i] = initMem();
	ps->table.physical[i] = i * PAGE_SIZE;

	return ps->table.virtual[i];
}
