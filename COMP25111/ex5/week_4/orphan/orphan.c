// A demonstration of an orphan process

#include <stdlib.h>		// Libraries which may be needed
#include <stdio.h>
#include <unistd.h>

/*----------------------------------------------------------------------------*/

main (int argc, char *argv[])	// The 'root' programme; execution start
{
pid_t new_PID;				// PID return value from fork

printf("Hello from %s!\n", argv[0]);	// My name

new_PID = fork();			// Clone another process

if (new_PID < 0)
  {
  printf("ERROR: fork() failed\n");
  exit(1);
  }
else if (new_PID != 0)

  {					// Parent process
  int i;

  printf("Parent process %d run by process %d\n", getpid(), getppid());

  sleep(1);				// Wait for a short time

  printf("Parent terminating %d\n", getpid());

  exit(0);
  }

else

  {					// Child process
  printf("Child  process %d parent is %d\n", getpid(), getppid());

  sleep(3);				// Wait for a longer time

  printf("Orphaned Child %d adopted by process %d\n", getpid(), getppid());
  printf("Orphan terminating %d\n", getpid());

  exit(0);
  }
}

/*----------------------------------------------------------------------------*/
