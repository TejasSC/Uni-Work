#include<stdlib.h>
#include<string.h>
void main(int argc, char const *argv[]) {
  int *array1 = malloc(10*sizeof(int));
  int malloc0isNull;
  int *someShit = malloc(0);
  malloc0isNull = (NULL == 0);
  printf("%d\n", malloc0isNull);
  exit(1);
}
