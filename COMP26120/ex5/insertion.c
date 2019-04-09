#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void insertSortArr(int someArr[], int arrLength) {
  //select first unsorted element by assuming first element already sorted
  int i, j;
  int firstUnsorted;
  for (i = 1; i < arrLength; ++i){
    firstUnsorted = someArr[i];
    j = i-1;
    //moves all other elements to right...
    while(j >= 0 && someArr[j] > firstUnsorted) {
      someArr[j+1] = someArr[j];
      j--;
    }//while
    //...so that first unsorted element is now in correct place in the sorted array
    someArr[j+1] = firstUnsorted;
  }//for
}//insertSortArr

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
    insertSortArr(testArr, arrLength);
    printArray(testArr, arrLength);
    exit(0);
  } else {
    exit(1);
  }

}//main
