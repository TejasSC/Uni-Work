#include "graph.h"
#include <string.h>

int i, maxOut, minOut, currentNodeIndex, numReachable, indexMinOut;
Node nodeMaxOut, nodeMinOut;
maxOut = 0, minOut = 999;
List* temp;

//Recursive, uses FILO based stack structure
//add to front, remove from front
void depth_first_search(Graph* mygraph, int nodeIndex) {
  List* current = mygraph->table[nodeIndex].outlist;//current adj list

  numReachable++;
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

//non-recursive, uses FIFO based queue structure
//add to front, remove from back
void breadth_first_search(Graph* mygraph, int nodeIndex) {
  numReachable = 0;
  Queue* q = makeQueue();//for elements of adj lists
  //printf("%s has been discovered\n", mygraph->table[nodeIndex].name);
  mygraph->table[nodeIndex].explored = 1;//mark this node as visited
  numReachable++;

  //initialising the queue with 1st node's adjacency list
  List *adjacentNode = mygraph->table[nodeIndex].outlist;
  for (i = 0; i < mygraph->table[nodeIndex].outdegree; i++) {
    //One more reachable node if it's not been explored yet
    if(!mygraph->table[adjacentNode->index].explored){
      //printf("%s has been discovered\n", mygraph->table[adjacentNode->index].name);
      numReachable++;
      mygraph->table[adjacentNode->index].explored = 1;
      enqueue(adjacentNode->index, q);//put it in the queue
    }//if
    adjacentNode = adjacentNode->next;
  }//for

  currentNodeIndex = q->front->index;
  //keep going while q isn't empty
  while (q->front != NULL) {
    //temp = mygraph->table[currentNodeIndex].outlist;
    dequeue(q);
    for (i = 0; i < mygraph->table[currentNodeIndex].outdegree; i++) {
      //if this node not visited, visit it and add to FIFO queue
      if (!(mygraph->table[i].explored)) {
        //printf("%s has been discovered\n", mygraph->table[i].name);
        numReachable++;
        mygraph->table[i].explored = 1;
        enqueue(i, q);
      }//if
    }//for
  }//while 
  free(q);
}//breadth_first_search


int main(int argc, char *argv[]) {
  Graph mygraph;
  read_graph(&mygraph, argv[1]);
  for (i = 0; i < mygraph.MaxSize; i++) {
    //outdegree is the length of this node's adjacency list
    if (mygraph.table[i].outdegree > maxOut) {
      maxOut = mygraph.table[i].outdegree;
      nodeMaxOut = mygraph.table[i];
    }//update maxOut, nodeMaxOut
    if (mygraph.table[i].outdegree < minOut && mygraph.table[i].outdegree > 0) {
      minOut = mygraph.table[i].outdegree;
      nodeMinOut = mygraph.table[i];
      indexMinOut = i;
    }//update minOut, nodeMinOut
  }//for

  #ifdef BFS
    breadth_first_search(&mygraph, indexMinOut);
  #endif
  #ifdef DFS
    depth_first_search(&mygraph, indexMinOut);
  #endif

  printf("The node with the smallest (non-zero) out-degree is\n");
  printf("%s with out-degree %d\n", nodeMinOut.name, minOut);
  printf("There are %d nodes reachable from the node with the\n", numReachable);
  printf("smallest (non-zero) out-degree and the node with the\n");
  printf("largest out-degree is %s with out-degree %d", nodeMaxOut.name, maxOut);

  free_graph(&mygraph);
  return(0);
}
