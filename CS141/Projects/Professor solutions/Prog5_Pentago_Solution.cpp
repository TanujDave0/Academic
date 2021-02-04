// Prog5Pentago.cpp
//     Play the two-player game of Pentago, trying to get 5 pieces in a row.
//
// Author: Dale Reed
// Program: #5, Pentago using classes
// TA: Karla Templar, Tues 10
//
// Test input:
//    To enter the input all at one time, for the run below use:
//       c31r  A5 3R  G05h  c05h  c25h  c21h  c2 1r  b 6 4 l  c53l  d6 3r  c41r  e14l  c6 2r  f2 3l
//
//    To have both win at same time, resulting in a tie, use:
//       b23r a53l b13l b63l b33l d63l e24l e12r e31r f23l
//
 /* Running the program looks like what is shown below.
        Welcome to Pentago, where you try to get 5 of your pieces in a line.
        At any point enter 'x' to exit or 'i' for instructions.

            1   2   3   4   5   6
          1-----------------------2
        A | .   .   . | .   .   . | A
          |           |           |
        B | .   .   . | .   .   . | B
          |           |           |
        C | .   .   . | .   .   . | C
          |-----------+-----------|
        D | .   .   . | .   .   . | D
          |           |           |
        E | .   .   . | .   .   . | E
          |           |           |
        F | .   .   . | .   .   . | F
          3-----------------------4
            1   2   3   4   5   6
        1. Enter row, column, quadrant, direction for X: a11r

            1   2   3   4   5   6
          1-----------------------2
        A | .   .   X | .   .   . | A
          |           |           |
        B | .   .   . | .   .   . | B
          |           |           |
        C | .   .   . | .   .   . | C
          |-----------+-----------|
        D | .   .   . | .   .   . | D
          |           |           |
        E | .   .   . | .   .   . | E
          |           |           |
        F | .   .   . | .   .   . | F
          3-----------------------4
            1   2   3   4   5   6
        2. Enter row, column, quadrant, direction for O: x
        Exiting program...
 
  */

#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>    // For toupper()
using namespace std;

// Global constants
const int BoardSize = 36;
const int NumberOfRows = 6;     // Used in the "algorithmic" approach to displayBoard(), which is commented out.
const int NumberOfColumns = 6;  // Used in the "algorithmic" approach to displayBoard(), which is commented out.
const char EmptyPiece = '.';


class Board
{
    public:
        // Default constructor
        Board() {
            // Initialize the playing board to be empty.
            for( int i=0; i<BoardSize; i++) {
                theBoard[ i] = EmptyPiece;
            }
        }
    
        // Accessor (get) and Mutator (set) member functions
        char getPieceAt( int index) { return theBoard[ index]; }
        void setPieceAt( char pieceToMove, int index) { theBoard[ index] = pieceToMove; }
    
        // Declaration of out-of-line member functions
        void displayBoard();
        bool allFiveAreSame( int position, int offset, char playerBeingChecked);
        bool notDone();
        void rotateBoardQuadrant( char quadrant, char rotateDirection);
    
    private:
        char theBoard[ BoardSize]; // The playing board
    
}; // end class Board


//-------------------------------------------------------------------------------------
// Display the board, which will look like:
//        1   2   3   4   5   6
//      1-----------------------2
//    A | .   .   . | .   .   . | A
//      |           |           |
//    B | .   .   . | .   .   . | B
//      |           |           |
//    C | .   .   . | .   .   . | C
//      |-----------+-----------|
//    D | .   .   . | .   .   . | D
//      |           |           |
//    E | .   .   . | .   .   . | E
//      |           |           |
//    F | .   .   . | .   .   . | F
//      3-----------------------4
//        1   2   3   4   5   6
void Board::displayBoard()
{
    // "Manually" display the board, which is in contrast to the "algorithmic"
    // approach which is commented out below.
    cout << endl
         << "    1   2   3   4   5   6   \n"
         << "  1-----------------------2 \n"
         << "A | " << theBoard[0]<< "   " << theBoard[1]<< "   " << theBoard[2]<< " | " << theBoard[3]<< "   " << theBoard[4]<< "   " << theBoard[5]<< " | A  \n"
         << "  |           |           | \n"
         << "B | " << theBoard[6]<< "   " << theBoard[7]<< "   " << theBoard[8]<< " | " << theBoard[9]<< "   " <<theBoard[10]<< "   " <<theBoard[11]<< " | B  \n"
         << "  |           |           | \n"
         << "C | " <<theBoard[12]<< "   " <<theBoard[13]<< "   " <<theBoard[14]<< " | " <<theBoard[15]<< "   " <<theBoard[16]<< "   " <<theBoard[17]<< " | C  \n"
         << "  |-----------+-----------| \n"
         << "D | " <<theBoard[18]<< "   " <<theBoard[19]<< "   " <<theBoard[20]<< " | " <<theBoard[21]<< "   " <<theBoard[22]<< "   " <<theBoard[23]<< " | D  \n"
         << "  |           |           | \n"
         << "E | " <<theBoard[24]<< "   " <<theBoard[25]<< "   " <<theBoard[26]<< " | " <<theBoard[27]<< "   " <<theBoard[28]<< "   " <<theBoard[29]<< " | E  \n"
         << "  |           |           | \n"
         << "F | " <<theBoard[30]<< "   " <<theBoard[31]<< "   " <<theBoard[32]<< " | " <<theBoard[33]<< "   " <<theBoard[34]<< "   " <<theBoard[35]<< " | F  \n"
         << "  3-----------------------4  \n"
         << "    1   2   3   4   5   6    "<< endl;

/*
//  The code below is an "algorithmic" approach to displaying the board, though in
//  my opinion is not as legible as the "manual" approach shown above.
    char rowLetter = 'A';
    cout << endl
         << "    1   2   3   4   5   6   \n"
         << "  1-----------------------2 \n";
    
    // For each row
    for( int row = 0; row < NumberOfRows; row++) {
        // Display the letter and opening bar
        cout << rowLetter << " |";
        
        // Display the middle contents
        for( int col = 0; col < NumberOfColumns; col++) {
            int pieceIndex = row * NumberOfColumns + col;
            cout << " " << theBoard[ pieceIndex];
            // Display a vertical piece if we're in the middle of the board
            //    or at the end of each line, else display spaces between pieces.
            if( (pieceIndex - 2) % 6 == 0  ||     // In the middle of a row
                (pieceIndex + 1) % 6 == 0         // At the end of a row
              ) {
                cout << " |";
            }
            else {
                cout << "  ";
            }
        }
        
        // Display the end of the row and advance the letter character
        cout << " " << rowLetter++ << endl;
        
        // Display the intervening row of blanks on all but the last line.
        // The rowLetter is 'G' the last time, after it gets incremented from
        // 'F' to 'G' in the line above.
        if( rowLetter < 'G') {
           // Display something different for the middle row
           if( rowLetter == 'D') {
              cout << "  |-----------+-----------| \n";           }
           else {
              cout << "  |           |           | \n";
           }
        }
    } // end for( int row...

    // Display the bottom of the table
    cout << "  3-----------------------4  \n"
         << "    1   2   3   4   5   6    " << endl;
*/
}//end Board::displayBoard()


//-------------------------------------------------------------------------------------
// Return true if the set of five pieces are all the same as the indicated ('X' or 'O') one,
// else return false.
bool Board::allFiveAreSame(
                int position,              // Index of 1st position to be checked
                int offset,                // Offset from each previous square
                char playerBeingChecked)   // 'X' or 'O'
{
    bool allPiecesAreSame = true;    // Assume all pieces are the same as a default
    
    for( int i=0; i<5; i++) {
        if( theBoard[ position] != playerBeingChecked) {
            allPiecesAreSame = false;
            break;  // Found a piece that is not the same, so break out of loop
        }
        position = position + offset;  // Advance to next index position
    }
    
    return allPiecesAreSame;
}//end Board::allFiveAreSame()



//-------------------------------------------------------------------------------------
// See if there are five in a row in any row, column or diagonal.
// The starting position and offset for the next square index to be checked are
// themselves stored in an array.  We have to not only check to see if some player
// won, but we have to see if *both* players have won, which would lead to a tie.
//
// The board index values are given here for reference:
//
//     0  1  2  3  4  5
//     6  7  8  9 10 11
//    12 13 14 15 16 17
//    18 19 20 21 22 23
//    24 25 26 27 28 29
//    30 31 32 33 34 35
//
bool Board::notDone()
{
    const int numberOfGroupsOfFive = 32;
    int playerOHasWon = false;
    int playerXHasWon = false;
    
    // Declare an array representing all the groups of five to check for a win.
    // For example, the entry {0,1} means start at index 0, and successively add
    // the offset 1 to find the other four pieces, to use in seeing if all five
    // are the same, which is a win.
    int checkPosition[ numberOfGroupsOfFive][2] = {
                 // First check rows, where offset is 1.
                 {0,1},{1,1},     // horizontal in first row, starting at 0 or at 1
                 {6,1},{7,1},     // horizontal in second row, starting at 6 or 7
                 {12,1},{13,1},   // horizontal in third row, starting at 12 or 13
                 {18,1},{19,1},   // horizontal in fourth row, starting at 18 or 19
                 {24,1},{25,1},   // horizontal in fifth row, starting at 24 or 25
                 {30,1},{31,1},   // horizontal in sixth row, starting at 30 or 31
                 // Now check columns, where offset is 6.
                 {0,6},{6,6},     // vertical in first column, starting at 0 or 6
                 {1,6},{7,6},     // vertical in second column, starting at 1 or 7
                 {2,6},{8,6},     // vertical in third column, starting at 2 or 8
                 {3,6},{9,6},     // vertical in fourth column, starting at 3 or 9
                 {4,6},{10,6},    // vertical in fifth column, starting at 4 or 10
                 {5,6},{11,6},    // vertical in sixth column, starting at 5 or 11
                 // Now check upper-left to lower-right diagonals, with offset of 7.
                 {1,7},{0,7},{7,7},{6,7},  // starting at 1, 0, 7 or 6
                 // Now check lower-left to upper-right diagonals, with offset of -5.
                 {24,-5},{30,-5},{25,-5},{31,-5}  // starting at 24, 30, 25 or 31
            };
    
    // Check to see if the board is full.  First count the number of blank squares on the board.
    int numberOfBlankSquaresOnBoard = 0;
    for( int i = 0; i < BoardSize; i++) {
        if( theBoard[ i] == EmptyPiece) {
            numberOfBlankSquaresOnBoard++;
        }
    }
    // If the number of blank squares on the board == 0, then return false (notDone() is false)
    // to allow exiting the program.
    if( numberOfBlankSquaresOnBoard == 0) {
       cout << "    *** No one has won.  Game is a tie." << endl;
       return false;  // notDone() is false, because we *are* done.
    }
    
    for( int i = 0; i < numberOfGroupsOfFive; i++) {
        // The next two lines are extracted for the purpose of code clarity, but code easily
        //   be instead inserted in-place in the code below.
        int startingPosition = checkPosition[i][ 0];  // Retrieve the index of starting square
        int offset = checkPosition[i][ 1];            // Retrieve the offset from previous square
        // checkPosition[ i] is itself a two-dimensional array of int, containing the
        // starting position of the set of 5 positions being checked, and the offset.
        // We have to check for a win for *both* X and O below, because it is possible that
        // a set of moves leads to both of them winning at the same time, which is a tie.
        if( allFiveAreSame( startingPosition, offset, 'X') ) {
            playerXHasWon = true;
        }
        if( allFiveAreSame( startingPosition, offset, 'O') ) {
            playerOHasWon = true;
        }
    } // end for( int

    // Check for a tie
    if( playerXHasWon && playerOHasWon) {
        cout << "    *** Both X and O have won.  Game is a tie." << endl;
        return false;   // We are done, so notDone() evaluates to false
    }
    
    // See if X has won
    if( playerXHasWon) {
        cout << "    *** X has won the game! " << endl;
        return false;   // We are done, so notDone() evaluates to false
    }
    
    // See if O has won
    if( playerOHasWon) {
        cout << "    *** O has won the game! " << endl;
        return false;   // We are done, so notDone() evaluates to false
    }
    
    // Neither has won.  Return true, since notDone() evaluates to true
    return true;
} // end Board::notDone()


//-------------------------------------------------------------------------------------
// Rotate the board quadrant in the selected direction ('L' for counter-clockwise,
// 'R' for clockwise).
// Board piece index values separated by quadrant are as follows:
//
//     0  1  2    3  4  5
//     6  7  8    9 10 11
//    12 13 14   15 16 17
//
//    18 19 20   21 22 23
//    24 25 26   27 28 29
//    30 31 32   33 34 35
//
// Each of these clusters of index values are stored below in an array, so that the
// same code can be used to rotate any of the four quadrants.
void Board::rotateBoardQuadrant(
    char quadrant,            // Quadrant '1'..'4'
    char rotateDirection)     // Direction ('L' or 'R') to rotate the chosen quadrant
{
    int quadrantValue = quadrant - '0';   // Convert quadrant character '1'..'4' to a numerical value 1..4
    // Store board piece index values to be rotated for each quadrant.  Add a "dummy"
    // first row (row 0) to this array, so that we can use the quadrant number ('1'..'4')
    // directly and don't need to subtract 1 from it.
    //
    //                     Index values:  0  1  2  3  4  5  6  7
    int quadrantIndexValues[ 5][ 8] = { {-1,-1,-1,-1,-1,-1,-1,-1}, // row 0
                                        { 0, 1, 2, 8,14,13,12, 6}, // row 1: Index values for quadrant 1
                                        { 3, 4, 5,11,17,16,15, 9}, // row 2: Index values for quadrant 2
                                        {18,19,20,26,32,31,30,24}, // row 3: Index values for quadrant 3
                                        {21,22,23,29,35,34,33,27}  // row 4: Index values for quadrant 4
                                      };
    int sourceIndex, destinationIndex;   // Used as intermediaries to store index values from above array
    
    // The code below rotates a single location in a circle.  Do this twice to give a 90 degree rotation.
    int j;
    for( j=0; j<2; j++) {
        
        // Have separate loops, depending on the direction of rotation.  The code below could easily
        // be compacted, but was left as-is to make it more clear in case you want to trace it.
        if( rotateDirection == 'R') {
            // First store the last character, so that we can store it into the first character at the end
            sourceIndex = quadrantIndexValues[ quadrantValue][ 7];
            char lastPiece = theBoard[ sourceIndex];
            // Rotate clockwise, starting with the last character
            for( int i=7; i>0; i--) {
                // The board index values we care about are stored in the 2-D array quadrantIndexValues
                sourceIndex = quadrantIndexValues[ quadrantValue][ i-1];
                destinationIndex = quadrantIndexValues[ quadrantValue][ i];
                theBoard[ destinationIndex] = theBoard[ sourceIndex];   // Shift the values
            }
            // Set the first character to be the old last character
            destinationIndex = quadrantIndexValues[quadrantValue][ 0];
            theBoard[ destinationIndex] = lastPiece;
        }
        else {
            // rotateDirection == 'L', to rotate counter-clockwise
            // First store the first character, so that we can store it into the last character at the end
            char firstPiece = theBoard[ quadrantIndexValues[quadrantValue][ 0] ];
            // Rotate counter-clockwise, starting with the first character
            for( int i=0; i<7; i++) {
                // The board index values we care about are themselves stored in a 2-D array
                destinationIndex = quadrantIndexValues[quadrantValue][ i];
                sourceIndex = quadrantIndexValues[quadrantValue][ i+1];
                theBoard[ destinationIndex] = theBoard[ sourceIndex];
            }
            // Set the last character to be the old first character
            destinationIndex = quadrantIndexValues[quadrantValue][ 7];
            theBoard[ destinationIndex] = firstPiece;
        }
        
    }//end for( j=0..
}//end Board::rotateBoardQuadrant(..)


//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << "\n"
         << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
         << "                                                                 \n"
         << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
         << "quadrants.  There are two players, X and O, who alternate turns. \n"
         << "The goal of each player is to get five of their pieces in a row, \n"
         << "either horizontally, vertically, or diagonally.                  \n"
         << "                                                                 \n"
         << "Players take turns placing one of their pieces into an empty     \n"
         << "space anywhere on the board, then choosing one of the four       \n"
         << "board quadrants to rotate 90 degrees left or right.              \n"
         << "                                                                 \n"
         << "If both players get five in a row at the same time, or the       \n"
         << "last move is played with no five in a row, the game is a tie.    \n"
         << "If a player makes five a row by placing a piece, there is no need\n"
         << "to rotate a quadrant and the player wins immediately.            \n"
         << "                                                                 \n"
         << "     Play online at:  https://perfect-pentago.net                \n"
         << "     Purchase at:     www.mindtwisterusa.com                     \n"
         << "                                                                 \n"
         << "For each move provide four inputs:                               \n"
         << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
         << "For instance input of B32R places the next piece at B3 and then  \n"
         << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
         << "                                                                 \n"
         << "At any point enter 'x' to exit the program or 'i' to display instructions." << endl;
} // end displayInstructions()


//-------------------------------------------------------------------------------------
// If move is invalid, return true, else return false.
// The pieceNumber is calculated from the row and column, with its calculated value
// reflected back to the calling part of the program since it is a reference parameter.
bool moveIsInvalid(
        Board theBoard,           // The playing board
        char moveRow,             // Row for the move; should be 'A'..'F'
        char moveColumn,          // Column for the move; should be '1'..'6'
        int &pieceNumber,         // Board piece 0..35 calculated from row and column
        char quadrant,            // Quadrant to be rotated ('1'..'4')
        char rotateDirection)     // Direction ('L' or 'R') to rotate the chosen quadrant
{

    // Validate move row
    if( moveRow < 'A' || moveRow > 'F') {
        cout << "    *** Invalid move row.  Please retry." << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    // Validate move column. (Note &* in scanf below could both be removed.)
    if( moveColumn < '1' || moveColumn > '6') {
        cout << "    *** Invalid move column.  Please retry." << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    // Calculate the piece number from row and column offsets
    pieceNumber = (moveRow-'A') * 6 + (moveColumn-'1');
    
    // Sanity check: Validate calculated piece location is on the board
    if( pieceNumber < 0 || pieceNumber > BoardSize) {
        // Sanity check.  Invalid row or invalid column should have triggered first.
        cout << "    *** Piece location is invalid.  Please retry." << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    // Piece is within range on the board.  Ensure it is empty
    if( theBoard.getPieceAt( pieceNumber) != EmptyPiece) {
        cout << "    *** That board location is already taken.  Please retry." << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    // Validate the quadrant choice
    if( quadrant < '1' || quadrant > '4') {
        cout << "    *** Selected quadrant is invalid.  Please retry. " << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    // Validate the quadrant rotate direction
    if( rotateDirection != 'L' &&  rotateDirection != 'R' ) {
        cout << "    *** Quadrant rotation direction is invalid.  Please retry. " << endl;
        return true;  // 1 is true, since move IS invalid
    }
    
    return false;  // return false, since move is NOT invalid
}//end moveIsInvalid()


//-------------------------------------------------------------------------------------
int main() {
    Board theBoard;         // Create the board as an instance of the Board class
    // The moveNumber and pieceToMove could appropriately be declared here, or in the Board class.
    int moveNumber = 1;
    char pieceToMove = 'X'; // Will be set to 'X' or 'O' depending on move number. Start with 'X'
    char moveRow;           // Will be 'A'..'F'
    char moveColumn;        // Will be '1'..'6'
    int pieceIndex;         // Calculated from moveRow and moveColumn
    char quadrant;          // Quadrant to be rotated ('1'..'4')
    char rotateDirection;   // Direction to rotate the chosen quadrant ('R' for clockwise,
                            //    'L' for counter clockwise)
    
    cout << "Welcome to Pentago, where you try to get 5 of your pieces in a line.\n"
         << "At any point enter 'x' to exit or 'i' for instructions. "
         << endl;
    
    // Loop while no one has won and empty spots remain
    while( theBoard.notDone() ) {

        // Infinite loop getting user input, to handle input error checking
        // Program assumes 4 inputs are given: row, column, quadrant, direction
        while( true) {
            theBoard.displayBoard();   // Display the board
        
            // Prompt for and get user input
            cout << moveNumber << ". Enter row, column, quadrant, direction for " << pieceToMove << ": ";
            cin >> moveRow;
            // convert to upper case to make it easier to check
            moveRow = toupper( moveRow);
            
            // Handle 'X' to exit, if that was entered
            if( moveRow == 'X') {
                cout << "Exiting program...\n" << endl;
                exit( 0);
            }
            // Handle 'I' to display instructions
            if( moveRow == 'I') {
                displayInstructions();
                continue;   // Loop back up to reprompt for move
            }
            
            // Read in column for the move, quadrant to be rotated, and rotate direction
            cin >> moveColumn >> quadrant >> rotateDirection;
            // Ensure rotate direction is upper case.  This is not needed for moveColumn
            //   and for quadrant, since they are numeral characters that don't have upper/lower case.
            rotateDirection = toupper( rotateDirection);
            
            // Validate user input
            if( moveIsInvalid( theBoard, moveRow, moveColumn, pieceIndex, quadrant, rotateDirection)) {
                continue;   // loop back up to get user input again
            }
            else {
                break;  // move was valid, so break out of the move validation loop
            }
        }//end while( true)
        
        // Make the move by placing the current piece to move into the selected open position.
        theBoard.setPieceAt( pieceToMove, pieceIndex);
        
        // Ensure there is not an immediate win, even before the subsequent rotation
        if( theBoard.notDone() ) {
            // Do the selected rotation
            theBoard.rotateBoardQuadrant( quadrant, rotateDirection);
            
            // A valid move was made, so increment the move number.
            moveNumber++;
            
            // Get the new pieceToMove, depending on whether moveNumber is even or odd
            if( moveNumber%2 == 1) {
                pieceToMove = 'X';   // odd numbered moves
            }
            else {
                pieceToMove = 'O';   // even numbered moves
            }
        }
        else {
            break;  // If there was an immediate win, exit loop.
        }
        
    }//end while( notDone(board)
    
    // Redisplay the board.
    theBoard.displayBoard();
    
    cout << "Thanks for playing.  Exiting... " << endl;
    return 0;
} // end main()
