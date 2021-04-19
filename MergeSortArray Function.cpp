#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "song.h"
#include "playlist.h"
#include "Survey.h"
using namespace std;

void merge(song arr[], int left, int mid, int right) {
    int temp1 = mid - left + 1;
    int temp2 = right - mid;
 
    // Create temp arrays
    song L[temp1], R[temp2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < temp1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < temp2; j++) {
        R[j] = arr[mid + 1 + j];
    }
 
    // Merge the temp arrays:
    int i = 0;  //First subarray
    int j = 0;  //Second subarray
    int k = left;  //Merged subarray
 
    while (i < temp1 && j < temp2) {
        if (L[i].duration <= R[j].duration) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    //If there are any, copy the remaining elements of L[]
    while (i < temp1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    //If there are any, copy the remaining elements of R[]
    while (j < temp2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(song arr[], int left, int right) {
    if (left >= right) {
        return;  //returns recursively
    }
    int mid = left + (right - left)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

/*
int main()
{
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, SongCatalog.size());
    for(int i = 0; i < SongCatalog.size(); i ++)
    {
        cout << arr[i].duration << " ";
    }

    return 0;
}
*/
