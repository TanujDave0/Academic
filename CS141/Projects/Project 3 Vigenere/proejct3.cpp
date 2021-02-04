/* Prog3Vigenere.cpp
 *     Encode/Decode using Vigenere cipher.
 */
#include <iomanip>
#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>
using namespace std;

// Global constants

void getWord(char dictArray[], char wordToCompare[] ,int & checkIndex){
    int i;
    int j=0;
    for(i=checkIndex+1; dictArray[i]!=' '; ++i){
        wordToCompare[j]=dictArray[i];
        j++;
    }
    wordToCompare[j]='\0';
    checkIndex=i;
}

void checkDictionary(){
    char theWord[81];
    int checkIndex = 0;             // Row for the current word
    char userInput[81];
    int truthValue=0;
    int length=0;
    int number=1760535;
    char dictArray[number];

    // Open a file for reading
    ifstream inStream;             // declare an input stream
    inStream.open( "dictionary.txt");

    if( !inStream.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit( -1);
    }

    fgets(userInput, 81, stdin);

    while( inStream >> theWord ) {
        strcat(dictArray, theWord);
        strcat(dictArray, " ");
        length+=strlen(theWord)+1;
    }
    dictArray[length]='\0';

    while(checkIndex<strlen(dictArray)){
        char wordFound[81];
        getWord(dictArray, wordFound, checkIndex);
        if(strcmp(wordFound , userInput)==0){
            truthValue=1;
        }
        checkIndex++;
    }

    if(truthValue==1){
        for(int i=0; i<strlen(userInput); ++i){
            cout<<userInput[i];
        }
        cout<<" IS in the dictionary./n";
    }
    else if(truthValue!=1){
        for(int i=0; i<strlen(userInput); ++i){
            cout<<userInput[i];
        }
        cout<<" is NOT in the dictionary./n";
    }
    inStream.close(); // close the file
}

void vigEncrypt(char userInput[], char keyWord[]){
    char temp[81];
    int index=0;
    for(int i=0; i<strlen(keyWord); ++i){
        temp[i]=keyWord[i];
    }
    for(int i=0; userInput[i]!='\0'; ++i){
        keyWord[i]=temp[i%strlen(temp)];
    }
    for(int i=0; i<strlen(keyWord); ++i){
        cout<<keyWord[i];
    }
}

void removeNewLine(char theArray[]){
    for(int i=0; i<strlen(theArray); ++i){
        if(theArray[i]=='\n'){
            theArray[i]='\0';
        }
    }
}

//---------------------------------------------------------------------------
int main()
{
    // Declare variables
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
    char userInput[81];
    char keyWord[81];
    
    // Display menu and handle menu options
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
        cin >> menuOption;
        returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
                                      // This is necessary because otherwise a subsequent cin.getline() reads it as
                                      // an empty line of input.
    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            checkDictionary();
            break;
            
        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            fgets(userInput, 81, stdin);
            removeNewLine(userInput);
            for(int i=0; i<strlen(userInput); ++i){
                cout<<userInput[i];
            }
            cout << "Enter a keyword for Vigenere encryption: ";
            fgets(keyWord, 81, stdin);
            removeNewLine(keyWord);
            cout << "Keyword, plainText and ciphertext are:  \n";
            vigEncrypt(userInput, keyWord);
            break;
            
        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            
            cout << "Enter a Vigenere keyword to be tried: ";

            break;
            
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";

            break;
            
        case 5: // exit program
            cout << "Exiting program" << endl;
            exit( 0);
            break;
            
        default:
            // Sanity check
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
    }// end switch( menuOption)
    
    return 0;
}//end main()
