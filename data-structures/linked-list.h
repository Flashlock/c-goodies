#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../goodies.h"

typedef struct LLNode LLNode_t;
typedef struct LinkedList LinkedList_t;

struct LLNode{
	char* key;
	void* value;
	LLNode_t* next, * prev;
	int isHead, isTail;
};

struct LinkedList{
	LLNode_t* head, * tail;
	int size;
};


//---------CREATION/DESTRUCTION--------------//
LinkedList_t* createList();

void destroyList(LinkedList_t*);

LLNode_t* createLLNode(void*, char*);

//not gonna be written here.
void destroyLLNode(LLNode_t*);

//-------------INSERT, SEARCH, REMOVE-----------//
void appendList(LinkedList_t*, LLNode_t*);

void insertList(LinkedList_t*, LLNode_t*, int);

LLNode_t* searchList(LinkedList_t*, char*);

void removeList(LinkedList_t*, LLNode_t*);

//------------Manipulation------------------------//
void printList(LinkedList_t*);

void printLLNArray(LLNode_t**, int);

//not gonna be written in here
void printLLNode(LLNode_t*);

//WARNING: this will make the list unusable
LLNode_t** listToArray(LinkedList_t*);

void destroyLLNArray(LLNode_t**, int);

#endif