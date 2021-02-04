// cipher.cpp
// CS 141 lab 5
/* Running the program looks like:
    Enter some lower-case text: hello
    Shifting  0 gives: hello
    Shifting  1 gives: ifmmp
    Shifting  2 gives: jgnnq
    Shifting  3 gives: khoor
    Shifting  4 gives: lipps
    Shifting  5 gives: mjqqt
    Shifting  6 gives: nkrru
    Shifting  7 gives: olssv
    Shifting  8 gives: pmttw
    Shifting  9 gives: qnuux
    Shifting 10 gives: rovvy
    Shifting 11 gives: spwwz
    Shifting 12 gives: tqxxa
    Shifting 13 gives: uryyb
    Shifting 14 gives: vszzc
    Shifting 15 gives: wtaad
    Shifting 16 gives: xubbe
    Shifting 17 gives: yvccf
    Shifting 18 gives: zwddg
    Shifting 19 gives: axeeh
    Shifting 20 gives: byffi
    Shifting 21 gives: czggj
    Shifting 22 gives: dahhk
    Shifting 23 gives: ebiil
    Shifting 24 gives: fcjjm
    Shifting 25 gives: gdkkn
 */// for CS 141 lab 5	

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

// Global constants
const int MaxWordSize = 81;     // 80 characters + 1 for NULL

//Uncomment for stage 3
//call this function from encrypt
void mystery(char shiftedText[]){
   char temp [80];
   int length =0;
   for(int i=0;shiftedText[i]!='\0';i++){
      length++;
   }
   
   for(int i=length;i>0;i--){
      temp[length-i] = shiftedText[i-1];
   }
   temp[length] = '\0';
   for(int i=0;shiftedText[i]!='\0';i++){
      shiftedText[i] = temp[i];
   }
}


//---------------------------------------------------
// Given an array of characters and a shift value, shift
// each character in the original text by some amount,
// storing the result into the shiftedText array.
// Wrap around at the end of the alphabet.
void shiftTheText(
        char startingText[ ],   // The starting text
        int shiftValue,         // The shift amount
        char shiftedText[])  {   // The resulting shifted text, wrapping around at 'z' back to 'a'

    for( int i = 0; startingText[ i] != '\0';  i++) {
        char c = startingText[ i];
        if( isalpha( c)) {
            // convert character into range 0..25
            c = c - 'a';
            // Add the shift value to it, wrapping around at end of alphabet
            c = (c + shiftValue) % 26;
            // Shift back up into alphabetic range
            c = c + 'a';
        }
     shiftedText[ i] = c;
    }
   // mystery(shiftedText);
} // end shiftTheText()




//---------------------------------------------------
int main()
{
    // Initialize the variables
    char startingText[ MaxWordSize];
    char shiftedText[ MaxWordSize];

    cout << "Enter some lower-case text: ";
    cin >> startingText;

    for( int shiftValue = 0; shiftValue < 26; shiftValue++) {
     // In the function call below you need to pass the starting text array, the shift value, and the shifted text array.
        shiftTheText( startingText, shiftValue, shiftedText);
        cout << "Shifting " << setw( 2) << shiftValue << " gives: " << shiftedText << endl;
    }
    return 0;   // Keep C++ happy
}// end main()