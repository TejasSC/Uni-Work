#include "graph.h"

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  int i, maxOut, maxIn, minIn;
  Node nodeMaxOut, nodeMaxIn, nodeMinIn;
  maxOut = 0, maxIn = 0, minIn = mygraph.MaxSize;

  for (i = 0; i < mygraph.MaxSize; i++) {
    if (mygraph.table[i].outdegree > maxOut) {
      maxOut = mygraph.table[i].outdegree;
      nodeMaxOut= mygraph.table[i];
    }//update maxOut, nodeMaxOut
    if (mygraph.table[i].indegree > maxIn) {
      maxIn = mygraph.table[i].indegree;
      nodeMaxIn = mygraph.table[i];
    }//update maxIn, nodeMaxIn
    if (mygraph.table[i].indegree < minIn && mygraph.table[i].indegree > 0) {
      minIn = mygraph.table[i].indegree;
      nodeMinIn = mygraph.table[i];
    }//update minIn, nodeMinIn
  }//for
  
  printf("Max out-degree is %d at node %s\n", maxOut, nodeMaxOut.name);
  printf("Max in-degree is %d at node %s\n", maxIn, nodeMaxIn.name);
  printf("Min in-degree is %d at node %s\n", minIn, nodeMinIn.name);

  free_graph(&mygraph);
  return(0);
}
