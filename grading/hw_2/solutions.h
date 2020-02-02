#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

typedef struct {
    double x, y, z;
} Point;

/*!
keeps track of the sum of the arguments it 
has been called with over time. 
    \param a
*/
int running_total(int a);


/*!
takes an array and its length and reverses it 
in place
    \param arr
    \param len
*/
void reverse_in_place(int arr[], int len);


/*!
takes an array and its length and returns a new 
array that is the reverse of the given array. 
The function should use calloc to create space for 
the new array.
    \param a
    \param len
*/
int * reverse(int arr[], int len);


/*!
takes an array of integers, a length, and a 
value and returns the number of instances of 
that value in the array.
    \param arr
    \param len
    \param val
*/
int num_instances(int arr[], int len, int val);

/*!
 takes an array of Points, its length, and a 
 function pointer that returns a newly allocated 
 array whose values are the values of the 
 function argument applied to the array argument.
    \param arr
    \param len
    \param ptr
*/
Point * map(Point arr[], int len, Point (* func) (Point));

#endif