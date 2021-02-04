#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;


//------------------------- Sample -----------------------------
// Iteratively (non-recursively) display numbers up to some limit
void sampleIterative( int counter, int limit)
{
    // Display numbers up to the limit
    while( counter < limit) {
        cout << counter << " ";
        counter++;
    }
    cout << endl;   // display a new line
}//end sampleIterative()


// Same thing, now using recursion
void sampleRecursive( int counter, int limit)
{
    // Check for the base condition
    if( counter == limit) {       // this tells the recursive function when to stop
        cout << endl;
    }
    else {
        cout << counter << " ";
        // make the recursive call
        sampleRecursive( ++counter, limit);         // function calls itself
    }
}//end sampleRecursive()


//------------------------- Problem 1 --------------------------
// Display odd numbers less than some limit
void problemOneOddNumbersIterative( int counter, int limit)
{
    // Display numbers up to the limit
    while( counter < limit) {
        if( counter % 2 == 1) {
            cout << counter << " ";
        }
        counter++;
    }
    cout << endl;   // display a new line
}//end problemOneOddNumbersIterative()


// Same thing, now done recursively.   >>> YOU SUPPLY CODE IN THIS FUNCTION <<<
void problemOneOddNumbersRecursive( int counter, int limit)
{
    //*** WRITE YOUR CODE HERE for problem 1 ...
      if( counter == limit) {
        cout << endl;
    }
    else {
      if(counter %2 == 1){
        cout << counter << " ";
      }
        // make the recursive call
        problemOneOddNumbersRecursive( ++counter, limit);
    }
    
    
}//end problemOneOddNumbersRecursive()


//------------------------- Problem 2 --------------------------
// Count the number of upper-case letters in an array
int problemTwoCountUpperIterative( int index, char arrayOfLetters[])
{
    int counter = 0;
    while( index < strlen( arrayOfLetters)) {
        char currentChar = arrayOfLetters[ index];   // first character
        // If the current character is upper case, increment counter
        if( isupper( currentChar)) {
            counter++;
        }
        // advance pointer to next character
        index++;
    }
    return counter;
}//end problemTwoCountUpperIterative()


// Same thing, now done recursively.
int problemTwoCountUpperRecursive( int index, char arrayOfLetters[])
{
    //*** WRITE YOUR CODE HERE for problem 2 ...
      if(index >= strlen(arrayOfLetters)){
        return 0;
      }
    else{
      char currentChar = arrayOfLetters[ index];   // first character
        // If the current character is upper case, increment counter
      if( isupper( currentChar)) {
        return 1 + problemTwoCountUpperRecursive(++index,arrayOfLetters);
      }
      else{
        return problemTwoCountUpperRecursive(++index,arrayOfLetters);
      }
    }
    //return 0;  // you may need to change this line
}//end problemTwoCountUpperRecursive()



//----------------------------------------------------------
//YOU SHOULD NOT EDIT CODE IN THE MAIN() FUNCTION
//----------------------------------------------------------
int main()
{
    cout<<"\nEnter a choice:";
    cout<<"\n 0. Problem 0: Display counts";
    cout<<"\n 1. Problem 1: Odd Numbers";
    cout<<"\n 2. Problem 2: Count Upper Case";
    cout<<"\n 3. Exit\n";
    int choice;
    cin>> choice;
    switch(choice){
      case 0:
        {
          //------------------------------------------------------
          // Problem 0:  This one is an already completed example.
          // Count to some limit using a while loop.
          // Then the recursive version does the same thing.
          // For the other functions below you will be given the iterative (non-recursive)
          // version, and will have to create the recursive version.
          int counter = 0;
          int limit;
          cout << "Sample Problem \n";
          cout << "Enter the limit: ";
          cin >> limit;
          sampleIterative( counter, limit);    // Iterative (non-recursive) version
          sampleRecursive( counter, limit);    // Recursive version
          break;
        }
      case 1: 
        {
          //------------------------------------------------------
          // Problem 1: Display the odd numbers less than some limit
          int counter = 0;
          int limit;
          cout << "Problem 1 \n";
          cout << "Enter the limit: ";
          cin >> limit;
          problemOneOddNumbersIterative( counter, limit);
          problemOneOddNumbersRecursive( counter, limit);  // <-- you supply the code for this one
          cout << "\n\n";
           break;
      }
      case 2:
        {
          //------------------------------------------------------
          // Problem 2: Given a C string, count how many characters are upper-case
          char arrayOfLetters[ 81];
          cout << "Problem 2 \n";
          cout << "Enter a line of input with mixed-case letters: ";
          int counter = 0;
          // First get rid of carriage-return lingering on input buffer from previous question
          char c;
          cin.get( c);
          // Now read in user input
          cin.getline( arrayOfLetters, 81);    // read in an entire line
          cout << "Number of upper-case done Iteratively is: "
                  << problemTwoCountUpperIterative( 0, arrayOfLetters) << endl;
          cout << "Number of upper-case done Recursively is: "
                << problemTwoCountUpperRecursive( counter, arrayOfLetters)  // <-- you supply the code for this one
                << endl;
          cout << endl;
          break;
        }
      
      case 3:
        {
          cout<<"Exiting with code 0";
        }
    }
 
}//end main()
