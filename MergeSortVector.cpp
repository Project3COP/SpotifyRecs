//
// Created by Maia Gervasone on 4/19/21.
//
#include <iostream>
#include <vector>
using namespace std;

//to print out the vector
void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

//merging left & right sub-vectors
vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    while ((int)left.size() > 0 || (int)right.size() > 0) {
        if ((int)left.size() > 0 && (int)right.size() > 0) {
            if ((int)left.front() <= (int)right.front()) {
                result.push_back((int)left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back((int)right.front());
                right.erase(right.begin());
            }
        }  else if ((int)left.size() > 0) {
            for (int i = 0; i < (int)left.size(); i++)
                result.push_back(left[i]);
            break;
        }  else if ((int)right.size() > 0) {
            for (int i = 0; i < (int)right.size(); i++)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
}

//merging the sub-vectors together
vector<int> mergeSort(vector<int> m)
{
    if (m.size() <= 1)
        return m;

    vector<int> left, right, result;
    int middle = ((int)m.size()+ 1) / 2;

    for (int i = 0; i < middle; i++) {
        left.push_back(m[i]);
    }

    for (int i = middle; i < (int)m.size(); i++) {
        right.push_back(m[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left, right);

    return result;
}

//songResults = songs we want to sort into the playlist
int main()
{
    vector<int> songResults;

    //push back the songs once we have that
    //songResults.pushback();

    //print unsorted array (for comparison)
    print(songResults);
    cout << "------------------" << endl;

    songResults = mergeSort(songResults);

    //print sorted array
    print(songResults);
}