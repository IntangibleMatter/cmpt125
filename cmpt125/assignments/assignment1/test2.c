/*
Modify to test fewer or more cases.
No need to submit it as we'll supply one.
*/
#include "a1_question2.h" //function header

#include <stdio.h> //for console I/O
#include <stdbool.h> //for the bool type

//a helper function that compares 2 bools
void checkAndPrintBools(bool expected, bool result) {
    if (expected != result) {
        printf("Different values, FAIL\n");
    } else {
        printf("Values are equal, PASS\n");
    }
}

int main() {
    int myIntArray[] = {-4, 3, -12, 0, 5, 72, 88, 128, 1, 64};

    //function should return false
    checkAndPrintBools(false, rangedCheckforSorted(myIntArray, 10, -2, 3));

    //function should return true
    checkAndPrintBools(true, rangedCheckforSorted(myIntArray, 10, 7, 2));

    //function should return true
    checkAndPrintBools(true, rangedCheckforSorted(myIntArray, 10, 5, 5));

    //function should return false
    checkAndPrintBools(false, rangedCheckforSorted(myIntArray, 10, 0, 9));

    return 0;
}