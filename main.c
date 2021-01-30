#include "goodies.h"
#include "./data-structures/linked-list.h"
#include <stdlib.h>
#include <stdio.h>

void destroyLLNode(LLNode_t* node){
	//free(node -> value);
	free(node);
}

int main(void){
	LinkedList_t* list = createList();

	LLNode_t* node = createLLNode("austin", "austin");
	LLNode_t* node2 = createLLNode("betts", "betts");
	LLNode_t* node3 = createLLNode("insert", "insert");

	appendList(list, node);
	appendList(list, node2);
	insertList(list, node3, 1);


	destroyList(list);
	return 0;
}