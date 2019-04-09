//------------------------------------------------------------------------------
// A template for the first investigation into variables and pointers in C

#include <stdlib.h>		// Libraries which may be needed
#include <stdio.h>

void method_1(int x);		// Take on trust for the moment

int glob_1, glob_2;		// Globally scoped variables
//char test;

//------------------------------------------------------------------------------

main (int argc, char *argv[]) {	// The 'root' programme; execution start

  int local_1, local_2;		// Variables local to 'main'
  int *ptr_1, *ptr_2;

  printf("Memory investigation programme\n");

  glob_1  = 0x12345678;		// Put a distinctive value in a variable
  local_1 = 0xABCDEF;		// ... and again
  glob_2 = 0x69420;
  ptr_1 = &glob_1; //ptr_1 holds address of variable glob_1 as data
  //ptr_1 is an alias for address
  ptr_2 = 0x90; //holds address 0x90
//  *ptr_2 = 17;
  printf("Variable glob_2 contains data %08X\n", glob_2);
  printf("Variable local_1 is alias for address %016X\n", &local_1);
  printf("Variable local_2 is alias for address %016X\n", &local_2);

  method_1(local_1);		// Call something, with an argument
  printf("\nSize of glob_1: %d\n", sizeof(glob_1));
  printf("Variable glob_1 at address %016X contains data %08X\n", &glob_1,
         glob_1);
  printf("Size of ptr_1: %d\n", sizeof(ptr_1));
  printf("Variable ptr_1 at address %016X contains data %08X\n", &ptr_1,
         ptr_1);
  printf("Size of ptr_2: %d\n", sizeof(ptr_2));
  printf("Variable ptr_2 at address %016X contains data %08X\n", &ptr_2,
         ptr_2);//holds data which is address 00000090

  printf("Size of main: %d\n", sizeof(main));
  printf("Size of method_1: %d\n", sizeof(method_1));
  printf("\nThat's all folks\n");

  exit(0);
}

//------------------------------------------------------------------------------

void method_1(int arg_1) {	// Declare a function

  int meth_int_1;			// Declare an alias for a particular address space

  meth_int_1 = 0xDEADBEEF;	// Another distinctive hex value
  printf("\nSTART METHOD 1\n");
  printf("Variable arg_1   contains data %08X\n", arg_1);
  printf("Variable arg_1 has address %016X\n", &arg_1);
  printf("Variable meth_int_1 contains data %08X\n", meth_int_1);
  printf("Variable meth_int_1 has address %016X\n", &meth_int_1);
  printf("END METHOD 1\n");

  return;
}

//==============================================================================
