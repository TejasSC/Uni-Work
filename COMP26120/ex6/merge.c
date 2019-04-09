#include<stdlib.h>
#include<stdio.h>
#include<string.h>
/* Function to print an array */
void printArray(int arr[], int size) {
  int i;
  for (i=0; i < size; i++) {
    printf("%d ", arr[i]);
  }//for
}//printArray

void mergeNumLists(int someArr[], int l, int m, int r) {
  int leftIndex, rightIndex, middleIndex;
  int sizeLeft, sizeRight;
  sizeLeft = m-l+1;//size of left array
  sizeRight = r-m;//size of right array
  int leftList[sizeLeft], rightList[sizeRight];//temporary arrays
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
    if (leftList[leftIndex] <= rightList[rightIndex]) {
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

void mergeSort(int someArr[], int left, int right){
  int m;//left, right, middle indexes
  if (left < right) {
    m = left+(right-left)/2;
    mergeSort(someArr, left, m);
    mergeSort(someArr, m+1, right);
    mergeNumLists(someArr, left, m, right);
  }//if
}//mergeSort

int main() {
  int i, arrLength;
  if (scanf("%d", &arrLength) == 1 && arrLength > 0) {
    int testArr[arrLength];
    for (i = 0; i < arrLength; i++) {
      scanf("%d", &testArr[i]);
    }//for
    mergeSort(testArr, 0, arrLength - 1);
    printArray(testArr, arrLength);
    return 0;
  }//if
}//main
