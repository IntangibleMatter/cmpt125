/*
Header file for Assignment 1 Question 1.
Do not modify or submit.
*/
#ifndef _A1_QUESTION2_H_
#define _A1_QUESTION2_H_

#include <stdbool.h> //for the bool type

/*
A function that checks if the elements between the left and right index
(inclusive) in the int array are sorted in ascending order.
Fixes the left and right indexes first if any of them are invalid.
Input: array - the array to be checked
       size - the size of the array (assumed to be correct)
       leftIndex - the left boundary of the check
       rightIndex - the right boundary of the check
Returns: whether the range is sorted or not
*/
bool rangedCheckforSorted(int array[], unsigned int size,
                            int leftIndex, int rightIndex);

#endif