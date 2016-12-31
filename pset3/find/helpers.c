/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int low = 0, high = n;
    int midpoint = (low + high)/2;
    while (low <= high)
    {
        if (value == values[midpoint])
        {
            return true;
        }
        
        // check right half if value is greater than midpoint.
        else if (value > values[midpoint])
        {
            low = midpoint + 1;
        }
        
        // Check left half if value is less than midpoint.
        else if (value < values[midpoint])
        {
            high = midpoint - 1;
        }
        
        // Find new midpoint of the remaining half.
        midpoint = (low + high)/2;
    }
    
    // return false if value is not found.
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n; i++)
    {
        int temp = values[i];
        for (int j = i; j > 0; j--)
        {
            if (values[j] < values[j-1])
            {
                //temp = values[j];
                values[j] = values[j-1];
                values[j-1] = temp;
            }
        }
    }
}