// Lab 1 template code, CS 141
// Write and run the tests the individual problems one at a time.
//
#include <iostream>
#include <iomanip>   // for setw() and setfill()
using namespace std;

// -----------------------------------------------------------------------------------------------------
// Given input of a number, display a line of dashes of that length, separated by spaces.
// Running this problem for one possible input should look like:
//   Enter a number: 4
//   Result is:
//   ----
//
void problem1()
{
   int theNumber;
   cout << "Enter a number:";
   cin >> theNumber;
   cout << "Result is:";
   int i =1;
   while(i<=theNumber){
      cout<<"-";
      i++;
   }
   cout<<endl;
   
}//end problem1()


// -----------------------------------------------------------------------------------------------------
// Given input of a number, display that number of spaces followed by an asterisk. 
// Running this problem for one possible input should look like:
//    Enter a number: 3
//    Result is:   *
//
void problem2()
{
   int theNumber;
   cout << "Enter a number:";
   cin >> theNumber;
   cout << "Result is:";
   cout<<setw(theNumber+1)<<"*";
   cout<<endl;
   
}//end problem2()


// -----------------------------------------------------------------------------------------------------
// Given input of a number, display an ASCII character box of that size, filled with the '.' character.
// Running this problem for one possible input should look like:
//    Enter a number: 3
//    Result is: 
//     ------
//    |......|
//    |......|
//    |......|
//     ------
//
void problem3()
{
   int theNumber;
   cout << "Enter a number:";
   cin >> theNumber;
   cout << "Result is:";
   int i =1;
   cout<<"\n";
   cout<<' '<< setfill('-') <<setw((theNumber*2)+1);
   while(i<=theNumber){
      cout<<"\n" << '|'<<setfill('.')<<setw((theNumber*2)+1)<<'|';
      i++;
   }
   cout<<"\n"<<' '<<setfill('-') << setw((theNumber*2)+1)<<"\n";
   
   
}//end problem3()


int main() {
   // You should not change the code below this point.  
   // All your changes should be inside the individual functions shown above.
   int menuOption = 0;
   
   cout << "Enter which problem to run: ";
   cin >> menuOption; 
   switch( menuOption) {
      case 1: problem1(); break;
      case 2: problem2(); break;
      case 3: problem3(); break;
   }  

   cout << "Done." << endl;
   return 0;
}// end main()