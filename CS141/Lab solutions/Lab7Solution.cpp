#include <iostream>
using namespace std;

// Global constant
const int LineLength = 81;

/* Create the function declarations so the code works. 
// For each function you implement, uncomment the driver code within main 
// so you can test it.
// ...*/

int myStrlen(char userInput[]){
   int count=0;
   for (int i=0;userInput[i]!='\0';i++){
      count++;
   }
   return count;
}

void removeVowels(char newString[], char userInput[]){
   int j=0;
   for(int i=0; userInput[i]!='\0';i++){
      if(userInput[i] !='a' && userInput[i] !='e' && userInput[i] !='i'
         && userInput[i] !='o' && userInput[i] !='u'){
            newString[j] = userInput[i];    
            j++;
      }
      
   }
}

void duplicateString(char newString[], int countRepeat){
   int length = myStrlen(newString);
   int startHere = length;
   char copy[81];
   
   for(int j = 0 ; j < length; j++){
         copy[j] = newString[j];
   }
   
   int j=0;
   for (int i = 1 ; i < countRepeat ; i++){
      for(j = 0 ; j < length; j++){
         newString[startHere +j] = copy[j];
      }
      startHere=startHere+j;
   }
}

int main()
{
   char userInput[ LineLength];
   char newString[ LineLength];
   // Initialize newString to have all NULL characters
   for( int i=0; i<LineLength; i++) {
      newString[ i] = '\0';    // Set to the NULL character
   } 

   // Get user input
   cout << "Enter a word: ";
   cin >> userInput;

   // Display results from functions.
   // If userInput is "cat", then the line below would give a length of 3
   cout << "That word has length: " << myStrlen( userInput) << endl;

   // Remove vowels, putting resulting new string into array newString
   // For instance removing vowels from "cat" would put "ct" into newString.
    removeVowels( newString, userInput);
    cout << userInput << " without vowels is: " << newString << endl;

   // Duplicate the current contents of newString some number of times.
   // If 3 duplicates are chosen and newString is currently "ct", then 
   // newString would become "ctctct"
   int howManyTotal = 0;
   cout << "Enter how many duplicates to make: ";
   cin >> howManyTotal;
   duplicateString( newString, howManyTotal);
   cout << newString << endl;

   return 0;    // Keep C++ happy
} // end main()
