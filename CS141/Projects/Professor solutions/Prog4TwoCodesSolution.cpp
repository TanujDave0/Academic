/* Prog4TwoCodes.cpp
        Look up a keyword in a document, displaying all paragraphs where it is found.
    This was inspired by the 2/12/2019 New York Times Article:
    "The Two Codes Your Kids Need to Know" describing how all students should know
    Computer Science and the Constitution:
         https://www.nytimes.com/2019/02/12/opinion/college-board-sat-ap.html
 
    Running this program looks like:
 
        Select from the following choices:
           W  Enter word or phrase to find, and display enclosing text
           X  Exit program
        Your choice: w perfect

        Enter word or phrase:
        Line 1:
        We the People of the United States, in Order to form a more perfect Union, establish Justice, insure domestic Tranquility, provide for the common defense, promote the general Welfare, and secure the Blessings of Liberty to ourselves and our Posterity, do ordain and establish this Constitution for the United States of America.

        Select from the following choices:
           W  Enter word or phrase to find, and display enclosing text
           P  Display previous text
           F  Display following text
           A  Display all occurrences of found word or phrase
           X  Exit program
        Your choice: p

        Line 0:
        PREAMBLE

        Select from the following choices:
           W  Enter word or phrase to find, and display enclosing text
           P  Display previous text
           F  Display following text
           A  Display all occurrences of found word or phrase
           X  Exit program
        Your choice: p

        There is no previous file contents.

        Select from the following choices:
           W  Enter word or phrase to find, and display enclosing text
           P  Display previous text
           F  Display following text
           A  Display all occurrences of found word or phrase
           X  Exit program
        Your choice: x

        Exiting program.
 */
#include <iostream>
#include <cctype>        // For the letter checking functions
#include <fstream>       // For file input
#include <vector>        // For vector storing text file contents
#include <string>        // C++ strings used to store a line of user input at a time
#include <cstring>       // For the C-string functions such as strstr
using namespace std;

// Global constants
const char InputFileName[] = "ConstitutionAndBillOfRights.txt";

//-----------------------------------------------------------------------
// Read and store lines from text file.  Do not store blank lines, which
// are lines of length 1 containing only a return character on them.
void readTextFile( vector<string> &textLines)
{
    ifstream inputFileStream;  // Declare the input file stream
    string inputLine;           // A single line of input from the text file
    
    // Open input file and verify
    inputFileStream.open( InputFileName);
    if( !inputFileStream.is_open() ) {
        cout << "Could not find input file " << InputFileName << ".  Exiting..." << endl;
        exit( -1);
    }
    
    // Continue reading input file lines and appending them to the strings
    // found so far until there are no more lines.
    while( getline( inputFileStream, inputLine)) {
        // Only store non-blank lines.  Blank lines have length 1 because they
        // have only a return character in them.
        if( inputLine.length() > 1) {
            textLines.push_back( inputLine);    // Append to existing lines
        }
    }
    
    // Close the file
    inputFileStream.close();
} // end readTextFile()


//-----------------------------------------------------------------------
// Convert a string to all lower case characters and return it.
string convertToLowerCase( string theString)
{
    for( int i=0; i<theString.length(); i++) {
        theString[ i] = tolower( theString[ i]);
    }
    
    return theString;
} // end convertToLowerCase(...)


//-----------------------------------------------------------------------
// Prompt for word to find and display the first occurrence of enclosing text.
void findWordAndDisplayText(
        int &indexOfLineContainingWord,      // Index of line where word is found
        vector<string> textLines,            // Vector of all lines from input file
        string &phraseToFind)                // The word to find
{
    // Set default value, to indicate word was not found
    indexOfLineContainingWord = -1;
    
    cout << "Enter word or phrase: ";
    getline( cin, phraseToFind);
    cout << endl;

    // Convert both word to find and string we're searching to lower case,
    //    to allow finding the word regardless of case matching or not.
    string lowerCaseTextLine;
    string lowerCaseWordToFind = convertToLowerCase( phraseToFind);
    
    // Step through all lines and look for the search word.
    for( int i = 0; i < textLines.size(); i++) {
        lowerCaseTextLine = convertToLowerCase( textLines[ i]);
        if( lowerCaseTextLine.find( lowerCaseWordToFind) != string::npos) {
            indexOfLineContainingWord = i;
            break;
        }
    }
    
    if( indexOfLineContainingWord != -1) {
        // Display the string containing the search word
        cout << "Line " << indexOfLineContainingWord << ": "
             << endl
             << textLines[ indexOfLineContainingWord] << endl;
    }
    else {
        cout << phraseToFind << " not found. " << endl;
    }
} // end findWordAndDisplayText(...)


//-----------------------------------------------------------------------
// Display the previous line, ensuring we don't try to go before the beginning
// of the document first line (line 0).
int displayPreviousText(
        int &indexOfLineContainingWord,      // Index of line where word is found
        vector<string> textLines)            // Vector of all lines from input file
{
    // Ensure we're not trying to go above the beginning of the document
    if( indexOfLineContainingWord <= 0) {
        cout << "There is no previous file contents. " << endl;
        return -1;    // Return value to indicate retrying move
    }
    // Find previous line that isn't blank, ensuring we stop at beginning.
    // Blank lines have length 1, with a single return character on them.
    do {
        indexOfLineContainingWord--;
    } while( indexOfLineContainingWord > 0 &&
             textLines[ indexOfLineContainingWord].length() <= 1
           );
    
    // Display the previously found line.
    cout << "Line " << indexOfLineContainingWord << ": "
         << endl
         << textLines[ indexOfLineContainingWord] << endl;
    
    return 1;    // Return value indicating previous line was found successfully.
} // end displayPreviousText(...)


//-----------------------------------------------------------------------
// Display the following line, ensuring we're not trying to go past the
//    end of the document.
int displayFollowingText(
        int &indexOfLineContainingWord,      // Index of line where word is found
        vector<string> textLines)            // Vector of all lines from input file
{
    // Ensure we're not trying to go past the end of the document
    if( indexOfLineContainingWord >= textLines.size()-1) {
        cout << "There is no following file contents. " << endl;
        return -1;    // Return value to indicate retrying move
    }
    // Find following line that isn't blank, ensuring we stop at end.
    // Blank lines have length 1, with a single return character on them.
    do {
        indexOfLineContainingWord++;
    } while( indexOfLineContainingWord < textLines.size()-1 &&
             textLines[ indexOfLineContainingWord].length() <= 1
           );
    
    // Display the line just found.
    cout << "Line " << indexOfLineContainingWord << ": "
         << endl
         << textLines[ indexOfLineContainingWord] << endl;
    
    return 1;    // Return value indicating following line was found successfully.
} // end displayFollowingText(...)


//-----------------------------------------------------------------------
// Display all occurrences of text with the previously found word.
void displayAllText(
        vector<string> textLines,    // Vector of all lines from input file
        string &phraseToFind)        // The word to find
{
    // Sanity check
    if( phraseToFind.length() == 0) {
        cout << "Word or phrase should have already been found. Exiting program.";
        exit( -1);
    }

    // Convert both word to find and string we're searching to lower case,
    //    to allow finding the word regardless of case matching or not.
    string lowerCaseTextLine;
    string lowerCaseWordToFind = convertToLowerCase( phraseToFind);
    
    // Step through all lines and look for the search word
    for( int i = 0; i < textLines.size(); i++) {
        string lowerCaseTextLine = convertToLowerCase( textLines[ i]);
        if( lowerCaseTextLine.find( lowerCaseWordToFind) != string::npos) {
            // Display the string containing the search word
            cout << "Line " << i << ": "
                 << endl
                 << textLines[ i] << endl
                 << endl;
        }
    }// end for( int i...
    
} // end displayAllText(...)


//-----------------------------------------------------------------------
int main()
{
    vector<string> textLines;    // Stores input file lines as a vector of strings
    
    // Read and store the lines of text from the input file
    readTextFile( textLines);
    
    // Display menu options
    char menuOption;
    char returnCharacter = ' ';
    int indexOfLineContainingWord = -1;
    string phraseToFind = "";
    
    // Infinite loop
    while( true) {
        cout << endl
             << "Select from the following choices: \n"
             << "   W  Enter word or phrase to find, and display enclosing text \n";
        // Only display the following menu choices if a word has already been found
        if( phraseToFind.length() != 0) {
            cout << "   P  Display previous text \n"
                 << "   F  Display following text \n"
                 << "   A  Display all occurrences of found word or phrase \n";
        }
        cout << "   X  Exit program \n"
             << "Your choice: ";
        cin >> menuOption;
        cout << endl;
        menuOption = toupper( menuOption);
        returnCharacter = getchar();
        // Strip off return character from input buffer so it is not later mistaken as
        // the input for the word or phrase for which we are searching.
        
        // Error checking
        if( phraseToFind.length() == 0 &&
            (menuOption == 'P' || menuOption == 'F' || menuOption == 'A')
          ) {
            // Word has not already been found, so display error and retry
            cout << "First you must find a word or phrase.  Please retry." << endl;
            continue;
        }
        
        switch( menuOption) {
            case 'W': // Enter Word to find and display enclosing text.
                    findWordAndDisplayText( indexOfLineContainingWord, textLines, phraseToFind);
                    break;
                
            case 'P': // Display Previous text
                    if( displayPreviousText( indexOfLineContainingWord, textLines) == -1) {
                        continue;    // Already at top of file, w/no previous line
                    }
                    break;
                
            case 'F': // Display Following text
                    if( displayFollowingText( indexOfLineContainingWord, textLines) == -1) {
                        continue;    // Already at end of file, w/no next line
                    }
                    break;
                
            case 'A': // Display All text containing found word;
                    displayAllText( textLines, phraseToFind);
                    break;
                
            case 'X': // Exit the program
                    cout << "Exiting program." << endl;
                    break;
                
            default: cout << "Invalid menu option.  Please retry." << endl;
                    break;
        } // end switch
        
        // Exit the enclosing loop if menuChoice was 'X'
        if( menuOption == 'X') {
            break;
        }
        
    } // end while( true)
    
    return 0;
} // end main()
