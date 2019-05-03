#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long fme(unsigned long g, unsigned long x, unsigned long prime){
  unsigned long c = 0;
  unsigned long result = 1;
  unsigned long size = floor(log(x)/log(2)) + 1;
  int i;
  for (i = size-1; i >= 0; i--) {
    c *= 2;
    result = (result*result)%prime;//
    int bitis1 = (x & ( 1 << i )) >> i;//ith bit of x
    if (bitis1) {
      c++;
      result = (result*g)%prime;
    }//if
  }//for
  return result;
}//fme

/*
modular exponentiation: a one-way function because exponentiation is easily
computable but there does not exist a quick algorithm for recovering the
exponent, i.e computing discrete logarithms
- primitive roots (r) of prime number p are GENERATORS
-- applying multiplication on r many times (r^number), all elements in discrete
  group {1,...,p-1} are generated
- 'discrete' because no floating point numbers from the group can be made
calculates x where y = (g^x) mod p
*/
unsigned long dl(unsigned long y, unsigned long g, unsigned long prime) {
  //create space for discrete group and populate it
  int discreteGroup[prime - 1]; unsigned long result = -1;
  int i; int found = 0;
  for (i = 0; i < prime - 1; i++) {
    discreteGroup[i] = fme(g, i+1, prime);
    //printf("discreteGroup element %d: %d\n", i+1, discreteGroup[i]);
  }//for
  i = 0;
  while (i < prime - 1 && !found) {
    if (y == discreteGroup[i]) {
      result = i+1; found = 1;
    }//if
    i++;
  }//while
  return result;
}//dl

int main(int argc, char const *argv[]) {
  printf("fme(4,2,3) = %d\n", fme(4,2,3));
  printf("dl(1,4,3) = %d\n", dl(fme(4,2,3),4,3));
  return (0);
}
/*
RUNTIMES as function of sizes of y, g and p:
constant in size of g
- Reason:

linear in p, therefore <<<>>> in size of p
- Reason:

constant in size of y
- Reason:
*/
