/*
Modify to test fewer or more cases.
No need to submit it as we'll supply one.
*/
#include "a1_question3.h" //function header

#include <stdio.h> //for console I/O
#include <stdlib.h> //for handling memory

//a helper function that compares 2 2D arrays, assuming same sizes
void checkAndPrint2DArrays(unsigned int row, unsigned int col,
                            int expected[][col], int** array) {
    for (int r=0; r<row; r++) {
        for (int c=0; c<col; c++) {
            if (expected[r][c] != array[r][c]) {
                printf("Different values at row %d col %d, FAIL\n", r, c);
            }
        }
    }

    //if reach this part, all are equal
    printf("All values are equal, PASS\n");
}

int main() {
    //the common way to create a 2D array
    int refArray[2][3] = {{0, -1, 2}, {999, -2345, -678}};

    //a different way to create a 2D array using pointer to a pointer array
	int** myArray = (int**) malloc(2*sizeof(int*)); //2 rows
    myArray[0] = (int*) malloc(3*sizeof(int)); //3 columns for the first row
    myArray[1] = (int*) malloc(3*sizeof(int)); //3 columns for the second row
    //fill out the array one-by-one
    myArray[0][0] = 0;
    myArray[0][1] = 1;
    myArray[0][2] = -2;
    myArray[1][0] = -999;
    myArray[1][1] = 2345;
    myArray[1][2] = 678;
    //print the array using the "normal" way
    printf("myArray before reversePolarity\n======\n");
    for (int i=0; i<2; i++) {
      for (int j=0; j<3; j++) {
        printf("%d ", myArray[i][j]);
      }
      printf("\n");
    }
    
    //call the function 
    reversePolarity(2, 3, myArray);
    
    printf("myArray after reversePolarity\n======\n");
    for (int i=0; i<2; i++) {
      for (int j=0; j<3; j++) {
        printf("%d ", myArray[i][j]);
      }
      printf("\n");
    }
    
    checkAndPrint2DArrays(2, 3, refArray, myArray);

    //clean up dynamic memory
    free(myArray[0]);
    free(myArray[1]);
    free(myArray);

    return 0;
}