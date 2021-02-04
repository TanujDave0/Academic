// Points:
// 1. Implement functions readInValues(...) and displayArray(...)
// 2. Implement function getBiggestElement(...)
// 3. Using the results of the previous functions, write function
//    findBiggest(...) which returns a pointer to the array containing
//    the biggest element.
//
#include <iostream>
using namespace std;

// Global constant for array size
const int ArraySize = 3;

//--------------------------------------------------------------------
// Prompt for and read in values into the array passed as a parameter.
void readInValues( int someNumbers[])
{
    for( int i=0; i < ArraySize; i++) {
        cin >> someNumbers[ i];
    }
}

//--------------------------------------------------------------------
// Display the values in the array passed as a parameter.
void displayArray( int *pTheArray)
{
  for( int i=0; i<ArraySize; i++) {
     cout << *pTheArray << " ";
     pTheArray++;
    }
    cout << endl;
}

//--------------------------------------------------------------------
// Find the biggest value in an array and return it
int getBiggestElement( int theArray[])
{
    int biggest = 0;
    for( int i=0; i<ArraySize; i++) {
        if( theArray[ i] > biggest) {
            biggest = theArray[ i];
        }
    }
    return biggest;
} // end getBiggestElement(...)

//--------------------------------------------------------------------
// Find which of two arrays has the biggest number in it, and return it.
int * findBiggest(
        int setOne[],
        int setTwo[])
{
    int biggestOfSetOne = getBiggestElement( setOne);
    int biggestOfSetTwo = getBiggestElement( setTwo);

    if( biggestOfSetOne >= biggestOfSetTwo) {
        return setOne;
    }
    else {
        return setTwo;
    }
} // end findBiggest(...)

//--------------------------------------------------------------------
int main( ) {
    int numbersSetOne[ ArraySize];
    int numbersSetTwo [ ArraySize];
    int *pBiggestNumberArray = NULL;
    // Stage 1 function calls
    cout << "Enter " << ArraySize << " numbers: ";
    readInValues( numbersSetOne);
    cout << endl<< "Enter " << ArraySize << " numbers: ";
    readInValues( numbersSetTwo);
    
    cout<< endl << "The array One is : ";
    displayArray(numbersSetOne);
    cout<< "The array Two is : "; 
    displayArray(numbersSetTwo);
    
    // stage 2 function calls (Comment for stage 3)
    int biggestInOne = getBiggestElement(numbersSetOne);
    int biggestInTwo = getBiggestElement(numbersSetTwo);
    cout<<endl << "The biggest element in array is: " << biggestInOne;
    cout<< endl <<"The biggest element in array is: " << biggestInTwo;
    
    //stage 3 function calls (comment for stage 1 and stage 2)
    pBiggestNumberArray = findBiggest( numbersSetOne, numbersSetTwo);
    cout << endl << "The array with the biggest numbers contains: ";

    displayArray( pBiggestNumberArray);
    return 0;
}



