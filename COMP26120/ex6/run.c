#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"string_helper.h"

/* Function to print an array */
void printArray(char* arr[], int size) {
  int i;
  for (i=0; i < size; i++) {
    printf("%s ", arr[i]);
  }//for
}//printArray

void mergeStringLists(char** someArr, int l, int m, int r) {
  int leftIndex, rightIndex, middleIndex;
  int sizeLeft, sizeRight;
  sizeLeft = m-l+1;//size of left array
  sizeRight = r-m;//size of right array
  char* leftList[sizeLeft];
  char* rightList[sizeRight];//temporary arrays
  //Copy data to temp arrays leftList and rightList
  for (leftIndex = 0; leftIndex < sizeLeft; leftIndex++) {
    leftList[leftIndex] = someArr[l+leftIndex];
  }//for
  for (rightIndex = 0; rightIndex < sizeRight; rightIndex++) {
    rightList[rightIndex] = someArr[m+1+rightIndex];
  }//for
  leftIndex = rightIndex = 0;//initial indexes of left and right arrays
  middleIndex = l;//initial index of merged array(which is someArr)
  while (leftIndex < sizeLeft && rightIndex < sizeRight) {
    if (strcmp(leftList[leftIndex], rightList[rightIndex]) <= 0) {
      someArr[middleIndex] = leftList[leftIndex];
      leftIndex++;
    } else {
      someArr[middleIndex] = rightList[rightIndex];
      rightIndex++;
    }//if
    middleIndex++;
  }//while
  // Copy the remaining elements of leftList[], if there are any
  while (leftIndex < sizeLeft) {
    someArr[middleIndex] = leftList[leftIndex];
    leftIndex++;
    middleIndex++;
  }//while
  // Copy the remaining elements of rightList[], if there are any
  while (rightIndex < sizeRight) {
    someArr[middleIndex] = rightList[rightIndex];
    rightIndex++;
    middleIndex++;
  }//while
}

void mergeSort(char **someArr, int left, int right){
  int m;//left, right, middle indexes
  if (left < right) {
    m = left+(right-left)/2;
    mergeSort(someArr, left, m);
    mergeSort(someArr, m+1, right);
    mergeStringLists(someArr, left, m, right);
  }//if
}//mergeSort

int main(int argc, char *argv[]) {
  int i, arrLength;
  if (scanf("%d\n", &arrLength) == 1 && arrLength > 0) {
    char** testArr = malloc(sizeof(char *)* arrLength);
    for (i = 0; i < arrLength; i++) {
      testArr[i] = get_next_string();
    }
    //scanf("%s ");
    mergeSort(testArr, 0, arrLength - 1);
    printf("\nSorted array is \n");
    printArray(testArr, arrLength);
    return 0;
  }//if
}
