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
  //to increase from 0 to x, where result = (g^c) mod prime, throughout algo
  unsigned long c = 0;
  unsigned long result = 1;
  //change of base law to get log with base 2
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
RUNTIMES as function of sizes g, x, and prime:
linear in size of x
- Reason: x = sumAll(x(i)*(2^i)), 0 <= i <= size-1
- Therefore a^x = productAll(a^(x(i)*(2^i)))
- a^(x(i)*(2^i)) = 1 if x(i) == 0, a^(2^i) if x(i) == 1
- Iterating over size(x), with 'size' iterations total

constant in the size of prime and g
- Reason: number of operations involving prime is worst case 2*size(x), and
  with g is size(x)
- therefore number of bits of prime number and g do not affect the runtime in
  the size of prime and g
*/

//Task 4: inverse modulo prime
//Use fermat's little theorem to find the multiplicative inverse of y mod p
unsigned long imp(unsigned long y, unsigned long prime){
  return fme(y, prime - 2, prime);// FLT: y^(p-1) = 1 mod p = result * y
}//imp
/*
RUNTIMES as function of sizes of y and p:
- linear in the size of prime, since in fme, x = prime - 2
- constant in the size of y, since in fme, g = y
*/

void get_string(char str1[], char str2[]) {
  fgets(str1, 80, stdin);
  sscanf(str1, "%[^\t\n]", str2);
}//get_string

void get_string_pair(char str1[], char str2[], char str3[]) {
  fgets(str1, 80, stdin);
  sscanf(str1, "(%[^\t\n], %[^\t\n])", str2, str3);
}//get_string

float myRand (void){
  /* return a random float in the range [0,1] */
  return (float) rand() / RAND_MAX;
}

int main(int argc, char const *argv[]) {
  char buf1[80];//buffer for input
  char buf2[80]; char buf3[80];//buffers for sscanf as used below
  unsigned long g = 3; unsigned long p = 65537;
  printf("Prime modulus is %d\n", p);
  printf("Primitive root wrt %d is %d\n", p, g);
  printf("Choose: e (encrypt) | d (decrypt) | k (get public key) | x (exit)? ");
  get_string(buf1, buf2);

  if (strcmp(buf2, "e")==0) {
    //Encryption
    printf("\nType secret number to send: ");
    get_string(buf1, buf2);
    unsigned long m = atol(buf2);//Secret number i.e. the message
    printf("Type recipient's public key: ");
    get_string(buf1, buf2);
    unsigned long y = atol(buf2);//public key
    unsigned long k = floor(myRand()*(p-1)) + 1;//random number in between
    printf(">>>>>value of k: %d>>>>>\n", k);
    unsigned long a = fme(g, k, p); unsigned long b = fme(m*y, k, p);
    printf("The encrypted secret is: (%d, %d)\n", a, b);
  } else if (strcmp(buf2, "d")==0) {
    //Decryption
    printf("\nType in received message in form (a,b): ");
    get_string_pair(buf1, buf2, buf3);
    unsigned long p1 = atol(buf2);//pair element 1
    unsigned long p2 = atol(buf3);//pair element 2
    printf("Type private key: ");
    get_string(buf1, buf2);
    unsigned long privateKey = atol(buf2);
    unsigned long publicKey = fme(g, privateKey, p);
    unsigned long decrypted = imp(g, publicKey);
    printf("\nThe decrypted secret is: %d\n", decrypted);
  } else if (strcmp(buf2, "k")==0) {
    //Getting public key
    printf("Type private key: ");
    get_string(buf1, buf2);
    unsigned long privateKey = atol(buf2);
    unsigned long publicKey = fme(g, privateKey, p);
    printf("Public key is %d", publicKey);
  } else if (strcmp(buf2, "x")==0){
    exit(0);//exiting
  }//if
  return(0);
}//main
