#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void main() {
  int i, arrLength;
  if (scanf("%d", &arrLength) == 1 && arrLength > 0) {
    int testArr[arrLength];
    for (i = 0; i < arrLength; i++) {
      scanf("%d", &testArr[i]);
    }
    int buckets[32768] = {0};
    int largest;
    //put each item in someArr in buckets
    for (i = 0; i < arrLength; i++) {
      buckets[testArr[i]] = testArr[i];
    }//for
    i = 0;
    for (i = 0; i < 32768; i++) {
      if (buckets[i] != 0) {
        printf("%d ", buckets[i]);
      }//if
    }//for
    exit(0);
  } else {
    exit(1);
  }
}
