#include <stdio.h>
#include <stdlib.h>

#define LEN 10

// try entering name shorter/longer than LEN
void get_name( char line[], int maxlen ) {
  printf("Please enter your name: ");

  // reads at most maxlen-1 chars from stdin, up to first newline, EOF or error.
  if( fgets( line, maxlen, stdin ) == 0 ) { // we ALWAYS check for I/O errors
    perror("failed to read a name");
    exit(1);
  }
}	

int main() {

  char name[LEN];
  get_name(name, LEN);

  // we don't need to be lucky this time
  printf("Your name is %s", name );

  return 0;
}	       
