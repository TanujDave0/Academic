/*
This is midterm 1 version 8 for CS 141.

The function doIt() receives two strings and an integer (the integer is declared in main).
You have to write the function such that your code compares the two strings and see if one is the reverse of the other. 
If so, set the integer to 1, else set it to 3.

Running the program might look like the following:

Enter two words:  peek keep 
The integer now is:  1

Running the program again might look like the following:

Enter two words:  peek keen
The integer now is:  3

*/


// Midterm 1 in-lab
// Spring 2020
// CS 141, Reed & Deitz

#include <iostream>
using namespace std;

// You must supply the return type, and the types and number of parameters, and
// the code to make this program run correctly.

void doIt( string s1, string s2, int &flag)
{
   // Your code goes here
   // Check to see if the two strings have different length
   if(s1.length() != s2.length()){
      flag = 3;
      return;
   }
   
   // Store the length in a variable
   int len = s1.length();
   // Iterate string1 from the head and string2 from the tail, 
   // check to see if each pair of chars are different
   for(int i = 0; i < len; i++){
      if( s1[i] != s2[len-i-1]){
         flag = 3;
         return;
      }
   }
   
   // After we done checking, it is safe to say that string1 and string2 are reverse of each other.
   flag = 1;
   return;
} // end doIt()


//-----------------------------------------------------------

// *** Do not change any code below this line. ***
int main()
{
    // Declare the two strings and one integer
    string s1;
    string s2;
    int flag = 0;
    // Prompt for and get the user input
    cout << "Enter two word: ";
    cin >> s1 >> s2;
    doIt( s1, s2, flag);
    cout << "\nThe integer now is: " << flag << endl;
    return 0;   // Keep C++ happy
} // end main()




