#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LLNode{
	void* value;
	struct LLNode* next, * prev;
	int isHead, isTail;
}LLNode;

typedef struct LinkedList{
	struct LLNode* head, * tail;
	int size;
}LinkedList;

// #region Creation and Destruction

// Creates a new Linked List struct.
LinkedList *create_list();

// Frees all list memory.
void destroy_list(LinkedList *);

// Creates a new Node.
LLNode* create_node(void *);

// Frees node memory.
void destroy_node(LLNode*);

// Frees all the nodes from the list.
void clear_list(LinkedList*);

// User Implemented: free node value as necessary. 
void destroy_node_value(void*);
// #endregion

// #region Insertion and Removal

// Appends a node to the end of the list.
void append_node(LinkedList *, LLNode *);

// Inserts a node at the given index.
void insert_node(LinkedList *, LLNode *, int);

// Removes a node from the list.
void remove_node(LinkedList *, LLNode *);
// #endregion

// Finds a node, return NULL if not found. Compare Nodes returns 1 if the node values match.
LLNode *find_node(LinkedList *, void *, int (*compareNodes)(void *, void *));

#endif