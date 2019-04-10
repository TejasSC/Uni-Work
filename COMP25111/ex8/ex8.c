#include <stdlib.h>			// Libraries which may be needed
#include <stdio.h>
#include <signal.h>

struct sigaction sigaction_structure;	// A data structure, filled in below
void goodbye();
int num;//global variable

//following intercepts the SIGQUIT unix signal
int main(int argc, char *argv[]) {
  sigaction_structure.sa_handler = &goodbye;	// Pointer to a -function-
  sigemptyset(&sigaction_structure.sa_mask);	// Call defines 'empty' field
  sigaction_structure.sa_flags   = 0;		// No flags

  //Ctrl + |
  // Link the structure to signal "SIGQUIT" (as generated by ^C)
  sigaction(SIGQUIT, &sigaction_structure, NULL); // Link
  num = 0;

  while (1) num++;			// Everlasting loop!
  exit(0);
}
void goodbye(int signum) {
  printf("\nGoodbye at count %d\n", num);
  exit(1);
}