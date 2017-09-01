/* 
	Author: Auro
 	29/08/2017

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define TMUT 0.08
#define MAX 10

typedef struct {
	double v[MAX], best;
} POP;


double f(double x) {
	if(x < 10) return x;
	return 10 - x;
}

POP *new_pop() {
	POP *new = (POP *) malloc(sizeof(POP));
	if(new == NULL) return NULL;
	int i;

	new->best = INT_MIN;
	
	for(i = 0; i < MAX; ++i) {
		new->v[i] = rand()%50;
		if(f(new->v[i]) > f(new->best)) new->best = new->v[i];
	}
	
	return new;
}

void evolution_pop(POP *pop) {
	if(pop == NULL) return;
	int i;
		
	for(i = 0; i < MAX; ++i) pop->v[i] = (pop->best + pop->v[i])/2;

	for(i = 0; i < MAX; ++i) 
		if(f(pop->v[i]) > f(pop->best)) pop->best = pop->v[i];
}


void mutate_pop(POP *pop) {
	if(pop == NULL) return;
	
	int signal = (rand()%2 == 1) ? -1 : 1;
	int index = rand()%MAX;
	
	pop->v[index] += pop->v[index] * signal * TMUT;
}

void destroy_pop(POP **pop) {
	if(*pop != NULL && pop != NULL) {
		free(*pop);
		*pop = NULL;
	}
}

enum {
	PROGNAME,
	NPOP
};
		
int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Invalid number of args in %s\n", argv[PROGNAME]);
		return -1;
	}

	srand(time(NULL));

	int counter = atoi(argv[NPOP]);


	POP *pop = new_pop();
	
	while(counter--) {
		evolution_pop(pop);
		mutate_pop(pop);
	}
	
	printf("%3lf\n", f(pop->best));

	destroy_pop(&pop);
	
	return 0;
}
			
