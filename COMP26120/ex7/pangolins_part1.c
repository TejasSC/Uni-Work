#include<stdlib.h>
#include<stdio.h>

//recursive data structure, binary tree
typedef struct node {
  char* questionName;
  char* objectName;
  struct node *yes_ptr;//pointer for correct guess
  struct node *no_ptr;//pointer for wrong guess
} node;

void nodePrint(node* someNode) {
  if (someNode->questionName == NULL) {
    printf("Question: [NOTHING]\n");
    printf("Object: %s\n", someNode->objectName);
  } else if (someNode->objectName == NULL) {
    printf("Object: [NOTHING]\n");
    printf("Question: %s\n", someNode->questionName);
    //printf("Yes: %s\n", someNode->yes_ptr->objectName);
    //printf("No: %s\n", someNode->no_ptr->objectName);

    if (someNode->yes_ptr->questionName == NULL) {
      printf("Yes: %s\n", someNode->yes_ptr->objectName);
    } else if (someNode->yes_ptr->objectName == NULL) {
      printf("Yes: %s\n", someNode->yes_ptr->questionName);
    }//if
    if (someNode->no_ptr->questionName == NULL) {
      printf("No: %s\n", someNode->no_ptr->objectName);
    } else if (someNode->no_ptr->objectName == NULL) {
      printf("No: %s\n", someNode->no_ptr->questionName);
    }//if

  }//if
  printf("\n");
}//nodePrint

void treePrint(node* someNode) {
  if (someNode != NULL) {
    //pre-order: act on root first, then go to + act on left & right children
    nodePrint(someNode);
    treePrint(someNode->yes_ptr);
    treePrint(someNode->no_ptr);
  }//if
}//treePrint
void freeTree(node* someNode) {
  if (someNode == NULL) {
    return;
  }//if
  //post order: act on all subtrees before root node
  freeTree(someNode->yes_ptr);
  freeTree(someNode->no_ptr);
  free(someNode);
}//freeTree

int main() {
  //create nodes
  struct node* root = (node*)malloc(sizeof(node));
  struct node* leftSub = (node*)malloc(sizeof(node));
  struct node* rightSub = (node*)malloc(sizeof(node));
  struct node* leaf1 = (node*)malloc(sizeof(node));
  struct node* leaf2 = (node*)malloc(sizeof(node));
  struct node* leaf3 = (node*)malloc(sizeof(node));
  struct node* leaf4 = (node*)malloc(sizeof(node));

  //make leaves external | whole tree (rather than just left subtrees) printed
  leaf1->yes_ptr = NULL;
  leaf1->no_ptr = NULL;
  leaf2->yes_ptr = NULL;
  leaf2->no_ptr = NULL;
  leaf3->yes_ptr = NULL;
  leaf3->no_ptr = NULL;
  leaf4->no_ptr = NULL;
  leaf4->yes_ptr = NULL;

  //connect them
  root->yes_ptr = leftSub;
  root->no_ptr = rightSub;
  leftSub->yes_ptr = leaf1;
  leftSub->no_ptr = leaf2;
  rightSub->yes_ptr = leaf3;
  rightSub->no_ptr = leaf4;

  //data for each node
  root->questionName = "Will it blend?";
  leftSub->questionName = "Will it bend?";
  rightSub->questionName = "Will it end?";
  leaf1->objectName = "iPhone 6";
  leaf2->objectName = "chocolate";
  leaf3->objectName = "film";
  leaf4->objectName = "loopyBoi";

  treePrint(root);//print the tree
  freeTree(root);//delete all of it
  return 0;
}
