#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>


void find_item(int* a, int len, int item) {
  for (int i=0;i<len;i++) {
    if (a[i] == item) {
        printf("***Item %d found in index %d\n", item, i);
        return;
      }
  }
  // if reached here, item not found
  printf("Item %d not found\n", item);
}


void find_duplicates(int* a, int len) {
  for (int i=0; i<len; i++)
    for (int j=0; j<i; j++)
      if (a[i] == a[j]) {
        printf("***The indices: %d, %d have the same value %d\n", i,j, a[i]);
        return;
      }
  printf("**** No duplicates found\n");
}


int main() {
  struct timeval current_time;

  int len = 20000; // increase this value to more and see how the time changes
  int* ar = malloc(len*sizeof(int));
  // fill the array with numbers
  for (unsigned int i=0; i<len; i++) 
    ar[i] = i*2;


  gettimeofday(&current_time, NULL);
  printf("seconds : %ld, micro seconds : %ld\n",
    current_time.tv_sec, current_time.tv_usec);


  find_item(ar, len, ar[len/2]); 
  gettimeofday(&current_time, NULL);
  printf("seconds : %ld, micro seconds : %ld\n",
    current_time.tv_sec, current_time.tv_usec);

  find_duplicates(ar, len); 

  gettimeofday(&current_time, NULL);
  printf("seconds : %ld, micro seconds : %ld\n",
    current_time.tv_sec, current_time.tv_usec);

  free(ar);
  
  return 0;
}