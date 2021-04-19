#include <iostream>
#include "song.h"



int Shellsort(int arr[], int n)
{
/* From Lecture Slides on Shellsort in Module 6
 * 1. Set the initial value of gapto n / 2
 * 2. while gap > 0
 * 3. foreach array element from position gap to the last element
 * 4. Insert this element where it belongs in its subarray.
 * 5. if gap is 2, set it to 1
 * 6. else gap = gap / 2.2.
 */

    int gap = n/2;
    while(gap > 0)
    {
        for (int i = gap; i < n; i += 1)
        {
       
            int temp = arr[i];

            
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
        gap = gap/2;
    }
    return 0;
}


int main() {



}