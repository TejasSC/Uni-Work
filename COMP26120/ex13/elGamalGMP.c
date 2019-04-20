#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

unsigned long result = 0;
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
  if (x == 0)
    return 1;//anything to power 0 is 1
  if (x%2==0) {
    result = fme(g, x/2, prime);//power is even, result = g^(x/2) mod prime
    return (result*result)%prime;
  }//if
  result = fme(g, (x-1)/2, prime);//power odd, result = g^((x-1)/2) mod prime
  return (g*((result*result)%prime))%prime;
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

double myRand (void){
  /* return a random float in the range [0,1] */
  return (double) rand() / RAND_MAX;
}

int main(int argc, char const *argv[]) {
  char buf1[80];//buffer for input
  char buf2[80]; char buf3[80];//buffers for sscanf as used below
  unsigned long g = 3; unsigned long prime = 65537;
  unsigned long y, message, k, a, b, p1, p2, next, nextFME;
  unsigned long privateKey, publicKey, typedPrivate, decrypted, check;
  // privateKey = 40000; message = 42069;
  // publicKey = fme(g, privateKey, prime);
  // do {
  //   //random number in between 1 and prime-1, needs to be relatively prime
  //   k = floor(myRand()*(prime-2)) + 1;
  //   result = hcf(prime - 1, k);
  //   //printf("result = %d\n", result);
  // } while(result != 1);
  // a = fme(g, k, prime); b = (message*fme(publicKey, k, prime))%prime;
  // next = imp(a, prime); nextFME = fme(next, privateKey, prime);
  // decrypted = (b * nextFME) % prime;
  // printf("message = %d\n", message);printf("decrypted = %d\n", decrypted);
  while (1) {
    printf("Prime modulus is %d\n", prime);
    printf("Primitive root wrt %d is %d\n", prime, g);
    printf("Choose: e (encrypt) | d (decrypt) | k (get public key) | x (exit)? ");
    get_string(buf1, buf2);

    if (strcmp(buf2, "e")==0) {
      /*
      ENCRYPTION
      */
      do {
        printf("\nType secret number to send: ");
        get_string(buf1, buf2);
        message = atol(buf2);//Secret number i.e. the message
      } while(message < 1 || message >= prime);
      do {
        printf("Type recipient's public key: ");
        get_string(buf1, buf2);
        y = atol(buf2);//public key
      } while(y != publicKey || y <= 0);
      do {
        //random number in between 1 and prime-1, needs to be relatively prime
        k = floor(myRand()*(prime-2)) + 1;
        check = hcf(prime - 1, k);
        //printf("result = %d\n", result);
      } while(check != 1);
      a = fme(g, k, prime); b = (message*fme(publicKey, k, prime))%prime;
      printf("The encrypted secret is: (%d, %d)\n\n", a, b);
    } else if (strcmp(buf2, "d")==0) {
      /*
      DECRYPTION
      */
      printf("\nType in received message in form (a,b): ");
      get_string_pair(buf1, buf2, buf3);
      p1 = atol(buf2);//pair element 1
      p2 = atol(buf3);//pair element 2
      do {
        printf("Type private key: ");
        get_string(buf1, buf2);
        typedPrivate = atol(buf2);
      } while(typedPrivate != privateKey);
      //M = M *(y^k) * (p1^privateKey)^-1 %p
      next = imp(a, prime); nextFME = fme(next, privateKey, prime);
      decrypted = (b * nextFME) % prime;
      //modular multiplicative inverse iff p1 is coprime with global prime
      if (hcf(p1, prime)==1) {
        printf("The decrypted secret is: %d\n\n", decrypted);
      } else {
        printf("Not able to decrypt message\n\n");
      }//if
    } else if (strcmp(buf2, "k")==0) {
      /*
      GETTING PUBLIC KEY
      */
      do {
        printf("Type private key: ");
        get_string(buf1, buf2);
        privateKey = atol(buf2);
      } while(privateKey >= prime - 1 || privateKey < 1);
      publicKey = fme(g, privateKey, prime);
      printf("Public key is %d\n\n", publicKey);
    } else if (strcmp(buf2, "x")==0){
      exit(0);//exiting
    } else {
      printf(">>>>>>>>>>>>>Not a valid option, try again<<<<<<<<<<<<<\n\n");
    }//if
  }//while
  return(0);
}//main
