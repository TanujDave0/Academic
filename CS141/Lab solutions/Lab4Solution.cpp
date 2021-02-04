// TicTacToe.cpp   
// for CS 141 lab 4
// 
#include <iostream>
using namespace std;


//----------------------------------------------------------------------------------
// Display the board.
// HINT: Supply parameters for all the board position variables.
// *** In the line below supply the return type and any needed parameters.
void displayBoard( char p1, char p2, char p3,
                   char p4, char p5, char p6,
                   char p7, char p8, char p9)
{
	cout << endl
	     << "------- \n"
	     << "|" << p1 << "|" << p2 << "|" << p3 << "|   1  2  3\n"
	     << "------- \n"
	     << "|" << p4 << "|" << p5 << "|" << p6 << "|   4  5  6\n"
	     << "------- \n"
	     << "|" << p7 << "|" << p8 << "|" << p9 << "|   7  8  9\n"
	     << "------- \n" 
	     << endl;
} // end displayBoard(...)


//----------------------------------------------------------------------------------
// Make a move by placing the correct character at the position indicated by the user.
// HINT: An ampersand '&' must be placed between a parameter type and the
// parameter name if you want changes to that parameter to be reflected back to 
// the calling code in main( ). 
// *** In the line below supply the return type and any needed parameters.
void makeMove( char &p1, char &p2, char &p3,     // The board variables
               char &p4, char &p5, char &p6,
               char &p7, char &p8, char &p9,
               int position,                 // Destination for the move
               char pieceToMove)             // The character to be placed at the destination
{
   	// Make move
		switch (position) {
			case 1: p1 = pieceToMove; break;
			case 2: p2 = pieceToMove; break;
			case 3: p3 = pieceToMove; break;
			case 4: p4 = pieceToMove; break;
			case 5: p5 = pieceToMove; break;
			case 6: p6 = pieceToMove; break;
			case 7: p7 = pieceToMove; break;
			case 8: p8 = pieceToMove; break;
			case 9: p9 = pieceToMove; break;
		}
}// end makeMove(...)


//----------------------------------------------------------------------------------
// After every move check the board for a winning condition.
// E.g. If the top row variables all have the same character
// (in positions 1,2 and 3) then there would be a win. If a winning  
// condition is found, return true, else return false.
// Check for win using board positions:
//    1 2 3
//    4 5 6
//    7 8 9
// *** In the line below supply the return type and any needed parameters.
bool thereIsAWin( char p1, char p2, char p3,
                  char p4, char p5, char p6,
                  char p7, char p8, char p9)
{
	// if winning condition found then set win = true
	bool win = false;
	if( (p1==p2 && p2==p3 && p3!=' ') ||  // top row
		 (p4==p5 && p5==p6 && p6!=' ') ||  // middle row
		 (p7==p8 && p8==p9 && p9!=' ') ||  // bottom row
		 (p1==p4 && p4==p7 && p7!=' ') ||  // left column
		 (p2==p5 && p5==p8 && p8!=' ') ||  // middle column
		 (p3==p6 && p6==p9 && p9!=' ') ||  // right column
		 (p1==p5 && p5==p9 && p9!=' ') ||  // upper-left to lower-right diagonal
		 (p7==p5 && p5==p3 && p3!=' ')     // lower-left to upper-right diagonal
     ){
		   win = true;
      }
   return win;
} // end thereIsAWin(...)


//----------------------------------------------------------------------------------
// Check whether the move position entered is valid, returning true or false.
// Receive parameters for the move position and all the board pieces.
// If the intended destination is already occupied or the selected
// move position is not between 1..9 (inclusive) then return false.
// *** In the line below supply the return type and any needed parameters and uncomment it.
bool moveIsValid( char &p1, char &p2, char &p3,     // The board variables
                  char &p4, char &p5, char &p6,
                  char &p7, char &p8, char &p9,
                  int position,                 // Destination for the move
                  char pieceToMove)             // The character to be placed at the destination
{
   bool returnValue = true;
   
   if( (position == 1 && p1 != ' ') ||
       (position == 2 && p2 != ' ') ||
       (position == 3 && p3 != ' ') ||
       (position == 4 && p4 != ' ') ||
       (position == 5 && p5 != ' ') ||
       (position == 6 && p6 != ' ') ||
       (position == 7 && p7 != ' ') ||
       (position == 8 && p8 != ' ') ||
       (position == 9 && p9 != ' ') ||
       position < 1 ||
       position > 9
     ) {
      returnValue = false;   // move is not valid        
   }
   
   return returnValue;
} // end moveIsValid(...)


//----------------------------------------------------------------------------------
int main()
{
   
   // Declare variables here
   char p1,p2,p3,
        p4,p5,p6,
        p7,p8,p9;
   
	// Initialize the board variables
	p1=p2=p3=p4=p5=p6=p7=p8=p9=' ';
	char pieceToMove = 'X';           // 'X' gets the first move
	int position = 0;
	int moveNumber = 1;
	     
	cout << "Welcome to the TicTacToe game!                  \n"
	     << "Take turns entering the move destination (1..9) \n"  
		  << "or '0' (zero) to exit." 
		  << endl;

	// Main loop
	while( moveNumber <= 9) {      // if winning condition not found the game stops after 9 moves
	
	   // *** Fix the call to function displayBoard in the line below, and uncomment it.
	   displayBoard( p1,p2,p3,p4,p5,p6,p7,p8,p9);
   
		// Prompt for and get move.  
		cout << moveNumber << ". Enter the move (1..9) for " << pieceToMove << ": ";
		cin >> position;       // the position at which the move is made
	   
		// See if 0 was entered, indicating the desire to exit the program
		if( position == 0) {
		   // 0 was entered. Break out of enclosing loop, to exit the program.
		   break;
		}
		
		// Validate intended move.  If move is not valid, give a message and loop back up to retry.
		// *** Correct the line below where function moveIsValid(...) is called, and uncomment the section.
		if( ! moveIsValid( p1,p2,p3,p4,p5,p6,p7,p8,p9, position, pieceToMove) ) {
		   cout << "That move is not valid.  Retry.";
		   continue;
		}
		
	   // Make the move, placing the character on the board.  
	   makeMove( p1,p2,p3,p4,p5,p6,p7,p8,p9, position, pieceToMove);        
      
		// *** Add any needed parameters below to function thereIsAWin(...). 
      if( thereIsAWin( p1,p2,p3,p4,p5,p6,p7,p8,p9) ) {        // if win was detected then the game stops
         // After a win again display the board.
   	   // *** Fix the call to function displayBoard(...) in the line below, and uncomment it.
         displayBoard( p1,p2,p3,p4,p5,p6,p7,p8,p9);
         cout << endl 
		     << "Congratulations player " << pieceToMove << ". You WON!" << endl;
          break;
      }
   
	   // Change to the other piece for next move.  
	   if( pieceToMove == 'X') {
		   pieceToMove = 'O';
	   }
	   else {
		   pieceToMove = 'X';
	   }

	   moveNumber++;
	} // end 	while( moveNumber

	cout << "Exiting program..." << endl;
	return 1;

} // end main()
