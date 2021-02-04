// TicTacToe.cpp   
// for CS 141 lab 3	

#include <iostream>
using namespace std;


char p1,p2,p3,p4,p5,p6,p7,p8,p9;
int win;
char pieceToMove;           
int position;

//Running display board should print out the board and the pieces if move has been made
//Running the code without making any move should look like:
//   -------
//   | | | |   1  2  3
//   -------
//   | | | |   4  5  6
//   -------
//   | | | |   7  8  9
//   -------
//
// Running the code after making the move should display the peice on the board:
//   -------
//   |X| | |   1  2  3
//   -------
//   | | | |   4  5  6
//   -------
//   | | | |   7  8  9
//   -------

void displayBoard(){
   //write your code here
   // *** Hint: This whole section of code should be a function call in your new version
	cout << endl
		 << "------- \n"
	     << "|" << p1 << "|" << p2 << "|" << p3 << "|   1  2  3\n"
	     << "------- \n"
	     << "|" << p4 << "|" << p5 << "|" << p6 << "|   4  5  6\n"
	     << "------- \n"
	     << "|" << p7 << "|" << p8 << "|" << p9 << "|   7  8  9\n"
	     << "------- " 
	     << endl;
}

// This function allows the player to make a move.
//the function should be able to place the correct character at the position
//entered by user.

void makeMove(){
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

}


//this function checks the board after every move 
// for a winning condition.
//For eg. the winning condition could be poistion 1,2,3 having the same character.
//if winning condition is found set the global varaible win to be 1
void checkBoard(){
   // Check for win using board positions:
		//    1 2 3
		//    4 5 6
		//    7 8 9
		if( (p1==p2 && p2==p3 && p3!=' ') ||  // top row
			(p4==p5 && p5==p6 && p6!=' ') ||  // middle row
			(p7==p8 && p8==p9 && p9!=' ') ||  // bottom row
			(p1==p4 && p4==p7 && p7!=' ') ||  // left column
			(p2==p5 && p5==p8 && p8!=' ') ||  // middle column
			(p3==p6 && p6==p9 && p9!=' ') ||  // right column
			(p1==p5 && p5==p9 && p9!=' ') ||  // upper-left to lower-right diagonal
			(p7==p5 && p5==p3 && p3!=' ')     // lower-left to upper-right diagonal
	      ){
	         displayBoard();
	         cout << endl 
			     << "Congratulations player " << pieceToMove << ". You WON!" << endl;
			   win =1;
	      }
}

int main()
{
	// Initialize the board
	p1=p2=p3=p4=p5=p6=p7=p8=p9=' ';
	pieceToMove = 'X';           // 'X' gets the first move
	position = 0;
	int moveNumber = 1;
	win = 0;
	     
	cout << "Welcome to the TicTacToe game! " << endl
	     << "Take turns entering the position (1..9)" << endl
	     << "into which your piece will be placed. "  
		 << endl << "Enter '0' (zero) to exit." 
		 << endl;
 
  displayBoard();

	// Main loop
	while( moveNumber <= 9) {      // if winning condition not found the game stops after 9 moves
		// Prompt for and get move.  
		cout << moveNumber << ". Enter the move (1..9) for " << pieceToMove << ": ";
		cin >> position;       // the position at which the move is made
		if(position !=0){
	    	makeMove();        // make the move to place teh character on the board
		   checkBoard();      //checks the board for winning condition
	      if(win==1){        // if win was detected then the game stops
	          break;
	      }
	   
		   // the game continues if the win flag was not set to 1
		   // Change to other piece for next move.  
		   if( pieceToMove == 'X') {
			   pieceToMove = 'O';
		   }
		   else {
			   pieceToMove = 'X';
		   }

	      displayBoard();     //display the current board

		   moveNumber++;
		}
		else{
		   break;
		}
	}

	cout << "Exiting program..." << endl;
	return 1;

}// end main()
