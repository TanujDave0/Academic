//  prog2Cuatro.cpp
//
//  Created 1/25/2020 by Dale Reed for CS 141 program 2.
//  System: Xcode on iMac
//
/*  Running the program looks like:

        Welcome to the game of Cuatro, where you try to complete a set
        of four pieces that are alike.  Players take turns making moves.
        On each move your OPPONENT chooses the piece, then YOU get to
        place it on the board.  If you create a set of four alike when
        you place your piece, then you win!

        A set of four alike can be completed by using four all upper (or all
        lower) case characters, four all vowels (or all consonants), or four
        all curved (or all straight-lined). Curved letters are 'O' and 'C'
        (upper or lower), and straight-line letters are 'I' and 'Z' (upper or
        lower). Groups of four can be created in a row, column, diagonal, or
        corner quadrant.

        When prompted for input you may also enter 'x' or 'X' to exit.

              ---------    Square #
             | . . . . |  1  2  3  4
             | . . . . |  5  6  7  8
             | . . . . |  9 10 11 12
             | . . . . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper: OO/CC  II/ZZ
                   Lower: oo/cc  ii/zz
                         Vowel/Consonant
        1. Player 1 enter piece, and Player 2 enter destination: C6

              ---------    Square #
             | . . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . . . |  9 10 11 12
             | . . . . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper: OO/ C  II/ZZ
                   Lower: oo/cc  ii/zz
                         Vowel/Consonant
        2. Player 2 enter piece, and Player 1 enter destination: O 1

              ---------    Square #
             | O . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . . . |  9 10 11 12
             | . . . . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper:  O/ C  II/ZZ
                   Lower: oo/cc  ii/zz
                         Vowel/Consonant
        3. Player 1 enter piece, and Player 2 enter destination: z12

              ---------    Square #
             | O . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . . z |  9 10 11 12
             | . . . . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper:  O/ C  II/ZZ
                   Lower: oo/cc  ii/ z
                         Vowel/Consonant
        4. Player 2 enter piece, and Player 1 enter destination: i 15

              ---------    Square #
             | O . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . . z |  9 10 11 12
             | . . i . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper:  O/ C  II/ZZ
                   Lower: oo/cc   i/ z
                         Vowel/Consonant
        5. Player 1 enter piece, and Player 2 enter destination: c 11

              ---------    Square #
             | O . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . c z |  9 10 11 12
             | . . i . | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper:  O/ C  II/ZZ
                   Lower: oo/ c   i/ z
                         Vowel/Consonant
        6. Player 2 enter piece, and Player 1 enter destination: o 16

              ---------    Square #
             | O . . . |  1  2  3  4
             | . C . . |  5  6  7  8
             | . . c z |  9 10 11 12
             | . . i o | 13 14 15 16
              ---------
             Pieces:     Curved Straight
                   Upper:  O/ C  II/ZZ
                   Lower:  o/ c   i/ z
                         Vowel/Consonant
        *** Player 1 you won!
 */
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
#include <cctype>     // for toupper()
#include <string>     // needed to use type string in some compilers, though not all
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Global variables to represent the 16 board pieces and C++ strings representing
// the pieces that have not yet been played.  Since these are global they don't
// need to be passed as parameters to functions, and are shared over the entire program.
// Normally global variables will not be allowed.
char p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;
string upperRowPiecesToPlay    = "OO/CC  II/ZZ";
string lowerRowPiecesToPlay = "oo/cc  ii/zz";

//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << "Welcome to the game of Cuatro, where you try to complete a set      \n"
         << "of four pieces that are alike.  Players take turns making moves.    \n"
         << "On each move your OPPONENT chooses the piece, then YOU get to       \n"
         << "place it on the board.  If you create a set of four alike when      \n"
         << "you place your piece, then you win!       \n"
         << "\n"
         << "A set of four alike can be completed by using four all upper (or all\n"
         << "lower) case characters, four all vowels (or all consonants), or four\n"
         << "all curved (or all straight-lined). Curved letters are 'O' and 'C'\n"
         << "(upper or lower), and straight-line letters are 'I' and 'Z' (upper or\n"
         << "lower). Groups of four can be created in a row, column, diagonal, or\n"
         << "corner quadrant.\n"
         << "\n"
         << "When prompted for input you may also enter 'x' or 'X' to exit." << endl;
}// end displayInstructions()


//-------------------------------------------------------------------------------------
// Use the 16 global board piece variables to display the board and the pieces remaining
// to be placed on the board.  At the beginning of the game the board looks like:
/*
      ---------    Square #
     | . . . . |  1  2  3  4
     | . . . . |  5  6  7  8
     | . . . . |  9 10 11 12
     | . . . . | 13 14 15 16
      ---------
     Pieces:     Curved Straight
           Upper: OO/CC  II/ZZ
           Lower: oo/cc  ii/zz
                 Vowel/Consonant
 */
void displayBoard()
{
cout << "\n"
     << "      ---------    Square #  \n"
     << "     | "<< p1<<" "<< p2<<" "<< p3<<" "<< p4<<" |  1  2  3  4 \n"
     << "     | "<< p5<<" "<< p6<<" "<< p7<<" "<< p8<<" |  5  6  7  8 \n"
     << "     | "<< p9<<" "<<p10<<" "<<p11<<" "<<p12<<" |  9 10 11 12 \n"
     << "     | "<<p13<<" "<<p14<<" "<<p15<<" "<<p16<<" | 13 14 15 16 \n"
     << "      ---------              \n"
     << "     Pieces:     Curved Straight                \n"
     << "           Upper: " << upperRowPiecesToPlay    << "\n"
     << "           Lower: " << lowerRowPiecesToPlay << "\n"
     << "                 Vowel/Consonant  "
     << endl;
} // end displayBoard()


//-------------------------------------------------------------------------------------
// Utility function to get the character stored in any of the 16 board pieces:
//     | . . . . |  1  2  3  4
//     | . . . . |  5  6  7  8
//     | . . . . |  9 10 11 12
//     | . . . . | 13 14 15 16
char getPieceAt( int position)
{
    char thePiece = ' ';   // Piece value to be returned will be stored here.
    
    switch( position) {
       case  1: thePiece =  p1; break;
       case  2: thePiece =  p2; break;
       case  3: thePiece =  p3; break;
       case  4: thePiece =  p4; break;
       case  5: thePiece =  p5; break;
       case  6: thePiece =  p6; break;
       case  7: thePiece =  p7; break;
       case  8: thePiece =  p8; break;
       case  9: thePiece =  p9; break;
       case 10: thePiece = p10; break;
       case 11: thePiece = p11; break;
       case 12: thePiece = p12; break;
       case 13: thePiece = p13; break;
       case 14: thePiece = p14; break;
       case 15: thePiece = p15; break;
       case 16: thePiece = p16; break;
       otherwise: // Sanity check, should never get here
            cout << "Invalid position " << position
                 << " inside getPieceAt() function.  Exiting..." << endl;
            exit( -1);
            break;
    }//end switch( position)
    
    return thePiece;
} // end getPieceAt()


//-------------------------------------------------------------------------------------
// Utility function to set the character to be stored into any of the 16 board pieces.
//     | . . . . |  1  2  3  4
//     | . . . . |  5  6  7  8
//     | . . . . |  9 10 11 12
//     | . . . . | 13 14 15 16
void setPieceAt(
        char theCharacter,  // The character to be stored
        int destination)    // The variable number into which it is to be stored
{
    switch( destination) {
       case  1:  p1 = theCharacter; break;
       case  2:  p2 = theCharacter; break;
       case  3:  p3 = theCharacter; break;
       case  4:  p4 = theCharacter; break;
       case  5:  p5 = theCharacter; break;
       case  6:  p6 = theCharacter; break;
       case  7:  p7 = theCharacter; break;
       case  8:  p8 = theCharacter; break;
       case  9:  p9 = theCharacter; break;
       case 10: p10 = theCharacter; break;
       case 11: p11 = theCharacter; break;
       case 12: p12 = theCharacter; break;
       case 13: p13 = theCharacter; break;
       case 14: p14 = theCharacter; break;
       case 15: p15 = theCharacter; break;
       case 16: p16 = theCharacter; break;
       otherwise: // Sanity check, should never get here
            cout << "Invalid destination " << destination
                 << " inside setPieceAt() function.  Exiting..." << endl;
            exit( -1);
            break;
    }//end switch( position)
} // end setPieceAt()


//-------------------------------------------------------------------------------------
// See if the piece to be played is in the set of playable pieces.
// This is nearly identical to the function blankoutPieceInPlayablePieces() below except this
// version only identifies whether or not the piece is present, and does not blank it out.
// This function is used to validate moves before actually making them.
bool findPieceInPlayablePieces(
        char pieceToPlay,       // The single character to be played
        string piecesToPlay)    // The C++ string containing the character to be found
{
    bool pieceWasFound = false; // Used to keep track of whether or not the desired piece is found
    
    // Iterated through the string, comparing one by one until the piece to be played is found.
    for( int i=0; i<piecesToPlay.length(); i++) {
        if( piecesToPlay[ i] == pieceToPlay) {
            pieceWasFound = true;     // Indicate that piece was found
            break;                    // Break out of loop, since we're done
        }
    }
    
    return pieceWasFound;
} // end findPieceInPlayablePieces()


//-------------------------------------------------------------------------------------
// Find the piece being played in the set of playable pieces and blank it out.
// This is identical to the function findPieceInPlayablePieces() above except this
// version not only finds the piece, but also blanks it out.
// This function is used after a move has been already validated and we are actually making the move.
bool blankoutPieceInPlayablePieces(
        char pieceToPlay,       // The single character to be played
        string &piecesToPlay)   // The C++ string containing the character, which should be removed.
                                //    This must be a reference parameter otherwise only the copy is
                                //    changed and not the original string.
{
    bool pieceWasFound = false; // Used for sanity check to ensure piece to be played was found
    
    // Iterated through the string, comparing one by one until the piece to be played is found.
    for( int i=0; i<piecesToPlay.length(); i++) {
        if( piecesToPlay[ i] == pieceToPlay) {
            pieceWasFound = true;     // Indicate that piece was found
            piecesToPlay[ i] = ' ';   // Blank out the piece so it can't be used again
            break;                    // Break out of loop, since we're done
        }
    }
    
    return pieceWasFound;
} // end blankoutPieceInPlayablePieces()


//-------------------------------------------------------------------------------------
// If the move is invalid then display the error message that corresponds to the error
// and return true.  If the move is valid then return false.
bool moveIsInvalid(
        char pieceToPlay,     // The piece to be placed onto the board
        int destination)       // The location where this piece is to be played
{
    // Verify that piece is one of the valid pieces remaining to be played
    if( !findPieceInPlayablePieces( pieceToPlay, upperRowPiecesToPlay) &&
        !findPieceInPlayablePieces( pieceToPlay, lowerRowPiecesToPlay)
      ) {
        cout << "*** Sorry, that is an invalid piece.  Please retry." << endl;
        return true;   // Move is invalid
    }
    
    // Verify that destination is within the valid range
    if( destination < 1 || destination > 16) {
        cout << "*** Sorry, that destination is invalid.  Please retry." << endl;
        return true;   // Move is invalid
    }
    
    // Verify that destination is not already occupied
    if( getPieceAt( destination) != '.') {
        cout << "*** Sorry, that destination is occupied.  Please retry." << endl;
        return true;   // Move is invalid
    }
    
    return false;
} // end moveIsInvalid()


//-------------------------------------------------------------------------------------
// Now that move has been validated, remove the played piece from the set of pieces to
// play. Make the move by placing the pieceToPlay into the variable that corresponds
// with the destination.
void makeMove(
        char pieceToPlay,     // The piece to be placed onto the board
        int destination)      // The location where this piece is to be played
{
    bool pieceWasFound = false;     // Used for move validation

    // Remove this piece from the set of possible pieces to be placed.  Note that move
    // validation has previously been done to ensure the move was valid to begin with.
    if( isupper( pieceToPlay) ) {
        pieceWasFound = blankoutPieceInPlayablePieces( pieceToPlay, upperRowPiecesToPlay);
    }
    else {
        pieceWasFound = blankoutPieceInPlayablePieces( pieceToPlay, lowerRowPiecesToPlay);
    }
    
    // Sanity check.  This should never be true if previous move validation did its job correctly.
    if( ! pieceWasFound) {
        cout << "Inside makeMove(), piece " << pieceToPlay
             << " was not found in " << upperRowPiecesToPlay << " or in "
             << lowerRowPiecesToPlay << ". Exiting program..." << endl;
        exit( -1);
    }
    
    // Place the selected piece into the indicated destination variable
    setPieceAt( pieceToPlay, destination);
} // end makeMove()


//-------------------------------------------------------------------------------------
// Swap the values of playerToMove and otherPlayer.
// For example to begin if they are 1 and 2, then they will be swapped to 2 and 1.
// They are both reference parameters so that changes get reflected back to the caller.
void swap(
        int &playerToMove,   // 1 or 2
        int &otherPlayer)    // 2 or 1
{
    int temp = playerToMove;
    playerToMove = otherPlayer;
    otherPlayer = temp;
} // end swap()


//-------------------------------------------------------------------------------------
// Character matches one of the two characters sent as parameters, matching either
// upper or lower case.  This code is shared among isStraightLine(), isCurved(),
// isVowel(), and isConsonant().
bool matches(
        char c,     // The character to compare
        char c1,    // The first character against which to compare
        char c2)    // The second character against which to compare
{
    c = toupper( c);    // Convert original character to upper case to make subsequent
                        //    comparison simpler.
    if( c == c1 || c == c2) {
        return true;
    }
    else {
        return false;
    }
} // end matches()


//-------------------------------------------------------------------------------------
// Return true if character c is a stright-line character, one of: Z,z,I,i, else return false.
bool isStraightLine( char c)
{
    return matches( c, 'Z', 'I');
} // end isStraightLine()


//-------------------------------------------------------------------------------------
// Return true if character c is a curved character, one of: O,o,C,c, else return false.
bool isCurved( char c)
{
    return matches( c, 'C', 'O');
} // end isCurved()


//-------------------------------------------------------------------------------------
// Return true if character c is a vowel, one of: O,o,I,i, else return false.
bool isVowel( char c)
{
    return matches( c, 'O', 'I');
} // end isVowel()


//-------------------------------------------------------------------------------------
// Return true if character c is a consonant, one of: Z,z,C,c, else return false.
bool isConsonant( char c)
{
    return matches( c, 'Z', 'C');
} // end isConsonant()


//-------------------------------------------------------------------------------------
// See if the four characters match.  They match if they are all in one of the following groups:
//    1. Upper case
//    2. Lower case
//    3. Straight-line (Z,z,I,i)
//    4. Curved (O,o,C,c)
//    5. Vowels (O,o,I,i)
//    6. Consonants (Z,z,C,c)
// The functions used to implement the above conditions could have been combined into one,
// but this was not done to make the code more clear.
bool piecesMatch( char c1, char c2, char c3, char c4)
{
    if( // Check if all are upper case
        ( isupper( c1) && isupper( c2) && isupper( c3) && isupper( c4) ) ||
       
        // Check if all are lower case
        ( islower( c1) && islower( c2) && islower( c3) && islower( c4) ) ||
       
        // Check if all are straight-line
        ( isStraightLine( c1) && isStraightLine( c2) && isStraightLine( c3) && isStraightLine( c4) ) ||
       
        // Check if all are curved
        ( isCurved( c1) && isCurved( c2) && isCurved( c3) && isCurved( c4) ) ||
       
        // Check if all are vowels
        ( isVowel( c1) && isVowel( c2) && isVowel( c3) && isVowel( c4) ) ||
       
        // Check if all are consonants
        ( isConsonant( c1) && isConsonant( c2) && isConsonant( c3) && isConsonant( c4) )
      ) {
      return true;      // All four pieces match according to one of the criteria
    }
    else {
        return false;   // Pieces do not match
    }
} // end piecesMatch()


//-------------------------------------------------------------------------------------
// If no one has won and there is still space on the board, then return true, else false.
// Check for all possible winning sets of 4, which could be in a row, column, diagonal
// or corner quadrant.  For reference the board index values are:
//     1  2  3  4
//     5  6  7  8
//     9 10 11 12
//    13 14 15 16
// The order in which winning configurations are checked because the same message is shown
// in all cases, and only the most recent moving player can win on a move.
bool notDone( int playerWhoJustMoved)
{
    if( // Check rows, top down
        piecesMatch( getPieceAt( 1), getPieceAt( 2), getPieceAt( 3), getPieceAt( 4)) ||
        piecesMatch( getPieceAt( 5), getPieceAt( 6), getPieceAt( 7), getPieceAt( 8)) ||
        piecesMatch( getPieceAt( 9), getPieceAt(10), getPieceAt(11), getPieceAt(12)) ||
        piecesMatch( getPieceAt(13), getPieceAt(14), getPieceAt(15), getPieceAt(16)) ||
       
        // Check columns, left to right
        piecesMatch( getPieceAt( 1), getPieceAt( 5), getPieceAt( 9), getPieceAt(13)) ||
        piecesMatch( getPieceAt( 2), getPieceAt( 6), getPieceAt(10), getPieceAt(14)) ||
        piecesMatch( getPieceAt( 3), getPieceAt( 7), getPieceAt(11), getPieceAt(15)) ||
        piecesMatch( getPieceAt( 4), getPieceAt( 8), getPieceAt(12), getPieceAt(16)) ||
       
        // Check diagonals, first upper-left to lower-right, then lower-left to upper-right
        piecesMatch( getPieceAt( 1), getPieceAt( 6), getPieceAt(11), getPieceAt(16)) ||
        piecesMatch( getPieceAt(13), getPieceAt(10), getPieceAt( 7), getPieceAt( 4)) ||
       
        // Check corner quadrants, clockwise starting from upper-left
        piecesMatch( getPieceAt( 1), getPieceAt( 2), getPieceAt( 6), getPieceAt( 5)) ||
        piecesMatch( getPieceAt( 3), getPieceAt( 4), getPieceAt( 8), getPieceAt( 7)) ||
        piecesMatch( getPieceAt(11), getPieceAt(12), getPieceAt(16), getPieceAt(15)) ||
        piecesMatch( getPieceAt( 9), getPieceAt(10), getPieceAt(14), getPieceAt(13))
      ) {
        displayBoard();   // Display the winning board configuration
        cout << "*** Player " << playerWhoJustMoved << " you won!" << endl;
        return false;   // We *are* done, since there was a winning set of 4
    }
    else {
        return true;    // We are not done yet
    }
} // end notDone()


//-------------------------------------------------------------------------------------
int main()
{
    // Initialize the global board piece variables to all be '.'
    p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16='.';
    int moveNumber = 1;      // Is incremented after every move
    int playerToMove = 1;    // The current player to move, alternating between 1 and 2
    int otherPlayer = 2;     // The other player, alternating between 2 and 1
    char pieceToPlay = ' ';  // The piece to be played on this move
    int destination = 0;     // Destination square where piece is to be placed
    
    displayInstructions();
    
    do {
        displayBoard();
        
        // Exit the game play loop if all pieces have been played and no one has won.
        if( moveNumber == 17) {
            break;              // Break out of game play loop
        }
        
        // Display prompt and get user input
        cout << moveNumber << ". Player " << playerToMove << " enter piece, "
             << "and Player " << otherPlayer << " enter destination: ";
        cin >> pieceToPlay;
        
        // Handle input of 'x' or 'X' to exit
        if( pieceToPlay == 'x' || pieceToPlay == 'X') {
            cout << "Exiting program...\n";
            exit( 0);
        }
        cin >> destination;
        
        // Validate user input, giving an error message if not valid
        if( moveIsInvalid( pieceToPlay, destination) ) {
            // Loop back up to try this move again
            continue;
        }
        
        // Make the move, now that it has been validated
        makeMove( pieceToPlay, destination);
        
        // Update move number and whose turn it is for next move
        swap( playerToMove, otherPlayer);
        moveNumber++;  // Increment the moveNumber
        
    } while( notDone( playerToMove) );
    
    return 0;
} // end main()
