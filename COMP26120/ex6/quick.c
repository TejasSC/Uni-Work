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
void swap(int* x, int* y){
  int t = *x;
  *x = *y;
  *y = t;
}
//Uses last element as pivot, places it at correct place in sorted array
//Then, puts all <= elements to the left of pivot, all > elements to right
int partition (int* arr, int low, int high) {
  int pivot = arr[high];//pivot is last element
  int i = low - 1;//index of smaller element
  int j;
  for (j = low; j < high; j++) {
    if (arr[j]<=pivot) {
      i++;//increment smaller element's index
      swap(&arr[i], &arr[j]);
    }
  }//for
  swap(&arr[i + 1], &arr[high]);
  return (i+1);//
}

void quickSort(int* someArr, int low, int high){
  if (low<high) {
    //ptn is partitioning index, someArr[ptn] at right place
    int ptn = partition(someArr, low, high);
    //sort elements before and after partition
    quickSort(someArr, low, ptn-1);
    quickSort(someArr, ptn+1, high);
  }
}//quickSort

int main() {
  int i, arrLength;
  if (scanf("%d", &arrLength) == 1 && arrLength > 0) {
    int testArr[arrLength];
    for (i = 0; i < arrLength; i++) {
      scanf("%d", &testArr[i]);
    }//for
    quickSort(testArr, 0, arrLength-1);
    printArray(testArr, arrLength);
    exit(0);
  } else {
    exit(1);
  }//if
  /*int x[4] = {1,4,3,2};
  printf("%d\n", sizeof(x));
  return 0;*/
}
