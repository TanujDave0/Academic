/*util.cpp*/

#include <iostream>

#include "ourvector.h"

using namespace std;


//
// findIndexOfSmallestValue:
//
// Given a vector and a starting position, finds the index of
// the smallest value in the range [start, last], where last is
// vector.size()-1.  That index is returned.
//
int findIndexOfSmallestValue(ourvector<int>& V, int start) {
   for (int i = start; i < V.size(); i++) {
       if (V.at(i) < V.at(start)) {
           start = i;
       }
   }
   return start;
}

//
// merge:
//
// merge assumes we are given a vector V with 2 portions, each in 
// sorted order:  [low, mid] and [mid+1, high].  The merge function
// then merges these two portions into one sorted list [low, high]
// back into the given vector V.
//
// NOTE: a 2nd, temporary vector is used to make this easier.  A 
// challenge exercise (for another time) is to merge the elements in
// place, without requiring the 2nd vector.
//
void merge(ourvector<int>& V, int low, int mid, int high) {
  ourvector<int>  temp;  // holds merged results before copying back to V:

  int i = low;      // start of first portion of sorted values:
  int j = mid + 1;  // start of second portion of sorted values:

  //
  // loop through the sorted portions, pushing the smallest of the 
  // elements into temp:
  //
  while (i <= mid && j <= high) {
    if (V.at(i) <= V.at(j)) {
        temp.push_back(V.at(i));
        i++;
    }
    else {
        temp.push_back(V.at(j));
        ++j; // you'll want to delete these eventually
    }
  }//while

  //
  // when we get here, one or both of the portions is empty.  But
  // it's probably just one, so that means the other portion contains
  // data.  So if a portion still has data to merge, copy it over.
  //
  while (i <= mid) {
    temp.push_back(V.at(i));
    ++i;
  }

  while (j <= high) {
    temp.push_back(V.at(j));
    ++j;
  }

  // 
  // last step is to copy the values from the temporary vector back
  // into the original vector V:
  //
  for (int i = 0; i < temp.size(); ++i) {
    V[low] = temp[i];
    ++low;
  }

  // 
  // done!
  //
  return;
}
