#include <stdio.h> // FILE stderr fopen fclose fprintf printf fgets
#include <ctype.h>

#define MAX 1000000
// All occurences of MAX are replaced with the corresponding number

static void invertLetters(char *inFile, char *outFile) {
  char space[MAX];
  int c;
  size_t n = 0;
  FILE *stream= fopen(inFile, "r");
  if (!stream) {
    fprintf(stderr, "can't open the given file for reading\n");
  } else {
    while ((c = fgetc(stream)) != EOF) {
      space[n++] = (char) c;
    }
    space[n] = '\0';
    int j = 0;
    int uC = 0; // count of new upper case characters
    int lC = 0; // count of new lower case characters
    for (j = 0; j < n; j++) {
      if (isupper(space[j])) {
        space[j] = putchar(tolower(space[j]));
        lC++;
      } else {
        space[j] = putchar(toupper(space[j]));
        uC++;
      }//if
    }//for
    printf("\nRead %d characters in total, %d converted to upper-case, %d to lower-case\n", n, uC, lC);
    FILE *output = fopen(outFile, "w");
    fprintf(output, "%s\n", space);
  }//if
}//invertLetters

int main(int argc, char **argv) {
  char in[MAX], out[MAX];

  printf("Enter input filename: ");
  scanf("%s\n", in);
  printf("Enter output filename: ");
  scanf("%s\n", out);

  invertLetters(in, out);
  return 0;
}
