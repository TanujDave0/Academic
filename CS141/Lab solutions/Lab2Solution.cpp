// Lab 2 template code, CS 141
// Write and run the tests the individual problems one at a time.
//
#include <iostream>
#include <iomanip>   // for setw() and setfill()
using namespace std;

// -----------------------------------------------------------------------------------------------------
// Given input of a number, display a square of that length composed of *.
// Running this problem for one possible input should look like:
//   Enter an odd Integer for the Pattern Maker: 3
//   ***
//   ***
//   ***

void square()
{
   int theNumber;
   cout << "Enter an odd Integer for the Pattern Maker:";
   cin >> theNumber;
   //your code goes here...
   cout<<endl;
   for(int i=0;i<theNumber;i++){
      for(int j=0;j<theNumber;j++){
         cout<<"*";
      }
      cout<<endl;
   }
}//end problem1()


// -----------------------------------------------------------------------------------------------------
// Given input of a number, display a triangle (left aligned), the number is the length of it's base. 
// Running this problem for one possible input should look like:
//   Enter an odd Integer for the Pattern Maker: 3
//       *
//       ***

void triangle()
{
   int theNumber;
   cout << "Enter an odd Integer for the Pattern Maker:";
   cin >> theNumber;
   //your code goes here...
   cout<<endl;
   for(int i=1;i<=theNumber;i+=2){    //this loop takes care of the lines
      for(int j=1;j<=i;j++){         // this loop prints the stars
         cout<<"*";
      }
      
      cout<<endl;
   }
   
}//end problem2()


// -----------------------------------------------------------------------------------------------------
// Given input of a number (maximum length of the diamond),
//display a diamond composed of *.
// Running this problem for one possible input should look like:
//   Enter an odd Integer for the Pattern Maker: 3
//       *
//      ***
//     *****
//      ***
//       *
void diamond()
{
   int theNumber;
   cout << "Enter an odd Integer for the Pattern Maker:";
   cin >> theNumber;
   //your code goes here...
   cout<<endl;
   int spaces = theNumber/2;
   int stars = 1;
   for(int i = 1 ; i <= theNumber; i ++){     //this loop takes care of the line nuumbers
      if(i <= theNumber/2){                       //first half of the diamond
         for(int j = spaces ; j  > 0 ; j--){        //this loop takes care of the spaces
            cout<<" ";
         }

         for(int k = 1; k <= stars; k++){                    //This loop prints out the *
            cout<<"*";
         }
         spaces--;
         stars+=2;
      }
      else{         
        // space =1                                          //second half
         for(int j = 0 ; j  < spaces ; j++){        //this loop takes care of the spaces
            cout<<" ";
         }
         for(int k= 1; k <= stars; k++){                    //stars
               cout<<"*";
            }
         spaces++; 
         stars-=2;
      }
      cout<<endl;      
   }
   
}//end problem3()


int main() {
   // You should not change the code below this point.  
   // All your changes should be inside the individual functions shown above.
   int menuOption = 0;
   
   cout << "Welcome to Pattern maker." << "\n"
        << "Enter the Pattern number (1: Square, 2: Triangle, 3: Diamond): ";
   cin >> menuOption; 
   cout<<endl;
   switch( menuOption) {
      case 1: square(); break;
      case 2: triangle(); break;
      case 3: diamond(); break;
   }  

   cout << "Done." << endl;
   return 0;
}// end main()