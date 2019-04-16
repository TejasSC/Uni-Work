#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Task 1: highest common factor
//computes highest common factor of a and b - euclid's algorithm
unsigned long hcf(unsigned long a, unsigned long b){
  unsigned long remainder;
  if (b == 0) {
    return a;
  } else {
    remainder = a%b;
    return hcf(b, remainder);
  }//if
}//hcf

//Task 2: fast modular exponentiation
//computes result = (g^x) mod prime, i.e. fast modular exponentiation
//Note: g < prime
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
<<<<COME BACK TO THIS, NOT FINISHED THE EXPLANATIONS YET>>>>
RUNTIMES as function of sizes g, x, and prime:
linear in size of x
- Reason: x = sumAll(x(i)*(2^i)), 0 <= i <= size-1
- Therefore a^x = productAll(a^(x(i)*(2^i)))
- a^(x(i)*(2^i)) = 1 if x(i) == 0, a^(2^i) if x(i) == 1
- Iterating over size(x), with 'size' iterations total

*/

//Task 4: inverse modulo prime
//Use fermat's little theorem to find the multiplicative inverse of y mod p
unsigned long imp(unsigned long y, unsigned long prime){
  return fme(y, prime - 2, prime);// FLT: y^(p-1) = 1 mod p = result * y
}//imp
/*
<<<<COME BACK TO THIS, NOT FINISHED THE EXPLANATIONS YET>>>>
RUNTIMES as function of sizes of y and p:
- linear in the size of prime, since in fme, x = prime - 2
- <<<<<< in the size of y, since in fme, g = y
*/

int main(int argc, char const *argv[]) {
  unsigned long testFME = fme(2, 5, 7);
  unsigned long testHCF = hcf(42, 28);
  unsigned long a = 3; unsigned long b = 4;
  unsigned long testIMP1 = imp(a, 11);
  unsigned long testIMP2 = imp(b, 11);
  printf("value of testFME: %d\n", testFME);
  printf("value of testHCF: %d\n", testHCF);
  if (testIMP1 == b && testIMP2 == a) {
    printf("Value of testIMP1 is %d\n", testIMP1);
    printf("Value of testIMP2 is %d\n", testIMP2);
  }
  return 0;
}//main
