#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void bubbleSortArr(int someArr[], int arrLength) {
  int isSorted;
  isSorted = 0;//initially false
  int lastUnsorted;//optimization avoids checking already sorted elements
  lastUnsorted = arrLength - 1;
  int i;//indexer
  while (!isSorted) {
    isSorted = 1;//set to true before pass begins
    for (i = 0; i < lastUnsorted; i++) {
      if (someArr[i] > someArr[i+1]) {
        swap(someArr, i, i + 1);
        isSorted = 0;
      }//if
    }//for
  }//while
}//bubbleSortArr

//swap method - need an auxiliary variable 'hold'
void swap(int someArr[], int i, int j) {
  int hold;
  hold = someArr[i];
  someArr[i] = someArr[j];
  someArr[j] = hold;
}//swap

/* Function to print an array */
void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++) {
      printf("%d ", arr[i]);
    }//for
}//printArray

void main() {
  int i, arrLength;
  if (scanf("%d", &arrLength) == 1 && arrLength > 0) {
    int testArr[arrLength];
    for (i = 0; i < arrLength; i++) {
      scanf("%d", &testArr[i]);
    }
    bubbleSortArr(testArr, arrLength);
    printArray(testArr, arrLength);
    exit(0);
  } else {
    exit(1);
  }

}//main
