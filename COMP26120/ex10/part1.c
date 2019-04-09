#include "graph.h"
#include <string.h>
#include <limits.h>

typedef struct queue {
  // points to the first thing in the queue, next points back
  List* front;
  // points to the last thing in the queue, next will be NULL
  List* back;
} Queue;

Queue* makeQueue()
{
  Queue* queue = malloc(sizeof(Queue));
  queue->front = NULL;
  queue->back = NULL;
  return queue;
}

void enqueue(int n, Queue* queue)
{
  List* new = malloc(sizeof(List));
  check(new, "Cannot enqueue");
  new->index = n;
  new->next = NULL;

  if(queue->back == NULL){
    //queue is empty
    queue->front = new;
    queue->back = new;
  }
  else{
    //queue.back->next will be NULL
    queue->back->next = new;
    queue->back = new;
  }
}
List* dequeue(Queue* queue)
{
  // queue is empty
  if(queue->front == NULL) return NULL;

  // shift front back
  List* ret = queue->front;
  queue->front = queue->front->next;

  // if eaten last thing tell back
  if(queue->front == NULL) queue->back=NULL;

  return ret;
}
List* temp;
//Recursive, uses FILO based stack structure
//add to front, remove from front
void depth_first_search(Graph* mygraph, int nodeIndex) {
  List* current = mygraph->table[nodeIndex].outlist;//current adj list
  //printf("%s has been discovered\n", mygraph->table[nodeIndex].name);
  mygraph->table[nodeIndex].explored = 1;//mark this node as visited

  //putting temp on the stack
  //not temp->next, but temp, otherwise algo fails on 1 element adj lists
  while (current != NULL) {
    //recursively call DFS algo on all unexplored nodes in adjacency list
    if (!(mygraph->table[current->index].explored)) {
      depth_first_search(mygraph, current->index);
    }//if
    current = current->next;//move onto the next one
  }//while
}//depth_first_search

int numReachable;
void Dijkstra_SP(Graph* mygraph, int nodeIndex, int* distances) {
  numReachable = 0;
  Queue* q = makeQueue();//for elements of adj lists
  mygraph->table[nodeIndex].explored = 1;
  enqueue(nodeIndex, q);
  while (q->front != NULL) {
    List* temp = dequeue(q);
    List* adjList = mygraph->table[temp->index].outlist;
    while (adjList!=NULL) {
      //if this node not visited, visit it and add to FIFO queue
      if (!(mygraph->table[adjList->index].explored)) {
        //update distance
        if (distances[temp->index] + 1 < distances[adjList->index])
          distances[adjList->index] = distances[temp->index] + 1;
        mygraph->table[adjList->index].explored = 1;//mark as visited
        numReachable++;
        enqueue(adjList->index, q);//enqueue
      }//if
      adjList = adjList->next;
    }//while
  }//while
  free(q);
}//Dijkstra_SP

double avgDistInts(int* distances, int length) {
  double sum = 0.0; int edges = 0;
  //Collect necessary information
  for (int j = 0; j < length; j++) {
    if (distances[j] != INT_MAX - 8) {
      sum += distances[j];
      edges++;
    }//if
  }//for
  return sum / (double) edges;
}//avgDist

double avgDistDoubles(double* distances, int length) {
  double sum = 0.0; int edges = 0;
  //Collect necessary information
  for (int j = 0; j < length; j++) {
    if (distances[j] != INT_MAX - 8) {
      sum += distances[j];
      edges++;
    }//if
  }//for
  return sum / (double) edges;
}//avgDist

int longest(int* distances, int length) {
  int max = 0;
  for (int j = 0; j < length; j++) {
    if (distances[j] != INT_MAX - 8) {
      if (distances[j] > max) {
        max = distances[j];
      }//if
    }//if
  }//for
  return max;
}//longest

int main(int argc, char *argv[]) {
  Graph mygraph;
  read_graph(&mygraph, argv[1]);
  printf("Max size is %d\n", mygraph.MaxSize);
  int* distances = malloc((mygraph.MaxSize + 1)*sizeof(int));
  double* avg_distances = malloc((mygraph.MaxSize + 1)*sizeof(double));
  int newmax = 0; int max = 0; int sumReachable = 0;
  //initialise distances and exploreds
  for (int i = 0; i < mygraph.MaxSize; i++) {
    for (int k = 0; k < mygraph.MaxSize; k++) {
      distances[k] = INT_MAX - 8;
      mygraph.table[k].explored = 0;
    }//for
    distances[i] = 0;
    Dijkstra_SP(&mygraph, i, distances);
    sumReachable += numReachable;
    //statistics variables
    double avg = avgDistInts(distances, mygraph.MaxSize);
    avg_distances[i] = avg;
    for (int j = 0; j < mygraph.MaxSize; j++) {
      newmax = longest(distances, mygraph.MaxSize);
      if (newmax > max) {
        max = newmax;
      }//if
    }//for
  }//for
  double avg = avgDistDoubles(avg_distances, mygraph.MaxSize);
  double connect = sumReachable / (double) (mygraph.MaxSize*mygraph.MaxSize);
  printf("\nLongest path: %d\n", max);
  printf("Average distance: %f\n", avg);
  //printf("Dijkstra time taken: %f\n", runtime_usage() - time);
  printf("Connectedness of graph: %f\n", connect);
  printf("For the file %s, ", argv[1]);
  printf("small-world property is %s\n", (max <= 6)?"proven":"disproved");

  free_graph(&mygraph);
  return(0);
}
