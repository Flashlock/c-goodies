#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _nullCheck(void *ptr){
	if(ptr == NULL){
		fprintf(stderr, "Null pointer exception");
		exit(1);
	}
}

// #region Creation and Destruction

LinkedList *create_list(){
	LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
	nullCheck(list);
	return list;
}

void destroy_list(LinkedList *list){
	clear_list(list);
	free(list);
}

LLNode *create_node(void *value){
	LLNode *node = (LLNode*) malloc(sizeof(LLNode));
	nullCheck(node);

	//put the goodies in the bag
	*node = (LLNode){
		.value = value,
		.next = NULL,
		.prev = NULL,
		.isHead = 0,
		.isTail = 0,
	};

	return node;
}

void destroy_node(LLNode *node){
	destroy_node_value(node -> value);
	free(node);
}

void clear_list(LinkedList *list){
	LLNode *curNode = list -> head;
	while(curNode != NULL){
		LLNode *next = curNode -> next;
		destroy_node(curNode);
		curNode = next;
	}
	list -> head = NULL;
	list -> tail = NULL;
	list -> size = 0;
}
// #endregion

// #region Insertion and Deletion

void append_node(LinkedList *list, LLNode *node){
	//is the list empty?
	if(list -> size == 0){
		list -> head = node;
		list -> tail = node;
		node -> isHead = 1;
		node -> isTail = 1;
	}
	else{
		list -> tail -> next = node;
		node -> prev = list -> tail;
		list -> tail -> isTail = 0;
		node -> isTail = 1;
		list -> tail = node;
	}

	list -> size++;
}

void insert_node(LinkedList *list, LLNode *node, int index){
	//can I append?
	if(index == list -> size){
		append_node(list, node);
	}
	//insert at top?
	else if(index == 0){
		list -> head -> isHead = 0;
		node -> next = list -> head;
		list -> head -> prev = node;
		node -> isHead = 1;
		list -> head = node;

		list -> size++;
	}
	//somewhere in the middle?
	else{
		LLNode *prevNode = list -> head;
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

void remove_node(LinkedList *list, LLNode *node){
	//empty the list
	if(node -> isHead && node -> isTail){
		list -> head = NULL;
		list -> tail = NULL;
	}

	//truncate?
	else if(node -> isHead){
		list -> head = node -> next;
		node -> next -> prev = NULL;
		list -> head -> isHead = 1;
	}
	else if(node -> isTail){
		list -> tail = node -> prev;
		node -> prev -> next = NULL;
		list -> tail -> isTail = 1;
	}
	//cinch maneuver
	else{
		node -> prev -> next = node -> next;
		node -> next -> prev = node -> prev;
	}

	*node = (LLNode){
		.isHead = 0,
		.isTail = 0,
		.next = NULL,
		.prev = NULL,
		.value = node -> value
	};
	list -> size--;
}
// #endregion

LLNode *find_node(LinkedList* list, void *match, int (*compareNode)(void *listValue, void *matchValue)){
	LLNode* curNode = list -> head;
	while(curNode != NULL){
		if(compareNode(curNode -> value, match)){
			return curNode;
		}
		curNode = curNode -> next;
	}
	return NULL;
}
