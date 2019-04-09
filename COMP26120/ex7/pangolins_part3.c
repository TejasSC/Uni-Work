#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 80

//recursive data structure, binary tree
enum qOrA {question, answer};
typedef union info {
  char* questionName;
  char* objectName;
} info;
typedef struct node {
  enum qOrA question_or_answer;
  info infoType;
  struct node *yes_ptr;//pointer for correct guess
  struct node *no_ptr;//pointer for wrong guess
} node;

// void nodePrint(node* someNode) {
//   if (someNode->question_or_answer == question) {
//     printf("Object: [NOTHING]\n");
//     printf("Question: %s\n", someNode->infoType.questionName);
//     if (someNode->yes_ptr->question_or_answer == question) {
//       printf("Yes: %s\n", someNode->yes_ptr->infoType.questionName);
//     } else {
//       printf("Yes: %s\n", someNode->yes_ptr->infoType.objectName);
//     }//if
//     if (someNode->no_ptr->question_or_answer == question) {
//       printf("No: %s\n", someNode->no_ptr->infoType.questionName);
//     } else {
//       printf("No: %s\n", someNode->no_ptr->infoType.objectName);
//     }//if
//   } else {
//     printf("Question: [NOTHING]\n");
//     printf("Object: %s\n", someNode->infoType.objectName);
//   }//if
//   printf("\n");
// }//nodePrint

void freeNode(node* someNode) {
  if (someNode->question_or_answer == question) {
    free(someNode->infoType.questionName);
  } else {
    free(someNode->infoType.objectName);
  }//if
  free(someNode);
}

void freeTree(node* someNode) {
  if (someNode == NULL) {
    return;
  }//if
  //post order: act on all subtrees before root node
  freeTree(someNode->yes_ptr);
  freeTree(someNode->no_ptr);
  freeNode(someNode);
}//freeTree

void treePrint(node* someNode) {
  if (someNode != NULL) {
    //pre-order: act on root first, then go to + act on left & right children
    if (someNode->question_or_answer = question) {
      printf("question: %s\n", someNode->infoType.questionName);
      treePrint(someNode->yes_ptr);
      treePrint(someNode->no_ptr);
    } else {
      printf("object: %s\n", someNode->infoType.objectName);
    }//if
  }//if
}//treePrint

node* treeRead(FILE* fp, char buf1[], char type[], char descr[]) {
  if (fgets(buf1, 80, fp) == 0) {
    return NULL;
  } else {
    sscanf(buf1, "%s %[^\t\n]", type, descr);
    node* somePtr = (node*)malloc(sizeof(node));
    if (strcmp(type, "question:") == 0) {
      someQuestion = fillNode(0, descr);
      //read yes and no subtrees
      someNode->yes_ptr = treeRead(fp, buf1, type, descr);
      someNode->no_ptr = treeRead(fp, buf1, type, descr);
    } else {
      somePtr = fillNode(1, descr);
    }
  }
}//treeRead

node* fillNode(int type, char someInfo[]){
  node* someNode = (node*)malloc(sizeof(node));
  someNode->question_or_answer = type;
  int len = strlen(someInfo);
  if (type == question) {
    someNode->infoType.questionName = malloc(sizeof(char)*(len+1));
    strcpy(someNode->infoType.questionName, someInfo);
  } else if (type == answer) {
    someNode->infoType.objectName = malloc(sizeof(char)*(len+1));
    strcpy(someNode->infoType.objectName, someInfo);
    //make it a leaf
    someNode->yes_ptr = NULL;
    someNode->no_ptr = NULL;
  }//if
  return someNode;
}//makeNode

int matchYes(char str[]) {
  return strcmp(str, "Yes") == 0 || strcmp(str, "yes") == 0
      || strcmp(str, "y") == 0 || strcmp(str, "Y") == 0
      || strcmp(str, "Correct") == 0 || strcmp(str, "correct") == 0;
}//matchYes

int matchNo(char str[]) {
  return strcmp(str, "No") == 0 || strcmp(str, "no") == 0
      || strcmp(str, "n") == 0 || strcmp(str, "N") == 0
      || strcmp(str, "Incorrect") == 0 || strcmp(str, "incorrect") == 0;
}//matchYes

//tests if node is leaf or not
int isLeaf(node* someNode) {
  return someNode->yes_ptr == NULL && someNode->no_ptr == NULL;
}//leaf

void get_string(char str1[], char str2[]) {
  fgets(str1, 80, stdin);
  sscanf(str1, "%[^\t\n]", str2);
}//get_string

int main(int argc, char const *argv[]) {
  char buf1[SIZE];//buffer for input
  char buf2[SIZE];//buffer for sscanf as used below
  node* pangolin = fillNode(1, "a pangolin");
  node* root = pangolin;//initialise root
  node* currentNode = root;//set currentNode to root
  node* previousNode = root;//previousNode, behind currentNode
  int playing, playingRound;
  playing = 1;
  while (playing) {
    playingRound = 1;
    while (playing && playingRound) {
      if (isLeaf(currentNode)) {
        //make the guess
        printf("Is it %s?\n>", currentNode->infoType.objectName);
        get_string(buf1, buf2);
        if (matchYes(buf2) == 1) {
          //computer has won
          printf("Good. That was easy.\n\n");
          break;
        } else {
          // if (currentNode->question_or_answer == question) {
          //   printf("currentNode at %s\n", currentNode->infoType.questionName);
          // } else {
          //   printf("currentNode at %s\n", currentNode->infoType.objectName);
          // }
          //say user has won
          printf("Oh. Well you win then -- What were you thinking of?\n>");
          get_string(buf1, buf2);
          //take user question
          //COPY entire data to newNode
          //change currentNode data to that question
          node* newObject = fillNode(1, buf2);
          //ask objectName and question
          printf("Please give me a question about %s, ", newObject->infoType.objectName);
          printf("so I can tell the difference between %s and %s.\n>",
                  newObject->infoType.objectName, currentNode->infoType.objectName);
          get_string(buf1, buf2);
          node* newQuestion = fillNode(0, buf2);
          //insert newQuestion and newObject into tree
          printf("What is the answer for %s?\n>", newObject->infoType.objectName);
          get_string(buf1, buf2);
          if (root->question_or_answer == answer) {
            root = newQuestion;
            //defining answers for question we just made
            if (matchNo(buf2) == 1) {
              root->no_ptr = newObject;
              root->yes_ptr = pangolin;
            } else {
              root->yes_ptr = newObject;
              root->no_ptr = pangolin;
            }//if
          } else {
            //defining answers for question we just made
            if (matchNo(buf2) == 1) {
              newQuestion->no_ptr = newObject;
              newQuestion->yes_ptr = currentNode;
            } else {
              newQuestion->yes_ptr = newObject;
              newQuestion->no_ptr = currentNode;
            }//if
            //reattach the previousNode's pointer to the question
            if (previousNode->yes_ptr == currentNode) {
              previousNode->yes_ptr = newQuestion;
            } else if (previousNode->no_ptr == currentNode) {
              previousNode->no_ptr = newQuestion;
            }//else
          }
          printf("Thanks\n");
          playingRound = 0;
        }
      } else {
        //If not a leaf, ask the question
        previousNode = currentNode;
        printf("%s\n", currentNode->infoType.questionName);
        //set current node according to yes/no response
        get_string(buf1, buf2);
        if (matchYes(buf2) == 1) {
          currentNode = currentNode->yes_ptr;
        } else {
          currentNode = currentNode->no_ptr;
        }//if
      }//else LEAF CHECK
    }//FINISHED ROUND AT THIS POINT
    printf("Would you like to play again?\n");
    get_string(buf1, buf2);
    if (matchYes(buf2) == 1) {
      currentNode = root;
      previousNode = root;
    } else {
      playing = 0;
    }//if
  }//while
  treePrint(root);
  freeTree(root);
  return 0;
}
