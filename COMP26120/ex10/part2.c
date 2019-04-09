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
int numReachable;
//checks if target is found in someList
int found(List* someList, int target) {
  List* temp = someList;
  while (temp != NULL) {
    if (temp->index == target)
      return 1;
    temp = temp->next;
  }//while
  return 0;
}//check_in_list

//finds largest outdegree of a node in an adj list
int largest_OD_index(List* someList, Graph* mygraph){
  List* temp = someList; int maxOut = 0; int maxIndex;
  while (temp != NULL) {
    if (mygraph->table[temp->index].outdegree > maxOut) {
      maxOut = mygraph->table[temp->index].outdegree;
      maxIndex = temp->index;
    }//if
    temp = temp->next;
  }//while
  return maxIndex;
}//largest_OD_index


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

void Dijkstra_SP(Graph* mygraph, int nodeIndex, int* distances) {
  //printf("----------------------------------------------------------\n");
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
        enqueue(adjList->index, q);//enqueue
      }//if
      adjList = adjList->next;
    }//while
  }//while
  free(q);
}//Dijkstra_SP

//uses heuristic approach to calculate shortest path between source and target
int heuristics_BFS(Graph* mygraph, int source, int target) {
  Node current = mygraph->table[source];
  //no distance between same node
  if (source == target) {
    return 0;
  } else {
    int path = 0;
    //most likely source and target will not be equal
    if (found(current.outlist, target)) {
      return 1;//target in outlist therefore 1 edge away
    } else {
      path++;
      while (!found(current.outlist, target) && current.outlist != NULL) {
        path++;
        int maxOut = largest_OD_index(current.outlist, mygraph);
        current = mygraph->table[maxOut];
      }//while
      path++;
      return path;
    }//if
  }//if
}//heuristics_BFS

int main(int argc, char *argv[]) {
  Graph mygraph;
  read_graph(&mygraph, argv[1]);
  printf("Max size is %d\n", mygraph.MaxSize);
  int* distances_DSP = malloc((mygraph.MaxSize + 1)*sizeof(int));
  int* distances_H = malloc((mygraph.MaxSize + 1)*sizeof(int));
  double* avg_distances_DSP = malloc((mygraph.MaxSize + 1)*sizeof(double));

  double avg = 0.0;
  int sum_H = 0; int edges_H = 0;
  double avg_H = 0.0;
  //initialise distances and exploreds
  for (int i = 0; i < mygraph.MaxSize; i++) {
    for (int k = 0; k < mygraph.MaxSize; k++) {
      distances_DSP[k] = INT_MAX - 8;
      distances_H[k] = INT_MAX - 8;
      mygraph.table[k].explored = 0;
    }//for
    distances_DSP[i] = 0;
    distances_H[i] = 0;
    Dijkstra_SP(&mygraph, i, distances_DSP);
    //statistics variables
    double avg = avgDistInts(distances_DSP, mygraph.MaxSize);
    avg_distances_DSP[i] = avg;
    for (int k = 0; k < mygraph.MaxSize; k++) {
      printf("i = %d, k = %d\n", i,k);
      int dist_H = heuristics_BFS(&mygraph, i, k);
      if (dist_H != INT_MAX - 8) {
        sum_H += dist_H;
        edges_H++;
      }//if
    }//for
  }//for

  avg = avgDistDoubles(avg_distances_DSP, mygraph.MaxSize);
  printf("Using Dijkstra, avg shortest path is %f\n", avg);
  avg_H = sum_H / (double) edges_H;
  printf("Using heuristics, shortest path is %f\n", avg_H);

  free_graph(&mygraph);
  return(0);
}
