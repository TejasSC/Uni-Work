// A template for 'piping' between processes

#include <stdlib.h>		// Libraries which are needed
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


main (int argc, char *argv[])	// The 'root' programme; execution start
{
pid_t new_PID;			// PID return value from fork
int   pipefd[2];		// Pipe ends identifier from call

printf("Hello from '%s'\n", argv[0]);// My name

pipe(pipefd);			// Create a pipe; record 'handles'

new_PID = fork();		// Split into two processes

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (new_PID != 0)
//Sends string 'message' using write() call to new pipe input end('1')
  {					// Parent process: transmitter
  int bytes_written;
  char *message = "Hello World!";	// Traditional message :-)

  sleep(1);				// Pauses for a second to let child get ahead

  printf("Parent to send message\n");

  bytes_written = write(pipefd[1], message, strlen(message) + 1);
			// The " + 1" is to include the string terminator

  printf("Bytes written: %d\n", bytes_written);
  }

else
//second branch immediately tries to read() from output '0' end of pipe
//waits until something is there
//new input directed to buffer
  {					// Child process: receiver
  char buffer[20];			// Somewhere to put the input
  int  bytes_read;

  printf("    Child waiting for message\n");

  bytes_read = read(pipefd[0], buffer, 20);// Read from pipe into "buffer"

  if (bytes_read == -1) printf("    Error: %d\n", errno);
  else                { printf("    Bytes read: %d\n", bytes_read);
                        printf("    Received string: %s\n", buffer); }

  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  printf("Goodbye from process %d\n", getpid());

  //unix pipes unidrectional, need to create another on to pass data in opposite way
  pid_t new_PID2;			// PID return value from fork

  printf("Hello from '%s'\n", argv[1]);// Chlid name

  pipe(pipefd);			// Create a pipe; record 'handles'

  //Duplicate lines given if this is included
  //new_PID2 = fork();		// Split into two processes

  if (new_PID != 0) {
    int bytes_written_child;
    char *childMsg = "Hi Mum and Dad!";

    sleep(1); //lets parent get ahead

    printf("Child to reply to parent's message\n");
    //including +1 for string terminator character
    bytes_written_child = write(pipefd[0], childMsg, strlen(childMsg) + 1);

    printf("Bytes written: %d\n", bytes_written_child);

  } else {
    printf("Parent waiting for message\n");
    char parrentBuff[20];
    int bytes_read_by_parent;

    bytes_read_by_parent = read(pipefd[1], parrentBuff, 20);
    if (bytes_read_by_parent == -1) printf("    Error: %d\n", errno);
    else                { printf("    Bytes read: %d\n", bytes_read_by_parent);
                          printf("    Received string: %s\n", parrentBuff); }
  }//if
  exit(0);
}

//------------------------------------------------------------------------------
