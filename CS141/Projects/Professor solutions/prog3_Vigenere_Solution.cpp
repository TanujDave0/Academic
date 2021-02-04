/* Prog3Vigenere.cpp
 *     Encode/Decode using Vigenere cipher.
 *
 * Author: Dale Reed
 * CS 141, Spring 2020
 * Program 3: Vigenere
 *
 
 Running the program looks like:
 
         21735 words of size >= 3 were read in from dictionary.

        Choose from the following options:
            1. Lookup dictionary word
            2. Encode some text
            3. Decode some text
            4. Auto-decode the ciphertext given with the assignment
            5. Exit program
        Your choice: 1
        Enter a word to be looked up in dictionary: cat
        cat IS in the dictionary.

 Running the program again looks like:
 
        21735 words of size >= 3 were read in from dictionary.

        Choose from the following options:
            1. Lookup dictionary word
            2. Encode some text
            3. Decode some text
            4. Auto-decode the ciphertext given with the assignment
            5. Exit program
        Your choice: 2
        Enter the text to be encoded: Hard Work
        Enter a keyword for Vigenere encryption: hidden
        Keyword, plainText and ciphertext are:
        hiddenhid
        hard work
        oiug jvzn

 Running the program again looks like:
 
        21735 words of size >= 3 were read in from dictionary.

        Choose from the following options:
            1. Lookup dictionary word
            2. Encode some text
            3. Decode some text
            4. Auto-decode the ciphertext given with the assignment
            5. Exit program
        Your choice: 3
        Enter the cipherText to be decoded: oiug jvzn
        Enter a Vigenere keyword to be tried: hidden
        2 words found using keyword: hidden giving:
           hard work
 
 Running the program again looks like:
 
        21735 words of size >= 3 were read in from dictionary.

        Choose from the following options:
            1. Lookup dictionary word
            2. Encode some text
            3. Decode some text
            4. Auto-decode the ciphertext given with the assignment
            5. Exit program
        Your choice: 4
        Enter the cipherText to be decoded: nol ycwh io ffpllhg uenmvi ihv qmdprlieg: zcfnd lfkt pqwayhz ib ofl.db/dgiaoy13
        1 words found using keyword: ﻿the giving:
           xyr rygr ph ppvsedq algifs par askinvskn: jmluw vpqa laggfav sh hbv.ji/zqsgvr13
        2 words found using keyword: hung giving:
           guy rijb ob ylcfent nkagoo cab kfjcleora: mwytq elxn vdqteut oo hly.wh/xzonir13
        5 words found using keyword: paralysed giving:
           you need to further decode the following: hycyd lumb mbwjywb ey ool.fj/arijon13
 
 Running the program again looks like:
 
        21735 words of size >= 3 were read in from dictionary.

        Choose from the following options:
            1. Lookup dictionary word
            2. Encode some text
            3. Decode some text
            4. Auto-decode the ciphertext given with the assignment
            5. Exit program
        Your choice: 4
        Enter the cipherText to be decoded: hycyd lumb mbwjywb ey ool.fj/arijon13
        1 words found using keyword: such giving:
           pearl jnuh fjchreh xg mht.dc/gpbrul13
        2 words found using keyword: skulking giving:
           point your browser to bit.ly/secret13
 
    bit.ly/secret13 goes to a google form, which allows the students to register their name and netid and
    upload their program, for 5 points of extra credit if they are among the first 20 to get there.
 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cstring>    // For strlen()
#include <cctype>     // Allows using the tolower() function
using namespace std;

// Global constants
const char DictionaryFileName[] = "dictionary.txt";    // In Code::blocks this is in /Users/reed
const char KeywordsFileName[] = "TheSecretAgentByJosephConrad.txt";
const int MaxNumberOfWords = 21735;    // Number of dictionary words
const int MaxNumberOfKeyWords = 93297; // Number of key words in input file
const int MinWordSize = 3;             // Minimum dictionary word size to be stored
const int MaxWordLength = 17;          // Max word size + 1 for null
const int LineSize = 81;               // Max size of an input line


//---------------------------------------------------------------------------
// Fold all characters in string to lower case
void toLowerCase( char theWord[])
{
    for( int i=0; i<strlen( theWord); i++) {
        theWord[ i] = tolower( theWord[ i]);
    }
}//end toLowerCase


//---------------------------------------------------------------------------
// This is our own version of fgets, which stores the newline character and
// then NULL terminates the string.  Our version here overwrites the
// ending newline character with NULL, and also converts to lower case.
void getInputLineInLowerCase( char charArray[])
{
    fgets( charArray, LineSize, stdin);
    charArray[ strlen( charArray) - 1] = '\0';
    toLowerCase( charArray);      // Fold into lower case
} // end getInputLineInLowerCase()


//---------------------------------------------------------------------------
// Read in dictionary words from file
void readInDictionary(
      char dictionary[ MaxNumberOfWords][ MaxWordLength],     // dictionary words
      int &numberOfWords)                                     // number of words stored
{
    // Now read in the words from the file
    ifstream inStream;                 // Declare an input stream
    numberOfWords = 0;                 // Row for the current word
    inStream.open( DictionaryFileName);
    if( !inStream.is_open()) {
        cout << "Could not find " << DictionaryFileName << ".  Exiting..." << endl;
        exit( -1);
    }
    
    // Keep repeating while input from the file yields a word
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    while( inStream >> theWord) {
        if( strlen( theWord) >= MinWordSize) {
            toLowerCase( theWord);  // convert to lower case
            strcpy( dictionary[ numberOfWords], theWord);
            // increment number of words
            numberOfWords++;
        }
    }//end while( inStream...
    
    cout << numberOfWords << " words of size >= " << MinWordSize << " were read in from dictionary. \n" << endl;
    
    // close the file
    inStream.close();
}//end readInDictionary()


//---------------------------------------------------------------------------
// Lookup word in dictionary using binary search.  Returns true if word is
// found, false otherwise.
bool wordIsInDictionary(
        char theWord[],                                      // word to look up
        char dictionary[MaxNumberOfWords][MaxWordLength],    // dictionary words
        int numberOfWords)                                   // number of words in dictionary
{
    int low, mid, high;     // array indices for binary search
    int searchResult;       // Stores 0 if search succeeded
    
    // Binary search for word
    low = 0;
    high = numberOfWords - 1;
    while( low <= high)  {
        mid = (low + high) / 2;
        // Compare theWord to currtent dictionary word, returning a negative if
        // theWord preceeds the dictionary word, returning 0 if they
        // are equal, and returning a positive number if theWord is
        // after the current dictionary word.
        searchResult = strcmp( theWord, dictionary[ mid]);
        if ( searchResult == 0)  {
            return true;         // found the word
        }
        else if (searchResult < 0)  {
            high = mid - 1; // theWord should be located prior to mid location
        }
        else  {
            low = mid + 1; // theWord should be located after mid location
        }
    }//end while( low...
    
    return false;       // Did not find the theWord
}//end wordIsInDictionary()


//---------------------------------------------------------------------------
// See how many words in a string are found in the dictionary.
// Note that we cannot use strtok to break up the string into individual words, because at the time of calling
// this function we are still in the middle of a strtok call that parses the input string of decoding keywords.
// Nesting strtok like this doesn't work, so we write our own instead.
int countDictionaryWordsInCipherText(
        char transposedCipherText[],                         // string of words to be looked up
        char dictionary[MaxNumberOfWords][MaxWordLength],    // dictionary words
        int numberOfWords,                                   // number of words in dictionary
        char wordsInDictionary[ LineSize * 100])             // The actual words found
{
    int numberOfWordsFound = 0;
    
    char *pCurrent = transposedCipherText;  // pointer to beginning of string
    char *pSpace = transposedCipherText;    // will point to spaces when found, to separate strings
    char tempWord[ LineSize];               // for copying individual words
    
    // Pull out a single word at a time and see if it is in the dictionary, updating counter if it is.
    // The extra parenthesis in the expression below makes a compiler warning go away.
    while( (pSpace = strchr( pCurrent, ' ')) ) {
        // A space character was found, so a word was found. Copy into temporary space and look it up in the dictionary.
        strncpy( tempWord, pCurrent, pSpace-pCurrent);
        tempWord[ pSpace-pCurrent] = '\0';   // Null terminate, since strncpy doesn't do this
        if( wordIsInDictionary( tempWord, dictionary, numberOfWords)) {
            numberOfWordsFound++;
            // Concatentate the actual word found in the dictionary to the list of all words found
            strcat( wordsInDictionary, " ");
            strcat( wordsInDictionary, tempWord);
        }
        pCurrent = pSpace + 1;   // Advance the pointer past the space to the beginning of next word
    }
    
    // Special case to handle the last word, which is followed by a NULL, not a space as the previous words were
    if( wordIsInDictionary( pCurrent, dictionary, numberOfWords)) {
        numberOfWordsFound++;
        // Concatentate the actual word found in the dictionary to the list of all words found
        strcat( wordsInDictionary, " ");
        strcat( wordsInDictionary, pCurrent);
    }
    
    return numberOfWordsFound;
}//end countDictionaryWordsInCipherText()


//---------------------------------------------------------------------------
/* Apply the vigenere encoding, which uses the following table as explained
   below:
            A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 
         A  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
         B  B C D E F G H I J K L M N O P Q R S T U V W X Y Z A
         C  C D E F G H I J K L M N O P Q R S T U V W X Y Z A B
         D  D E F G H I J K L M N O P Q R S T U V W X Y Z A B C
         E  E F G H I J K L M N O P Q R S T U V W X Y Z A B C D
         F  F G H I J K L M N O P Q R S T U V W X Y Z A B C D E
         G  G H I J K L M N O P Q R S T U V W X Y Z A B C D E F
         H  H I J K L M N O P Q R S T U V W X Y Z A B C D E F G
         I  I J K L M N O P Q R S T U V W X Y Z A B C D E F G H
         J  J K L M N O P Q R S T U V W X Y Z A B C D E F G H I
         K  K L M N O P Q R S T U V W X Y Z A B C D E F G H I J
         L  L M N O P Q R S T U V W X Y Z A B C D E F G H I J K
         M  M N O P Q R S T U V W X Y Z A B C D E F G H I J K L
         N  N O P Q R S T U V W X Y Z A B C D E F G H I J K L M
         O  O P Q R S T U V W X Y Z A B C D E F G H I J K L M N
         P  P Q R S T U V W X Y Z A B C D E F G H I J K L M N O
         Q  Q R S T U V W X Y Z A B C D E F G H I J K L M N O P
         R  R S T U V W X Y Z A B C D E F G H I J K L M N O P Q
         S  S T U V W X Y Z A B C D E F G H I J K L M N O P Q R
         T  T U V W X Y Z A B C D E F G H I J K L M N O P Q R S
         U  U V W X Y Z A B C D E F G H I J K L M N O P Q R S T
         V  V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
         W  W X Y Z A B C D E F G H I J K L M N O P Q R S T U V
         X  X Y Z A B C D E F G H I J K L M N O P Q R S T U V W
         Y  Y Z A B C D E F G H I J K L M N O P Q R S T U V W X
         Z  Z A B C D E F G H I J K L M N O P Q R S T U V W X Y
 
     Example of encoding using the keyword: HIDDEN
     Take the plaintext message and write the keyword over it, repeating it as many times as you need it
     until each plaintext message has a letter over it. This would give you:
          HIDDENHID  <-repeated keyword
          HARD WORK  <-original plaintext message
     Now use the vertical pairs of letters to encode the plaintext message, which is the text: HARD WORK.
     The first (left-most) vertical pair of letters are 'H' on the top row and 'H' on the bottom row. Use the
     top 'H' as the row in the Vigenere table, and the bottom 'H' as the column, giving you the letter 'O'.
     The next vertical pair of letters are 'I' on the top and 'A' on the bottom. Use 'I' as the row, and 'A'
     as the column, giving you the letter 'I'. Next comes 'D' and 'R', which gives the letter 'U'.
     Resolving these pairs in turn gives:
      row:  HIDDENHID  <-repeated keyword
      col:  HARD WORK  <-original plaintext message
      new:  OIUG JVZN  <-ciphertext (the encoded message)
 */
void vigenereEncode(
        char plainText[],   // The original plain text
        char keyword[],     // Keyword used in Vigenere encoding
        char cipherText[])  // The new Vigenere encoded text
{
    int row, col;
    int keywordLength = (int)strlen( keyword);
    
    // Step through each character in the plaintext, applying Vigenere to it
    for( int i=0; i<strlen( plainText); i++) {
        // Apply Vigenere transposition only to alphabetic characters. Extract the character in question.
        char c = plainText[ i];
        if( isalpha( c)) {
            // Sanity check ensuring letters are only lower case
            if( ! islower(c)) {
                cout << "Character " << c << " should be lower case, but is not. Exiting program." << endl;
                exit( -1);
            };
            
            // Use a formula to find the keyword character.  For instance, if the keyword were CAT:
            //         value of i-->  012345678...
            // keyword character -->  CATCATCAT...
            row = keyword[ i % keywordLength] - 'a';
            col = plainText[ i] - 'a';
            
            // Shift into range 0..26
            c = c - 'a';
            // Add the row for the number of row shifts, then add col to indicate where in that row the character is.
            // Wrap around the end of the alphabet by using %
            c = (row + col) % 26;
            
            // Shift back into alphabetic range and store
            cipherText[ i] = c + 'a';
        }//end if( isalpha..
        else {
            // plainText character is not alphabetic, so just copy it over to the cipherText
            cipherText[ i] = plainText[ i];
        }
        
        // Null-terminate the cipherText, now that we've copied over all the encrypted characters
        cipherText[ strlen( plainText)] = '\0';
        
    }//end for( int i...
}//end vigenereEncode()


//---------------------------------------------------------------------------
/* Apply Vigenere decoding using the given keyword.
    To decipher a message take the top letter (from the keyword row, e.g. 'D' in the third column below)
    and find the row corresponding to that letter.  Follow across that row until you find the corresponding
    ciphertext character (e.g. 'U' in the third column below). At that spot in the table then go straight
    up to find the letter that is the label at the top of that column. That character (e.g. 'R' in this case)
    is the original plaintext character.
 
    row:  HIDDENHID  <-repeated keyword
    col:  ???? ????  <-original plaintext message
    new:  OIUG JVZN  <-ciphertext (the encoded message)
 */
void vigenereDecode(
        char cipherText[],      // CipherText to be decoded
        char plainText[],       // Decoded plainText
        char keyword[],         // Keyword for decoding
        char dictionary[MaxNumberOfWords][MaxWordLength],    // dictionary words
        int numberOfWords)      // Number of words in dictionary
{
    int row, col;
    int keywordLength = (int) strlen( keyword);   // Cast to (int) to avoid compiler warning of loss of precision
    
    // Step through each character in the ciphertext, applying Vigenere to it
    for( int i = 0; i < strlen( cipherText); i++) {
        // Only apply Vigenere transposition for alphabetic characters, leaving others unchanged
        // Extract the character in question.
        char c = cipherText[ i];
        if( isalpha( c)) {
            // Sanity check ensuring letters are only lower case
            if( ! islower(c)) {
                cout << "Character " << c << " should be lower case, but is not. Exiting program." << endl;
                exit( -1);
            };
            
            // Use a formula to find the keyword character.  For instance, if the keyword were CAT:
            //         value of i-->  012345678...
            // keyword character -->  CATCATCAT...
            row = keyword[ i % keywordLength] - 'a';
            col = cipherText[ i] - 'a';
            
            // shift into range 0..26
            c = c - 'a';
            // Subtract the row for the number of row shifts. Because of the alphabetic wrap-around,
            // subtracting 1 is the same as adding (26-1) % 26
            c = (c + (26 - row)) % 26;
            
            // shift back into alphabetic range and store
            plainText[ i] = c + 'a';
        }//end if( isalpha..
        else {
            // Is not an alphabetic character, so just copy it over into the plainText array
            plainText[ i] = cipherText[ i];
        }
        
    }//end for( int i...
}//end vigenereDecode()


//---------------------------------------------------------------------------
// Decode a cipherText string using a single keyword and store how many of
// the decoded words are found in the dictionary.  Update the bestNumberWordsFound
// if this is a new best case.  Display results found.
void decodeAndDisplayResult(
        char cipherText[],            // CipherText to be decoded
        char keyword[],               // Keyword to use in Vigenere decoding
        char dictionary[MaxNumberOfWords][MaxWordLength],    // dictionary words
        int numberOfWords,            // Number of words in dictionary
        int &bestNumberWordsFound,    // Best number of dictionary words found
        char bestKeyword[ LineSize])  // Best Vigenere keyword
{
    int wordsFound = 0;
    // Declare space to store the transposed text
    char plainText[ LineSize];
    // Initialize the space to NULLS
    for( int i=0; i<LineSize; i++) {
       plainText[ i] = '\0';
    }
    // Store the actual words found in the dictionary, to use in debugging
    char wordsInDictionary[ LineSize * 100];
    for( int i=0; i<LineSize * 100; i++) {
       wordsInDictionary[ i] = '\0';
    }
    
    // Decode using Vigenere with the keyword.
    vigenereDecode( cipherText, plainText, keyword, dictionary, numberOfWords);
    
    // Count how many dictionary words are found in the decoded text
    wordsFound = countDictionaryWordsInCipherText( plainText, dictionary, numberOfWords, wordsInDictionary);

    // Store potential new best result
    if( wordsFound > bestNumberWordsFound) {
        bestNumberWordsFound = wordsFound;    // Store the new best number of words found
        strcpy( bestKeyword, keyword);        // Store the new best keyword
    
        // Display new best case found
        cout << wordsFound << " words found using keyword: " << keyword
             << " giving:\n   " << plainText
             //<< ", with words found being: " << wordsInDictionary     // Used for debugging, to show actual words found
             << endl;
    }
    
}//end decodeAndDisplayResult()


//---------------------------------------------------------------------------
// Decode using keywords from file for menu option #3.
void decodeUsingKeywordsFromFile(
     char cipherText[],                                   // CipherText to be decoded
     char dictionary[MaxNumberOfWords][MaxWordLength],    // Dictionary words
     int numberOfWords,                                   // Number of words in dictionary
     int &bestNumberWordsFound,    // Best number of dictionary words found
     char bestKeyword[ LineSize])  // Best Vigenere keyword
{
    // Make a copy of the cipherText so each new keyword starts again with the original
    char keyWord[ 81];    // declare input space to be clearly larger than largest word
    
    // Read in the words from the keywords file
    ifstream inStream;                 // Declare an input stream
    inStream.open( KeywordsFileName);
    if( !inStream.is_open()) {
        cout << "Could not find " << KeywordsFileName << ".  Exiting..." << endl;
        exit( -1);
    }
    
    // Keep repeating while input from the keywords file yields a word
    while( inStream >> keyWord) {
        toLowerCase( keyWord);  // convert to lower case
        
        // Decode the cipherText with this particular code word
        decodeAndDisplayResult( cipherText, keyWord, dictionary, numberOfWords, bestNumberWordsFound, bestKeyword);
        
    }//end while( inStream...
    
}//end decodeUsingKeywordsFromFile()


//---------------------------------------------------------------------------
int main()
{
    // Declare variables
    char dictionary[ MaxNumberOfWords][ MaxWordLength];                 // Dictionary words
    int numberOfWords;                // How many words of desired length get read into dictionary
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
    char plainText[ LineSize];        // User input for text to be encoded
    char vigenereKeyword[ LineSize];  // Vigenere keyword used for encoding
    char cipherText[ LineSize];       // PlainText that has now been encoded
    char keyword[ LineSize];          // A single possible Vigenere keyword
    int bestNumberWordsFound = 0;     // Best number of dictionary words found
    char bestKeyword[ LineSize];      // Best Vigenere keyword
    
    // Read in dictionary
    readInDictionary( dictionary, numberOfWords);
    
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
            char aWord[ LineSize];
            cin >> aWord;
            if( wordIsInDictionary( aWord, dictionary, numberOfWords)) {
                cout << aWord << " IS in the dictionary." << endl;
            }
            else {
                cout << aWord << " is NOT in the dictionary." << endl;
            }
            break;
            
        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            getInputLineInLowerCase( plainText);
            
            cout << "Enter a keyword for Vigenere encryption: ";
            getInputLineInLowerCase( vigenereKeyword);
            
            cout << "Keyword, plainText and ciphertext are:  \n";
            // Display the Vigenere keyword repeated as many times as is necessary to match the length of the plainText
            for( int i=0; i<strlen(plainText); i++) {
                cout << vigenereKeyword[ i % strlen(vigenereKeyword)];
            }
            cout << endl;
            
            // Display the plainText immediately below the Vigenere keyword that has been repeated to match the length
            cout << plainText << endl;
            
            // Do the Vigenere encoding using the Vigenere keyword, and then display the new cipherText
            vigenereEncode( plainText, vigenereKeyword, cipherText);
            cout << cipherText << endl;
            break;
            
        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            getInputLineInLowerCase( cipherText);
            
            cout << "Enter a Vigenere keyword to be tried: ";
            getInputLineInLowerCase( keyword);

            decodeAndDisplayResult( cipherText, keyword, dictionary, numberOfWords, bestNumberWordsFound, bestKeyword);
            break;
            
        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            getInputLineInLowerCase( cipherText);
            decodeUsingKeywordsFromFile( cipherText, dictionary, numberOfWords, bestNumberWordsFound, bestKeyword);
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

