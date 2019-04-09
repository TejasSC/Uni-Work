#include <stdio.h>
#include <string.h>

float c2f (float c) {
  return ((9.0/5.0)*c + 32);
}//c2f
float f2c (float f) {
  return ((5.0/9.0)*(f - 32));
}//f2c
int main(int argc, char *argv[]) {
  float testVal, resultTemp;//declaring input and output values to use later
  if (argc != 3) {
    printf("Wrong number of arguments supplied\n");
    exit(1);//if there's not 3 arguments supplied
  } else if (sscanf(argv[2], "%f", &testVal) == 0) {
    printf("Malformed number in second param\n");
    exit(3);//
  } else if (testVal < -273.15) {
    printf("Absolute zero value cannot be exceeded\n");
    exit(4);
  } else {
    if (strcmp(argv[1], "-c")==0) {
      resultTemp = c2f(testVal);
      printf("%.2f°C = %.2f°F", testVal, resultTemp);
    } else if (strcmp(argv[1], "-f")==0) {
      resultTemp = f2c(testVal);
      printf("%.2f°C = %.2f°F", resultTemp, testVal);
    } else {
      printf("Invalid temp style given\n");
      exit(2);
    }//else
  }//else
}//main
