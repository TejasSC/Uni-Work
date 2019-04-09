#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i;//indexing elements of CLI list
  int posMax;//index of longest string
  int maxL = 0;//length of longest string
  if (argv == NULL) {
    printf("Can't work with null array");//will not work null arrays
  } else {
    if (argc == 1) {
      printf("Empty list of strings\n\n");//empty list cannot work
    } else {
      for (i = 1; i < argc; i++) {
        if (strlen(argv[i]) > maxL) {
          maxL = strlen(argv[i]);
          posMax = i;
        }//if
      }//for
      printf("%s", argv[posMax]);
    }//else
  }//else
  return 0;
}
