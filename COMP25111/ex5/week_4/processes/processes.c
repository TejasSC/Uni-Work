// A template for investigation process forking

#include <stdlib.h>		// Libraries which may be needed
#include <stdio.h>
#include <unistd.h>


main (int argc, char *argv[])	// The 'root' programme; execution start
{
pid_t new_PID;			// PID return value from fork

printf("Hello from %s!\n", argv[0]);// My name
printf("My PID is %d\n", getpid()); // My Unix identity

new_PID = fork();		// The call we are exercising
//Fork clones the process, now two processes are executing this file
//if copy is same process that made fork() call, value returned = new 'daughter'
//value
//If copy is newly created, value = 0

printf("That call returned the value %d to process %d\n", new_PID, getpid());

//Causes just daughter to run new program
//1st and 2nd arguments inputs to new process
//Final argument is a null string, i.e. pointer to \0 
if (new_PID == 0) execlp("./baby", "baby", (char*)NULL);

printf("Goodbye from %s with PID %d\n", argv[0], getpid());

exit(0);			// A way of stopping this process
				// The '0' indicates "okay"
}
