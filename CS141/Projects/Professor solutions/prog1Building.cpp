//  prog1Building.cpp
//
//  Created 1/1/2020 by Dale Reed for CS 141 program 1.
//  System: Xcode on iMac
//
/*  Running the program looks like:
        Choose from among the following options:
        1. Display original graphic
        2. Display building
        3. Exit the program
        Your choice -> 1

                ------------------------------------------
                   ______     _____
                  /          /     \      /   /    /    /
                 /          |            /   /    /    /
                |            ---        /    -----    /
                |               \      /        /    /
                 \_____   \_____/     /        /    /

                ------------------------------------------
        >>> Your original graphic will appear instead of the above <<<

    Running the program again looks like:
 
        Choose from among the following options:
        1. Display original graphic
        2. Display building
        3. Exit the program
        Your choice -> 2

        Number of building sections -> 3

             /\
             ||
             ||
             --
            |++|
            ====
            |\/|
            |/\|
            /--\
           |\::/|
           |:\/:|
           |:/\:|
           |/::\|
           /----\
          |\::::/|
          |:\::/:|
          |::\/::|
          |::/\::|
          |:/::\:|
          |/::::\|
          /------\
         ..........
        ++++++++++++
*/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw
using namespace std;  // so that we don't need to preface every cin and cout with std::

int main()
{
    int menuOption = 0;
    
    cout << "Choose from among the following options:  \n"
         << "1. Display original graphic  \n"
         << "2. Display building          \n"
         << "3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    cout << endl;   // Leave a blank line after getting the user input for the menu option.
    
    // See if exit was chosen
    if( menuOption == 3) {
        exit( 0);
    }
    
    else if( menuOption == 1) {
        // My own graphic
        cout << setw( 8) << " ";
        for( int i=0; i<42; i++) {
           cout << "-";
        }
        cout << endl;
        cout << setw( 8) << " " << "   ______     _____                       \n"
             << setw( 8) << " " << "  /          /     \\      /   /    /    /  \n"
             << setw( 8) << " " << " /          |            /   /    /    /   \n"
             << setw( 8) << " " << "|            ---        /    -----    /    \n"
             << setw( 8) << " " << "|               \\      /        /    /     \n"
             << setw( 8) << " " << " \\_____   \\_____/     /        /    /      \n"
             << endl;
        cout << setw( 8) << " ";
        for( int i=0; i<42; i++) {
            cout << "-";
        }
        cout << endl;
        cout << ">>> Your original graphic will appear instead of the above <<<" << endl;
    } //end if( menuOption == 1)  // menu option to display custom graphic

    else if( menuOption == 2) {
        // Prompt for and get the number of building sections.
        int numberOfSections = 0;
        cout << "Number of building sections -> ";
        cin >> numberOfSections;
        cout << endl;    // Leave a blank line after the user input
        
        // Display the top of the tower.
        int topSectionDisplayWidth = numberOfSections + 6;   // Blank space to the left, plus space for the tower
        cout << setw( topSectionDisplayWidth-1) << " /\\\n"
             << setw( topSectionDisplayWidth-1) << " ||\n"
             << setw( topSectionDisplayWidth-1) << " ||\n"
             << setw( topSectionDisplayWidth-1) << " --\n"
             << setw( topSectionDisplayWidth)   << "|++|\n"
             << setw( topSectionDisplayWidth)   << "====\n";
        
        int numberOfRows = 0;   // Declared outside the number of sections loop below, since it is also
                                // used to display the base of the whole tower.
        
        // Loop to display each building section.
        for( int currentSection = 1; currentSection <= numberOfSections; currentSection++) {
            
            // Display the rows for a single building section.
            int displayWidth = 1;               // Used to display a character in a variable width field, using setw()
            numberOfRows = currentSection * 2;  // Number of rows must always be an even number
            for( int row=0; row<numberOfRows; row++) {
            
                // Display left wall with appropriate leading space, so sections are all centered
                cout << setfill(' ') << setw( numberOfSections - currentSection + 3) << "|";
                
                // Set the left and right characters to be used in displaying this section of the X
                char leftCharacter = '\\';
                char rightCharacter = '/';
                // Reverse these if we are in the bottom half of the X
                if( row >= numberOfRows/2) {
                    leftCharacter = '/';
                    rightCharacter = '\\';
                }
                
                // Display the first part of the X.
                cout << setfill(':') << setw( displayWidth) << leftCharacter;
                // Display the second part of the X.
                cout << setfill(':') << setw( numberOfRows - (displayWidth * 2) + 1) << rightCharacter;
                // Display the right wall.
                cout << setfill(':') << setw( displayWidth) << "|" << endl;
                
                // Increment the displayWidth used for spacing of output characters.
                // E.g. as the value of row  is: 0 1 2 3 4 5
                // the value of displayWidth is: 1 2 3 3 2 1
                if( (row+1) < numberOfRows/2) {
                    displayWidth++;
                }
                if( (row+1) > numberOfRows/2) {
                    displayWidth--;
                }
            } //end for( int row...
            
            // Display the bottom separator row for the above section
            cout << setfill(' ') << setw(numberOfSections - currentSection + 3) << "/";
            for( int i=0; i<numberOfRows; i++) {
               cout << "-";
            }
            cout << "\\" << endl;
            
        } //end for( int currentSection = 1 ...
        
        // Display the base for the entire building.  The size of the base is relative to the total
        // number of lines in the section immediatly above it.
        cout << " ";   // Leave a single leading space
        for( int i=0; i<numberOfRows+4; i++) {
           cout << ".";
        }
        cout << endl;
        for( int i=0; i<numberOfRows+6; i++) {
           cout << "+";
        }
        cout << endl;
        
    } //end if( menuOption == 2) // menu option to display building
    
    cout << endl;
    return 0;
}// end main()
