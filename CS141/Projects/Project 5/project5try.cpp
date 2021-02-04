/* ----------------------------------------------------------- 
Program 5:

Class: CS 141, Spring 2020.  Tues 4pm lab
Author: Tanuj Dave (tdave6)

-----------------------------------------------------------
*/
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
#include <cctype>
#include <vector>
#include <string>
using namespace std;

// function that displays the instructions.
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

// class for the Pentago board.
class Pentago{
    public:
        Pentago(); // default constructor.
        int checkForWin(int& playersWon, char& playerWonChar); // checks for winning conditions.
        void makeMove(char row, char columnInt, char quadrantInt, char direction, char playerSymbol, int& win); // function for maing move.
        void rotateQuadrant(int swapVariable, char direction); // function for rotating a quadrant.
        void displayBoard(); // function to display the board.
        void displayWin(int playersWon, char playerWonChar); // function that displays win messages.
        bool checkInput(char row, char column, char quadrant, char direction); // function for checking input correctness.
        void swapPieces(int firstIndex, int secondIndex); // function that swaps board pieces.
        void numberOfPlayersWon(int& playersWon, char& playerWonChar, int index);  // function to assign number of players won.

    private:
        vector<char> boardPieces = vector<char>(36); // board pieces as in a vector.
};

// default constructor.
Pentago::Pentago(){
    for(int i=0; i<36; ++i)
        boardPieces.at(i) = '.';
}

// function to display the board.
void Pentago::displayBoard(){
    cout<<"    1   2   3   4   5   6\n"
        <<"  1-----------------------2\n"
        <<"A | "<<boardPieces.at(0)<<"   "<<boardPieces.at(1)<<"   "<<boardPieces.at(2)<<" | "<<boardPieces.at(3)<<"   "<<boardPieces.at(4)<<"   "<<boardPieces.at(5)<<" | A\n"
        <<"  |           |           |\n"
        <<"B | "<<boardPieces.at(6)<<"   "<<boardPieces.at(7)<<"   "<<boardPieces.at(8)<<" | "<<boardPieces.at(9)<<"   "<<boardPieces.at(10)<<"   "<<boardPieces.at(11)<<" | B\n"
        <<"  |           |           |\n"
        <<"C | "<<boardPieces.at(12)<<"   "<<boardPieces.at(13)<<"   "<<boardPieces.at(14)<<" | "<<boardPieces.at(15)<<"   "<<boardPieces.at(16)<<"   "<<boardPieces.at(17)<<" | C\n"
        <<"  |-----------+-----------|\n"
        <<"D | "<<boardPieces.at(18)<<"   "<<boardPieces.at(19)<<"   "<<boardPieces.at(20)<<" | "<<boardPieces.at(21)<<"   "<<boardPieces.at(22)<<"   "<<boardPieces.at(23)<<" | D\n"
        <<"  |           |           |\n"
        <<"E | "<<boardPieces.at(24)<<"   "<<boardPieces.at(25)<<"   "<<boardPieces.at(26)<<" | "<<boardPieces.at(27)<<"   "<<boardPieces.at(28)<<"   "<<boardPieces.at(29)<<" | E\n"
        <<"  |           |           |\n"
        <<"F | "<<boardPieces.at(30)<<"   "<<boardPieces.at(31)<<"   "<<boardPieces.at(32)<<" | "<<boardPieces.at(33)<<"   "<<boardPieces.at(34)<<"   "<<boardPieces.at(35)<<" | F\n"
        <<"  3-----------------------4\n"
        <<"    1   2   3   4   5   6 \n";
}

// function that displays win messages.
void Pentago::displayWin(int playersWon, char playerWonChar){
    if(playersWon==1){ // if one player has won.
            if(playerWonChar=='O'){
                cout<<"    *** O has won the game!"<<endl;
                displayBoard();
            }
            else if(playerWonChar=='X'){   
                cout<<"    *** X has won the game!" <<endl;                
                displayBoard();
            }
        }
        else if(playersWon==2){ // if two players won.
            cout<<"   *** Both X and O have won.  Game is a tie."<<endl;
            displayBoard();
        }
}

// function to assign number of players won.
void Pentago::numberOfPlayersWon(int& playersWon, char& playerWonChar, int index){
    if(playersWon==0){ // if until now, no player has won.
        playersWon=1;
        playerWonChar=boardPieces.at(index);
    }
    else if(playersWon==1 && playerWonChar!=boardPieces.at(index)) // if a player aleady has winning condition and the second one has too.
        playersWon=2;
}

// checks for winning conditions.
int Pentago::checkForWin(int& playersWon, char& playerWonChar){
    for(int i=0; i<12; ++i){ // checking columns.
        if( boardPieces.at(i)!='.' &&
            boardPieces.at(i)==boardPieces.at(i+6) &&
            boardPieces.at(i)==boardPieces.at(i+18) &&
            boardPieces.at(i)==boardPieces.at(i+12) &&
            boardPieces.at(i)==boardPieces.at(i+24)){
               numberOfPlayersWon(playersWon, playerWonChar, i);
               if(playersWon==2)
                   return playersWon;
           }
    }
    for(int i=0; i<31 ; i+=6){ // checking rows.
        for(int j=0; j<2; ++j){
            if( boardPieces.at(i+j)!='.' &&
                boardPieces.at(i+j)==boardPieces.at(i+1+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+2+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+3+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+4+j)){
                numberOfPlayersWon(playersWon, playerWonChar, i+j);
                if(playersWon==2)
                    return playersWon;
            }
        }
    }
    for(int i=0; i<2; ++i){ // checking diagonals.
        for(int j=4; j<11; j+=6){// left diagonals.
            if( boardPieces.at(i+j)!='.' &&
                boardPieces.at(i+j)==boardPieces.at(i+j+5) &&
                boardPieces.at(i+j)==boardPieces.at(i+j+10) &&
                boardPieces.at(i+j)==boardPieces.at(i+j+15) &&
                boardPieces.at(i+j)==boardPieces.at(i+j+20)){
                    numberOfPlayersWon(playersWon, playerWonChar, i+j);
                    if(playersWon==2)
                        return playersWon;
            }
        }
        for(int j=0; j<7 && boardPieces.at(i+j)!='.'; j+=6){// right diagonals.
            if( boardPieces.at(i+j)!='.' &&
                boardPieces.at(i+j)==boardPieces.at(i+7+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+14+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+21+j) &&
                boardPieces.at(i+j)==boardPieces.at(i+28+j)){
                    numberOfPlayersWon(playersWon, playerWonChar, i+j);
                    if(playersWon==2)
                        return playersWon;
            }
        }
    }
    return playersWon;
}

// function that swaps board pieces.
void Pentago::swapPieces(int firstIndex, int secondIndex){
    char temp;
    temp=boardPieces.at(firstIndex);
    boardPieces.at(firstIndex)=boardPieces.at(secondIndex);
    boardPieces.at(secondIndex)=temp;
}

// function for maing moves in the board and displaying win.
void Pentago::makeMove(char rowInt, char columnInt, char quadrantInt, char direction, char playerSymbol, int& win){
    int playersWon=0;
    char playerWonChar;

    boardPieces.at((rowInt*6)+columnInt-1)=playerSymbol; // making the move.

    checkForWin(playersWon, playerWonChar); // checking for a win.
    if(!playersWon) // if a winning isn't condition is met.
        rotateQuadrant(quadrantInt, direction); // rotating if no wining condition.
    else { // if a winning conditon is met before rotating.
        win=1;
        displayWin(playersWon, playerWonChar);        
    }

    checkForWin(playersWon, playerWonChar); // checking for a win again after rotation.
    if(playersWon){ // if there is a winning conditon.
        win=1;
        displayWin(playersWon, playerWonChar);
    }
}

// function for rotating a quadrant.
void Pentago::rotateQuadrant(int quadrantInt, char direction){
    int swapVariable;

    // assigning the swap variable according to the quadrant.
    if(quadrantInt==1) // first quadrant.
        swapVariable=0;
    else if(quadrantInt==2) // second quadrant.
        swapVariable=3;
    else if(quadrantInt==3) // third quadrant.
        swapVariable=18;
    else if(quadrantInt==4) // fourth quadrant.
        swapVariable=21;

    if(direction=='R'){ // to rotate right.
        swapPieces(0+swapVariable, 2+swapVariable);
        swapPieces(0+swapVariable, 14+swapVariable);
        swapPieces(0+swapVariable, 12+swapVariable);
        swapPieces(1+swapVariable, 8+swapVariable);
        swapPieces(1+swapVariable, 13+swapVariable);
        swapPieces(1+swapVariable, 6+swapVariable);
    }
    else{ // to rotate left.
        swapPieces(1+swapVariable, 6+swapVariable);
        swapPieces(1+swapVariable, 13+swapVariable);
        swapPieces(1+swapVariable, 8+swapVariable);
        swapPieces(0+swapVariable, 12+swapVariable);
        swapPieces(0+swapVariable, 14+swapVariable);
        swapPieces(0+swapVariable, 2+swapVariable);
    }
}

// function for checking input correctness.
bool Pentago::checkInput(char rowInt, char columnInt, char quadrantInt, char direction){
    if(rowInt>5 || rowInt<0){
        cout<<"    *** Invalid move row.  Please retry."<<endl;
        return false;
    }
    else if(columnInt>6 || columnInt<1){
        cout<<"    *** Invalid move column.  Please retry."<<endl;
        return false;
    }
    else if(boardPieces.at((rowInt*6)+columnInt-1)!='.'){
        cout<<"    *** That board location is already taken.  Please retry."<<endl;
        return false;
    }
    else if(quadrantInt>4 || quadrantInt<1){
        cout<< "    *** Selected quadrant is invalid.  Please retry. "<<endl;
        return false;
    }
    else if(direction!='R' && direction!='L'){
        cout<< "    *** Quadrant rotation direction is invalid.  Please retry. "<<endl;
        return false;
    }
    return true;
}

// function that takes input.
void takeInput(int numberOfIteration, char& row, char& column, char& quadrant, char& direction, char playerSymbol, Pentago theBoard) {
    cout<<numberOfIteration<<". Enter row, column, quadrant, direction for "<<playerSymbol<<": ";
    cin>>row;
    if(toupper(row)=='X'){ // checking if player wants to exit.
        cout<<"Exiting program...";
        exit(0);
    }
    else if(toupper(row)=='I'){ // checking if player wants instructions.
        displayInstructions();
        cout<<endl;
    }
    else{
        cin>>column>>quadrant>>direction;
        cout<<endl;
        row=toupper(row);
        direction=toupper(direction);
    }
}

// function that changes player symbols for turns.
void changePlayerSymbol(char& playerSymbol, int& numberOfIteration){
    if(playerSymbol == 'X')
        playerSymbol = 'O';
    else
        playerSymbol = 'X';

    numberOfIteration++;
}

// function that prints messages if no one has won.
void checkForTie(Pentago theBoard, int numberOfIteration){
    if(numberOfIteration==37){
        cout<<"    *** No one has won.  Game is a tie."<<endl;
        theBoard.displayBoard();
    }
}

// the main.
int main(){
    //declaring the variables.
    int numberOfIteration=1; // iteration counter for playing.
    int columnInt, quadrantInt, rowInt;
    int win=0;
    char row, column, quadrant, direction;
    char playerSymbol = 'X';
    Pentago theBoard; // our game board.

    //displaying the first message.
    cout<<"Welcome to Pentago, where you try to get 5 of your pieces in a line.\n"
        <<"At any point enter 'x' to exit or 'i' for instructions.\n\n";

    while(numberOfIteration<=36){
        theBoard.displayBoard(); // displaying the board.
        takeInput(numberOfIteration, row, column, quadrant, direction, playerSymbol, theBoard); // taking input.
        columnInt = column - '0'; // assigning the column int.
        quadrantInt = quadrant - '0';// assigning the quadrant int.
        rowInt = row-'A'; // assigning the row int.

        if(toupper(row)!='I' && theBoard.checkInput(rowInt, columnInt, quadrantInt, direction)){ // if inputs are right. 
            theBoard.makeMove(rowInt, columnInt, quadrantInt, direction, playerSymbol, win); // making the move.
            if(win>0) // if win conditons met.
                break; // exiting out of the main loop.
            changePlayerSymbol(playerSymbol, numberOfIteration);// changing the player symbol.
        }
    }
    checkForTie(theBoard, numberOfIteration); // checking for a no win tie.

    cout << "Thanks for playing.  Exiting... " << endl; // displaying final message.
    exit(0); // exiting.
    return 0; // just for C++'s happiness.
}