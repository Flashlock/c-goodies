#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//-------------CREATION/DESTRUCTION-------------------//
LinkedList_t* createList(){
	LinkedList_t* list = (LinkedList_t*) malloc(sizeof(LinkedList_t));
	memCheck(list);
	return list;
}

void destroyList(LinkedList_t* list){
	assert(list != NULL);

	//free all the nodes
	LLNode_t* currNode = list -> head;
	while(currNode != NULL){
		LLNode_t* next = currNode -> next;
		destroyLLNode(currNode);
		currNode = next;
	}

	//free the list
	free(list);
}

LLNode_t* createLLNode(void* value, char* key){
	assert(value != NULL);
	assert(key != NULL);

	LLNode_t* node = (LLNode_t*) malloc(sizeof(LLNode_t));
	memCheck(node);

	//put the goodies in the bag
	*node = (LLNode_t){
		key,				//key
		value,				//value
		NULL,				//next
		NULL,				//prev
		FALSE,				//isHead
		FALSE,				//isTail
	};

	return node;
}

//------------------INSERT, SEARCH, REMOVE------------//
void appendList(LinkedList_t* list, LLNode_t* node){
	assert(list != NULL);
	assert(node != NULL);

	//is the list empty?
	if(list -> size == 0){
		list -> head = node;
		list -> tail = node;
		node -> isHead = TRUE;
		node -> isTail = TRUE;
	}
	else{
		list -> tail -> next = node;
		node -> prev = list -> tail;
		list -> tail -> isTail = FALSE;
		node -> isTail = TRUE;
		list -> tail = node;
	}

	list -> size++;
}

void insertList(LinkedList_t* list, LLNode_t* node, int index){
	assert(list != NULL);
	assert(node != NULL);
	assert(index <= list -> size);

	//can I append?
	if(index == list -> size){
		appendList(list, node);
	}
	//insert at top?
	else if(index == 0){
		list -> head -> isHead = FALSE;
		node -> next = list -> head;
		list -> head -> prev = node;
		node -> isHead = TRUE;
		list -> head = node;

		list -> size++;
	}
	//somewhere in the middle?
	else{
		LLNode_t* prevNode = list -> head;
		for(int i = 0; i < index - 1; i++){
			prevNode = prevNode -> next;
		}

		node -> next = prevNode -> next;
		node -> next -> prev = node;

		prevNode -> next = node;
		node -> prev = prevNode;

		list -> size++;
	}
}

LLNode_t* searchList(LinkedList_t* list, char* key){
	assert(list != NULL);
	LLNode_t* currNode = list -> head;
	while(currNode != NULL){
		if(strcmp(currNode -> key, key) == 0){
			return &(*currNode);
		}
		currNode = currNode -> next;
	}

	return NULL;
}

void removeList(LinkedList_t* list, LLNode_t* node){
	assert(list != NULL);
	assert(node != NULL);

	//does the node exist in the given list?
	LLNode_t* exists = searchList(list, node -> key);
	if(exists == NULL){
		fprintf(stderr, "Node absent from list - failed remove\n");
		exit(EXIT_FAILURE);
	}

	//empty the list
	if(node -> isHead && node -> isTail){
		list -> head = NULL;
		list -> tail = NULL;
	}

	//truncate?
	else if(node -> isHead){
		list -> head = node -> next;
		node -> next -> prev = NULL;
		list -> head -> isHead = TRUE;
	}
	else if(node -> isTail){
		list -> tail = node -> prev;
		node -> prev -> next = NULL;
		list -> tail -> isTail = TRUE;
	}
	//cinch maneuver
	else{
		node -> prev -> next = node -> next;
		node -> next -> prev = node -> prev;
	}

	list -> size--;
}

//--------------MANIPULATION-----------------//
void printList(LinkedList_t* list){
	LLNode_t* currNode = list -> head;
	while(currNode != NULL){
		printf("%s > ", currNode -> key);
		currNode = currNode -> next;
	}
	printf("NULL\n");
}