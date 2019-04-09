#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
//node stores element and height
struct node
{
  Key_Type element;
  tree_ptr left, right;
  int height;
};

struct table
{
  tree_ptr head; // points to the head of the tree
};

struct node* previousNode;//a reference to the parent pointer of...
struct node* currentNode;//...the current node

//default max function
int max(int a, int b) {
  return (a>b)?a:b;
}//max

Table initialize_table()
{
  //initialising root to null
  Table tableTree = (Table) malloc(sizeof(struct table));
  check(tableTree);
  tableTree -> head = NULL;
  return tableTree;
}//initialize_table

//getting the height of a tree
int getheight(struct node* thisNode) {
  if (thisNode == NULL) {
    return -1;
  }
  return 1 + max(getheight(thisNode->left), getheight(thisNode->right));
}//getheight

//creates a new node inside a table
struct node* makeNode(Key_Type str_kt, struct node* thisNode) {
  thisNode = (struct node*) malloc(sizeof(struct node));
  int len = strlen(str_kt);
  thisNode->element = malloc(sizeof(char)*(len+1));
  strcpy(thisNode->element, str_kt);
  thisNode->left = NULL;
  thisNode->right = NULL;
  thisNode->height = 0;
  return thisNode;
}//makeNode

//getBalance function - ideally should be -1, 0, or 1
int getBalance(struct node* thisNode) {
  if (thisNode == NULL) {
    return 0;
  }//else return difference between left and right subtrees
  return getheight(thisNode->left) - getheight(thisNode->right);
}

//function left-rotates subtrees
struct node* leftRotate(struct node* thisNode) {
  struct node* middle = thisNode->right;
  struct node* couldBeNull = middle->left;

  //perform left rotation
  thisNode->right = couldBeNull;
  middle->left = thisNode;
  //change the heights
  thisNode->height = max(getheight(thisNode->left), getheight(thisNode->right));
  middle->height = max(getheight(middle->left), getheight(middle->right));
  //return the 'middle' part/root
  return middle;
}//leftRotate

//function right-rotates subtrees
struct node* rightRotate(struct node* thisNode) {
  struct node* middle = thisNode->left;
  struct node* couldBeNull = middle->right;

  //perform left rotation
  thisNode->left = couldBeNull;
  middle->right = thisNode;
  //change the heights
  thisNode->height = max(getheight(thisNode->left), getheight(thisNode->right));
  middle->height = max(getheight(middle->left), getheight(middle->right));
  //return the 'middle' part/root
  return middle;
}//leftRotate

//insertTree function - inserts a value into a new node in unbalanced tree
struct node* insertTree(Key_Type str_kt, struct node* thisNode) {
  if (thisNode == NULL) {
    return(makeNode(str_kt, thisNode));
  }//if
  //if not null node, move along tree's subchildren
  if (strcmp(str_kt, thisNode->element) < 0) {
    thisNode->left = insertTree(str_kt, thisNode->left);
  } else if (strcmp(str_kt, thisNode->element) > 0) {
    thisNode->right = insertTree(str_kt, thisNode->right);
  } else {
    return thisNode;
  }//else
  return thisNode;
}//insertTree

//insertTreeAVL function - inserts a value into a new node in an AVL tree
struct node* insertTreeAVL(Key_Type str_kt, struct node* thisNode) {
  //
  if (thisNode == NULL) {
    return(makeNode(str_kt, thisNode));
  }
  //if not null node, move along tree's subchildren
  if (strcmp(str_kt, thisNode->element) < 0) {
    thisNode->left = insertTree(str_kt, thisNode->left);
  } else if (strcmp(str_kt, thisNode->element) > 0) {
    thisNode->right = insertTree(str_kt, thisNode->right);
  } else {
    return thisNode;
  }//else

  //must balance it like so
  thisNode->height = 1 + max(getheight(thisNode->left), getheight(thisNode->right));
  int balance = getBalance(thisNode);

  //These cases are for when the imbalance is too high or low
  //case left left - single rotation to the right
  if (balance > 1 && strcmp(str_kt, thisNode->left->element) < 0) {
    return rightRotate(thisNode);
  }
  //case right right - single rotation to the left
  if (balance < -1 && strcmp(str_kt, thisNode->right->element) > 0) {
    return leftRotate(thisNode);
  }
  //left right case - rotate middle node left, then rotate top node right
  if (balance > 1 && strcmp(str_kt, thisNode->left->element) > 0) {
    thisNode->left = leftRotate(thisNode->left);
    return rightRotate(thisNode);
  }
  if (balance < -1 && strcmp(str_kt, thisNode->right->element) < 0) {
    //right right case - rotate middle node right, then rotate top node left
    thisNode->right = rightRotate(thisNode->right);
    return leftRotate(thisNode);
  }
  return thisNode;
}//insertTreeAVL

//findTree function recursively finds an element in a tree - binary search
Boolean findTree(Key_Type str_kt, struct node* thisNode) {
  if (strcmp(str_kt, thisNode->element) < 0) {
    //search to the left if target is less than current node's elment
    return findTree(str_kt, thisNode->left);
  } else if (strcmp(str_kt, thisNode->element) > 0) {
    //search to the right if target is more than current node's elment
    return findTree(str_kt, thisNode->right);
  } else {
    //if element already at root, it's found
    return strcmp(str_kt, thisNode->element) == 0;
  }//else
}//findTree

//nodePrint function for printing one node
void nodePrint(struct node* someNode) {
  printf("%d:%s\n", getheight(someNode), someNode->element);
}//nodePrint
//printTree function recursively prints an element in a tree - pre order
void treePrint(struct node* someNode) {
  if (someNode != NULL) {
    //pre-order: act on root first, then go to + act on left & right children
    nodePrint(someNode);
    treePrint(someNode->left);
    treePrint(someNode->right);
  }//if
}//treePrint
void print_table(Table table)
{
  treePrint(table->head);
}//print_table

Table insert(Key_Type str_kt, Table table)
{
  //if the table is null, add the keytype
	if (table->head == NULL) {
    table->head = makeNode(str_kt, table->head);
	} else {
    //insert into the AVL tree within the table
    if (mode == 1) {
      table->head = insertTree(str_kt, table->head);
    } else if (mode == 2) {
      table->head = insertTreeAVL(str_kt, table->head);
    }//if
  }//else
  print_table(table);//debugging tool
  printf("\n");
  return table;
}//insert

Boolean find(Key_Type str_kt, Table table)
{
  if (table->head == NULL) {
    return FALSE;
  }//if
  return findTree(str_kt, table->head);
}//find

void freeNode(struct node* someNode) {
  free(someNode->element);
  free(someNode);
}//freeNode

//freeTree function to clean up the memory allocated for some nodes
void freeTree(struct node* someNode){
  if (someNode == NULL) {
    return;
  }//if
  //post order: act on all subtrees before root node
  freeTree(someNode->left);
  freeTree(someNode->right);
  freeNode(someNode);
}//freeTree

void tidy(Table table) {
  freeTree(table->head);//call freeTree function
  free(table);
}//tidy

void print_stats (Table table)
{
  printf("height: %d\n", getheight(table->head));
}//print_stats
