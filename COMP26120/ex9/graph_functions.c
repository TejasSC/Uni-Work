#include "graph.h"
#include <string.h>
// Important: you do not need to allocate memory for
// mygraph. Currently this is already allocated on
// the stack in the stub for part1 and read_graph
// passes a pointer to this stack-allocated graph
// into this function
List *newNode, *last;//for inserting a graph link
int initialize_graph (Graph *mygraph, int MaxSize)
{
  mygraph->MaxSize = MaxSize;
  mygraph->table = (Node*) malloc(MaxSize*sizeof(Node));
  int i;
  for (i = 0; i < MaxSize; i++) {
    mygraph->table[i].outlist = NULL;
    mygraph->table[i].name = NULL;
    mygraph->table[i].outdegree = 0;
    mygraph->table[i].indegree = 0;
    mygraph->table[i].pagerank_score = 0.0;
    mygraph->table[i].explored = 0;
  }//initialise values each node within table
  return(0);
}
int insert_graph_node (Graph *mygraph, int n, char *name)
{
  //access table[n], initialize properties of new node
  n--;
  mygraph->table[n].name = strdup(name);
  mygraph->table[n].outlist = NULL;
  mygraph->table[n].outdegree = 0;
  mygraph->table[n].indegree = 0;
  mygraph->table[n].pagerank_score = 0.0;
  mygraph->table[n].explored = 0;
  return(0);
}
int insert_graph_link (Graph *mygraph, int source, int target)
{
  source--;//so it can fit in the array of nodes
  target--;
  mygraph->table[source].outdegree++;//one more outgoing link from source
  mygraph->table[target].indegree++;//one more incoming link to target
  newNode = (List*) malloc(sizeof(List));
  newNode->index = target;
  newNode->next = NULL;//finish creating new node
  last = mygraph->table[source].outlist;//insert at end, start at beginning
  if (last == NULL) {
    mygraph->table[source].outlist = newNode;//first item inserted this way
  } else {
    while (last->next != NULL) {
      last = last->next;
    }//keep going until end of list reached
    last->next = newNode;//put it here, at the end
  }
  return(0);
}
// use to check result of strdup, malloc etc.
void check (void *memory, char *message)
{
  if (memory == NULL)
  {
    fprintf (stderr, "Can't allocate memory for %s\n", message);
    exit (3);
  }
}
int read_graph (Graph *mygraph, char *filename)
/*
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph.
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command.
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command.
 * 8/2/2010 - JLS
 */
{
  FILE *fp;
  char command[80], name[80];
  int i, s, t;
  fp= fopen (filename, "r");
  if (fp==NULL)
  {
    fprintf(stderr,"cannot open file %s\n", filename);
    return -1;
  }
  printf ("Reading graph from %s\n", filename);
  fscanf (fp,"%s", command);
  if (strcmp (command, "MAX")!=0)
  {
    fprintf (stderr, "Error in graphics file format\n");
    fclose (fp);
    return -1;
  }
  else
  {
    fscanf (fp, "%d", &i);
    initialize_graph (mygraph, i+1); // +1 so nodes can be numbered 1..MAX
    while (fscanf (fp, "%s", command)!=EOF)
    {
      if (strcmp (command, "NODE")==0)
      {
        fscanf (fp, "%d %s", &i, name);
        insert_graph_node (mygraph, i, name);
      }
      else
      {
        if (strcmp (command, "EDGE")==0)
        {
          fscanf (fp, "%d %d", &s, &t);
          insert_graph_link (mygraph, s, t);
        }
        else
        {
          fclose (fp);
          return -1;
        }
      }
    }
  }
  fclose (fp);
  return 0;
}
void print_graph (Graph *mygraph)
/*
 * Prints out Graph *mygraph to the stdout in .gx format - JLS
 */
{
  int i;
  List *current;
  printf ("MAX %d\n", mygraph->MaxSize);
  for (i=0; i<mygraph->MaxSize; i++)
    if (mygraph->table[i].name!=NULL)
    {
      printf ("NODE %d %s\n", i, mygraph->table[i].name);
      current= mygraph->table[i].outlist;
      while (current!=NULL)
      {
        printf ("EDGE %d %d\n", i, current->index);
        current= current->next;
      }
    }
}

//cleans up memory
void free_graph (Graph *mygraph) {
  List* temp;
  for (int i = 0; i < mygraph->MaxSize; i++) {
    while (mygraph->table[i].outlist != NULL) {
      temp = mygraph->table[i].outlist;
      mygraph->table[i].outlist = mygraph->table[i].outlist->next;
      free(temp);
    }//while
    free(mygraph->table[i].name);
  }//free all the nodes's data and linked lists
  free(mygraph->table);
}//free_graph

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
void dequeue(Queue* queue)
{
  // queue is empty
  if(queue->front == NULL) return NULL;

  // shift front back
  List* ret = queue->front;
  queue->front = queue->front->next;

  // if eaten last thing tell back
  if(queue->front == NULL) queue->back=NULL;

  free( ret);
}
