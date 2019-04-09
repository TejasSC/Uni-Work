#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define __USE_BSD // make prototype for strdup visible
#include <string.h>

typedef struct linkedlist { // linked list of ints (for use in Node)
  int index;
  struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
  char *name;
  List *outlist; // adjacency list
  int outdegree; // length of outlist
  int indegree; //how many edges are incident to this node
  double pagerank_score; //not needed for this exercise
  int explored;// for DFS and BFS
} Node;

//A graph is a collection of nodes
typedef struct {
  int MaxSize;
  Node* table;
} Graph;
/*
Here is an implementation of a Queue that you may wish to use in
part 2. You do not need to use it but if you do use it you will
need to be able to explain how it works and the complexity of
enqueue and dequeue
*/
typedef struct queue {
  // points to the first thing in the queue, next points back
  List* front;
  // points to the last thing in the queue, next will be NULL
  List* back;
} Queue;

// use to check result of strdup, malloc etc.
extern void check (void *memory, char *message);

// These functions have an int return type so that you can return
// a status indicating the success or otherwise of the function
// as is done in read_graph. You may change the functions to
// void if you wish to do so.

extern int initialize_graph (Graph *mygraph, int MaxSize);
extern int insert_graph_node (Graph *mygraph, int n, char *name);
extern int insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);
extern void free_graph(Graph *mygraph);
extern void enqueue(int n, Queue* q);
extern void dequeue(Queue* q);
extern Queue* makeQueue();
