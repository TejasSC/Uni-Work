// A demonstration of a zombie process

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

  printf("Parent process will have a sleep ...\n");

  sleep(10);				// Wait for a while

  printf("Parent terminating; O.S. will clean up.\n");

  exit(0);
  }

else

  {					// Child process
  printf("Child process  %d parent is %d\n", getpid(), getppid());

  sleep(1);				// Wait for a short time

  printf("Child exiting now; will be a zombie for a few seconds\n");

  exit(0);
  }
}

/*----------------------------------------------------------------------------*/
