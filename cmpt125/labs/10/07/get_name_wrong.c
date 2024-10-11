#include <stdio.h>
#include <stdlib.h>

#define LEN 10
// WHY IS THIS WRONG?
char* get_name() {
  printf("Please enter your name: ");

  // should be enough space for a name
  char line[LEN];
  
  // reads at most LEN chars from stdin, up to first newline, 
  // EOF or error.
  if( fgets( line, LEN, stdin ) == 0 ) // we ALWAYS check for I/O errors
  {
    perror("failed to read a name");
    exit(1);
  }
  
  return line; 
}	

int main( void ) {
  char* name = get_name();

  // works if we are *lucky*
  printf("Your name is %s\n", name);

  return 0;
}	       
