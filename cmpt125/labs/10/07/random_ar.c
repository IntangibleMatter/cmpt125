#include <stdio.h>  // for printf()
#include <stdlib.h> // for rand()
#include <time.h>   // for time()

/* Reads an integer len from stdin and returns a pointer to an array
   of integers of length len, containing random values between 0 and
   len-1 inclusive. Sets *reportlen (which must not be null) to indicate
   the length of the array. */
int* get_array_of_random_numbers(int* reportlen) {
  // user enters a number for the array length AND maximum value  
  printf( "Enter length of the array: " );
  
  int len=0;
  if( scanf("%d", &len) != 1 ) { // check I/O for errors
      perror("reading an integer failed");
      exit(1);
  }
  
  // explicitly allocate space for an array of ints
  int* arr = (int*) malloc(len*sizeof(int));
  
  if(arr==0) { // always check a system call for errors
      perror("allocating a random-length array failed");
      exit(1);
  }
  
  // fill the array with random numbers
  for (unsigned int i = 0; i < len; i++) 
    arr[i] = rand() % len;
  
  *reportlen = len;
  return arr;
}	

int main() {
  // intialize the random number generator with the current time in seconds
  srand(time(0));
  
  // I can't know in advance how long array will be
  int len=0;			
  int* array = get_array_of_random_numbers( &len );
  // len now holds the length of the array

  printf("[");
  for ( unsigned int i = 0; i < len; i++ )  			
    printf(" %d", array[i]);
  printf(" ]\n");
  
  // free the memory allocated by malloc
  free(array);

  return 0;
}	        