// C program to implement recursive Binary Search
#include <stdio.h>
#include <string.h>

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
char* binarySearch(char* arr[], int left, int right, char* x)
{
   if (right >= left)
   {
        int mid = left + (right - left)/2;

        // If the element is present at the middle
        // itself
        if (strcmp(arr[mid], x) == 0)
            return "yes";

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (strcmp(arr[mid], x) > 0)
            return binarySearch(arr, left, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, right, x);
   }

   // We reach here when element is not
   // present in array
   return "no";
}
