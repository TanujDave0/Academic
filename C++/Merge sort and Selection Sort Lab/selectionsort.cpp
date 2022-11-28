//
// Lab Week 4: writing selection sort and mergesort, and then 
// timing the efficiency of one versus the other.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <string>

#include "ourvector.h"

using namespace std;

int findIndexOfSmallestValue(ourvector<int>& V, int start);


//
// selectionSort
//
// Sorts the given vector of integers using selection sort,
// where you repeatedly select the smallest value to move to
// position i.
//
void selectionSort(ourvector<int>& V)
{
  //
  // for each location, find the smallest value to the right ("select")
  // and swap into this location.
  //
  for (int i = 0; i < V.size() - 1; ++i)
  {
    // looking to the right starting from position i, where is the
    // smallest value?
    int indexSmallest = findIndexOfSmallestValue(V, i);

    // swap into ith position:
    if (indexSmallest != i)
    {
      int temp = V[i];
      V[i] = V[indexSmallest];
      V[indexSmallest] = temp;
    }
  }
}


//
// testSort
//
// Fills vector with N elements, runs the sort algorithm, and outputs
// first 3 elements, last 3 elements, and whether correct.
//
void testSort(unsigned long long N)
{
  ourvector<int>    V;
  std::vector<int>  V2;

  cout << "Testing..." << endl;
  cout << "N=" << N << endl;

  //
  // Fill vectors with N random numbers:
  //
  std::random_device random_device;
  std::mt19937 random_engine(12345);
  std::uniform_int_distribution<int> distributionAgent(1, 1000000000);

  for (unsigned long long i = 0; i < N; ++i)
  {
    int ranInt = distributionAgent(random_engine);
    V.push_back(ranInt);
    V2.push_back(ranInt);
  }

  //
  // now sort both vectors, one using the built-in sort:
  //
  selectionSort(V);

  std::sort(V2.begin(), V2.end());

  //
  // output first and last elements:
  //
  cout << "Elements: ";

  for (int i = 0; i < 3; ++i)
    cout << V[i] << ", ";

  cout << "..., ";

  for (int i = V.size()-3; i < V.size()-1; ++i)
    cout << V[i] << ", ";

  cout << V[V.size() - 1] << endl;

  //
  // correct?
  //
  bool correct = true;
  for (size_t i = 0; i < V2.size(); ++i)
  {
    if (V[(int)i] != V2[i])
    {
      correct = false;
      break;
    }
  }

  if (correct)
    cout << "Sorting: correct" << endl;
  else
    cout << "Sorting: incorrect" << endl;
}


//
// timeSort
//
// Fills vector with N elements, runs the sort algorithm, and outputs
// the time.
//
void timeSort(unsigned long long N, bool showStats)
{
  ourvector<int> V;

  cout << "N=" << N << ": ";

  //
  // Fill vector with N random numbers:
  //
  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_int_distribution<int> distributionAgent(1, 1000000000);

  for (unsigned long long i = 0; i < N; ++i)
  {
    int ranInt = distributionAgent(random_engine);
    V.push_back(ranInt);
  }

  //
  // now time the sort:
  //
  auto start = chrono::high_resolution_clock::now();

  selectionSort(V);

  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  auto timeInMs = chrono::duration <double, milli>(diff).count();

  cout << "Time=" << std::round(timeInMs) << " ms" << endl;

  if (showStats)
  {
    cout << endl;
    V._stats();
  }
}



//
// sort.exe N T
//
// N = # of elements to sort initially
// R = # of runs to time; if R = 0 just test for correctness
//
int main(int argc, char* argv[])
{
  unsigned long long N;
  int                R;

  if (argc < 3)
  {
    cout << "Please enter N> ";
    cin >> N;

    cout << "Please enter # of runs (0 to test)> ";
    cin >> R;
  }
  else
  {
    N = std::stoi(argv[1]);
    R = std::stoi(argv[2]);
  }

  if (N < 6)
  {
    N = 6;  // 6 is the minimum we support:
  }

  if (R == 0)
  {
    testSort(N);
  }
  else
  {
    cout << "Timing..." << endl;

    for (int i = 0; i < R - 1; ++i)
    {
      timeSort(N, false /*no stats*/);
      N = N * 2;
    }

    // last one:
    timeSort(N, true /*show stats*/);
  }

  return 0;
}
