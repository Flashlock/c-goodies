#include "goodies.h"
#include <stdlib.h>
#include <stdio.h>

void memCheck(void* ptr){
	if(ptr == NULL){
		fprintf(stderr, "Failed allocation\n");
		exit(EXIT_FAILURE);
	}
}