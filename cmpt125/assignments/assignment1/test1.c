/*
Modify to test fewer or more cases.
No need to submit it as we'll supply one.
*/
#include "a1_question1.h" //function header

#include <stdio.h> //for console I/O

//a helper function that compares 2 ints
void checkAndPrintInts(int expected, int result) {
    if (expected != result) {
        printf("Different values: %d vs %d, FAIL\n", expected, result);
    } else {
        printf("Values are equal, PASS\n");
    }
}

int main() {
    //function should return 2
    checkAndPrintInts(2, replaceDigits(1, '1', '2'));

    //function should return -202
    checkAndPrintInts(-202, replaceDigits(-232, '3', '0'));

    //function should return 123
    checkAndPrintInts(123, replaceDigits(123, '4', '5'));

    //function should return 1223
    checkAndPrintInts(1223, replaceDigits(1223, '!', '?'));

    //function should return 670
    checkAndPrintInts(670, replaceDigits(5670, '5', '0'));

    //function should return 39499
    checkAndPrintInts(39499, replaceDigits(30400, '0', '9'));

    return 0;
}