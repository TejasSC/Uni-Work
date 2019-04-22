#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

mpz_t result; mpz_t remainder; mpz_init(remainder);
//Task 1: highest common factor
//computes highest common factor of a and b - euclid's algorithm
mpz_t hcf(mpz_t a, mpz_t b){
  if (mpz_cmp(b,0)==0) {
    return a;
  } else {
    mpz_mod(remainder, a, b);
    return hcf(b, remainder);
  }//if
}//hcf

//Task 2: fast modular exponentiation
//computes result = (g^x) mod prime, i.e. fast modular exponentiation
//Note: g < prime
mpz_t fme(mpz_t g, mpz_t x, mpz_t prime){
  mpz_mod(remainder, x, 2);
  if (mpz_cmp(x,0)==0)
    return 1;//anything to power 0 is 1
  if (mpz_cmp(remainder,0)==0) {
    //power is even, result = g^(x/2) mod prime
    mpz_divexact(x, x, 2);
    mpz_init_set(result, fme(g,x,prime));
    result = fme(g, x, prime);
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
mpz_t imp(mpz_t y, mpz_t prime){
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
  mpz_t g; mpz_t prime; mpz_init(g); mpz_init(prime);
  mpz_set_str(g, "3", 10); mpz_set_str(prime, "65537", 10);
  mpz_t y, message, k, a, b, p1, p2, next, nextFME;
  mpz_init(y); mpz_init(message); mpz_init(k); mpz_init(a); mpz_init(b);
  mpz_init(p1); mpz_init(p2); mpz_init(next); mpz_init(nextFME);
  mpz_t privateKey, publicKey, typedPrivate, decrypted;
  mpz_init(privateKey); mpz_init(publicKey); mpz_init(typedPrivate);
  mpz_init(decrypted);

  while (1) {
    gmp_printf("Prime modulus is %Zd\n", prime);
    gmp_printf("Primitive root wrt %Zd is %Zd\n", prime, g);
    gmp_printf("Choose: e (encrypt) | d (decrypt) | k (get public key) | x (exit)? ");
    get_string(buf1, buf2);

    if (strcmp(buf2, "e")==0) {
      /*
      ENCRYPTION
      */
      do {
        gmp_printf("\nType secret number to send: ");
        get_string(buf1, buf2);
        mpz_set_str(message, buf2, 10);//Secret number i.e. the message
      } while(mpz_cmp(message,1) < 0 || mpz_cmp(message,prime) >= 0);
      do {
        gmp_printf("Type recipient's public key: ");
        get_string(buf1, buf2);
        mpz_set_str(y, buf2, 10);//public key
      } while(mpz_cmp(y, publicKey)!=0);
      do {
        //random number in between 1 and prime-1, needs to be relatively prime
        k = floor(myRand()*(prime-2)) + 1;
        check = hcf(prime - 1, k);
        //gmp_printf("result = %Zd\n", result);
      } while(check != 1);
      a = fme(g, k, prime); b = (message*fme(publicKey, k, prime))%prime;
      gmp_printf("The encrypted secret is: (%Zd, %Zd)\n\n", a, b);
    } else if (strcmp(buf2, "d")==0) {
      /*
      DECRYPTION
      */
      gmp_printf("\nType in received message in form (a,b): ");
      get_string_pair(buf1, buf2, buf3);
      p1 = atol(buf2);//pair element 1
      p2 = atol(buf3);//pair element 2
      do {
        gmp_printf("Type private key: ");
        get_string(buf1, buf2);
        typedPrivate = atol(buf2);
      } while(typedPrivate != privateKey);
      //M = M *(y^k) * (p1^privateKey)^-1 %p
      next = imp(a, prime); nextFME = fme(next, privateKey, prime);
      decrypted = (b * nextFME) % prime;
      //modular multiplicative inverse iff p1 is coprime with global prime
      if (hcf(p1, prime)==1) {
        gmp_printf("The decrypted secret is: %Zd\n\n", decrypted);
      } else {
        gmp_printf("Not able to decrypt message\n\n");
      }//if
    } else if (strcmp(buf2, "k")==0) {
      /*
      GETTING PUBLIC KEY
      */
      do {
        gmp_printf("Type private key: ");
        get_string(buf1, buf2);
        privateKey = atol(buf2);
      } while(privateKey >= prime - 1 || privateKey < 1);
      publicKey = fme(g, privateKey, prime);
      gmp_printf("Public key is %Zd\n\n", publicKey);
    } else if (strcmp(buf2, "x")==0){
      exit(0);//exiting
    } else {
      gmp_printf(">>>>>>>>>>>>>Not a valid option, try again<<<<<<<<<<<<<\n\n");
    }//if
  }//while
  return(0);
}//main
