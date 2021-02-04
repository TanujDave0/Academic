#include <iostream>
#include <cctype>
#include <iomanip>
using namespace std;

char p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16; //creating global variables for pieces in board.
string upperRowPiecesToPlay = "OO/CC  II/ZZ"; //creating global variables for pieces to play.
string lowerRowPiecesToPlay = "oo/cc  ii/zz"; //creating global variables for pieces to play.

bool vowelCheck(char aChar){
    //function for checking if char is vowel.
    int i = false;
    string c = "OI";
    for(int j=0; j<2; j++){
        if(toupper(aChar)==c.at(j)){
            i=true;
        }
    }
    return i;
}

bool consonantCheck(char aChar){
    //function for checking if char is consonant.
    int i = false;
    string c = "CZ";
    for(int j=0; j<2; j++){
        if(toupper(aChar)==c.at(j)){
            i=true;
        }
    }
    return i;
}

bool curvedCheck(char aChar){
    //function for checking if char is curved.
    int i = false;
    string c = "OC";
    for(int j=0; j<2; j++){
        if(toupper(aChar)==c.at(j)){
            i=true;
        }
    }
    return i;
}

bool straightCheck(char aChar){
    //function for checking if char is straight.
    int i = false;
    string c = "IZ";
    for(int j=0; j<2; j++){
        if(toupper(aChar)==c.at(j)){
            i=true;
        }
    }
    return i;
}

bool upperCheck(char aChar){
    //function for checking if char is upper.
    int i = false;
    string c = "OCIZ";
    for(int j=0; j<4; j++){
        if(aChar==c.at(j)){
            i=true;
        }
    }
    return i;
}

bool lowerCheck(char aChar){
    //function for checking if char is lower.
    int i = false;
    string c = "ociz";
    for(int j=0; j<4; j++){
        if(aChar==c.at(j)){
            i=true;
        }
    }
    return i;
}

//function checkBoardVowel checks board for winning conditions containing vowels.
bool checkBoardVowel(){
    int win=false;
    //for row
    if( vowelCheck(p1) && vowelCheck(p2) && vowelCheck(p3) && vowelCheck(p4)){
            win=true;
        }
    else if( vowelCheck(p5) && vowelCheck(p6) && vowelCheck(p7) && vowelCheck(p8)){
            win=true;
        }
    else if( vowelCheck(p9) && vowelCheck(p10) && vowelCheck(p11) && vowelCheck(p12) ){
            win=true;
        }
    else if( vowelCheck(p13) && vowelCheck(p14) && vowelCheck(p15) && vowelCheck(p16) ){
            win=true;
        }
    //for column
    else if( vowelCheck(p1) && vowelCheck(p5) && vowelCheck(p9) && vowelCheck(p13) ){
            win=true;
        }
    else if( vowelCheck(p2) && vowelCheck(p6) && vowelCheck(p10) && vowelCheck(p14) ){
            win=true;
        }
    else if( vowelCheck(p3) && vowelCheck(p7) && vowelCheck(p11) && vowelCheck(p15) ){
            win=true;
        }
    else if( vowelCheck(p4) && vowelCheck(p8) && vowelCheck(p12) && vowelCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( vowelCheck(p1) && vowelCheck(p6) && vowelCheck(p11) && vowelCheck(p16) ){

            win=true;
        }
    else if( vowelCheck(p4) && vowelCheck(p7) && vowelCheck(p10) && vowelCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( vowelCheck(p1) && vowelCheck(p2) && vowelCheck(p5) && vowelCheck(p6) ){
            win=true;
        }
    else if( vowelCheck(p3) && vowelCheck(p4) && vowelCheck(p7) && vowelCheck(p8) ){
            win=true;
        }
    else if( vowelCheck(p9) && vowelCheck(p10) && vowelCheck(p13) && vowelCheck(p14) ){
            win=true;
        }
    else if( vowelCheck(p11) && vowelCheck(p12) && vowelCheck(p15) && vowelCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions containing consonants.
bool checkBoardConsonant(){
    int win=false;
    //for row
    if( consonantCheck(p1) && consonantCheck(p2) && consonantCheck(p3) && consonantCheck(p4)){
            win=true;
        }
    else if( consonantCheck(p5) && consonantCheck(p6) && consonantCheck(p7) && consonantCheck(p8) ){
            win=true;
        }
    else if( consonantCheck(p9) && consonantCheck(p10) && consonantCheck(p11) && consonantCheck(p12) ){
            win=true;
        }
    else if( consonantCheck(p13) && consonantCheck(p14) && consonantCheck(p15) && consonantCheck(p16) ){
            win=true;
        }
    //for column
    else if( consonantCheck(p1) && consonantCheck(p5) && consonantCheck(p9) && consonantCheck(p13) ){
            win=true;
        }
    else if( consonantCheck(p2) && consonantCheck(p6) && consonantCheck(p10) && consonantCheck(p14) ){
            win=true;
        }
    else if( consonantCheck(p3) && consonantCheck(p7) && consonantCheck(p11) && consonantCheck(p15) ){
            win=true;
        }
    else if( consonantCheck(p4) && consonantCheck(p8) && consonantCheck(p12) && consonantCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( consonantCheck(p1) && consonantCheck(p6) && consonantCheck(p11) && consonantCheck(p16) ){
            win=true;
        }
    else if( consonantCheck(p4) && consonantCheck(p7) && consonantCheck(p10) && consonantCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( consonantCheck(p1) && consonantCheck(p2) && consonantCheck(p5) && consonantCheck(p6) ){
            win=true;
        }
    else if( consonantCheck(p3) && consonantCheck(p4) && consonantCheck(p7) && consonantCheck(p8) ){
            win=true;
        }
    else if( consonantCheck(p9) && consonantCheck(p10) && consonantCheck(p13) && consonantCheck(p14) ){
            win=true;
        }
    else if( consonantCheck(p11) && consonantCheck(p12) && consonantCheck(p15) && consonantCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions containing Curved.
bool checkBoardCurved(){
    int win=false;
    //for row
    if( curvedCheck(p1) && curvedCheck(p2) && curvedCheck(p3) && curvedCheck(p4)){
            win=true;
        }
    else if( curvedCheck(p5) && curvedCheck(p6) && curvedCheck(p7) && curvedCheck(p8) ){
            win=true;
        }
    else if( curvedCheck(p9) && curvedCheck(p10) && curvedCheck(p11) && curvedCheck(p12) ){
            win=true;
        }
    else if( curvedCheck(p13) && curvedCheck(p14) && curvedCheck(p15) && curvedCheck(p16) ){
            win=true;
        }
    //for column
    else if( curvedCheck(p1) && curvedCheck(p5) && curvedCheck(p9) && curvedCheck(p13) ){
            win=true;
        }
    else if( curvedCheck(p2) && curvedCheck(p6) && curvedCheck(p10) && curvedCheck(p14) ){
            win=true;
        }
    else if( curvedCheck(p3) && curvedCheck(p7) && curvedCheck(p11) && curvedCheck(p15) ){
            win=true;
        }
    else if( curvedCheck(p4) && curvedCheck(p8) && curvedCheck(p12) &&curvedCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( curvedCheck(p1) && curvedCheck(p6) && curvedCheck(p11) && curvedCheck(p16) ){
            win=true;
        }
    else if( curvedCheck(p4) && curvedCheck(p7) && curvedCheck(p10) && curvedCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( curvedCheck(p1) && curvedCheck(p2) && curvedCheck(p5) && curvedCheck(p6) ){
            win=true;
        }
    else if( curvedCheck(p3) && curvedCheck(p4) && curvedCheck(p7) && curvedCheck(p8) ){
            win=true;
        }
    else if( curvedCheck(p9) && curvedCheck(p10) && curvedCheck(p13) && curvedCheck(p14) ){
            win=true;
        }
    else if( curvedCheck(p11) && curvedCheck(p12) && curvedCheck(p15) && curvedCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions containing Straight.
bool checkBoardStraight(){
    int win=false;
    //for row
    if( straightCheck(p1) && straightCheck(p2) && straightCheck(p3) && straightCheck(p4)    ){
            win=true;
        }
    else if( straightCheck(p5) && straightCheck(p6) && straightCheck(p7) && straightCheck(p8) ){
            win=true;
        }
    else if( straightCheck(p9) && straightCheck(p10) && straightCheck(p11) && straightCheck(p12) ){
            win=true;
        }
    else if( straightCheck(p13) && straightCheck(p14) && straightCheck(p15) && straightCheck(p16) ){
            win=true;
        }
    //for column
    else if( straightCheck(p1) && straightCheck(p5) && straightCheck(p9) && straightCheck(p13) ){
            win=true;
        }
    else if( straightCheck(p2) && straightCheck(p6) && straightCheck(p10) && straightCheck(p14) ){
            win=true;
        }
    else if( straightCheck(p3) && straightCheck(p7) && straightCheck(p11) && straightCheck(p15) ){
            win=true;
        }
    else if( straightCheck(p4) && straightCheck(p8) && straightCheck(p12) && straightCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( straightCheck(p1) && straightCheck(p6) && straightCheck(p11) && straightCheck(p16) ){
            win=true;
        }
    else if( straightCheck(p4) && straightCheck(p7) && straightCheck(p10) && straightCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( straightCheck(p1) && straightCheck(p2) && straightCheck(p5) && straightCheck(p6) ){
            win=true;
        }
    else if( straightCheck(p3) && straightCheck(p4) && straightCheck(p7) && straightCheck(p8) ){
            win=true;
        }
    else if( straightCheck(p9) && straightCheck(p10) && straightCheck(p13) && straightCheck(p14) ){
            win=true;
        }
    else if( straightCheck(p11) && straightCheck(p12) && straightCheck(p15) && straightCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions containing upper.
bool checkBoardUpper(){
    int win=false;
    //for row
    if( upperCheck(p1) && upperCheck(p2) && upperCheck(p3) && upperCheck(p4)    ){
            win=true;
        }
    else if( upperCheck(p5) && upperCheck(p6) && upperCheck(p7) && upperCheck(p8) ){
            win=true;
        }
    else if( upperCheck(p9) && upperCheck(p10) && upperCheck(p11) && upperCheck(p12) ){
            win=true;
        }
    else if( upperCheck(p13) && upperCheck(p14) && upperCheck(p15) && upperCheck(p16) ){
            win=true;
        }
    //for column
    else if( upperCheck(p1) && upperCheck(p5) && upperCheck(p9) && upperCheck(p13) ){
            win=true;
        }
    else if( upperCheck(p2) && upperCheck(p6) && upperCheck(p10) && upperCheck(p14) ){
            win=true;
        }
    else if( upperCheck(p3) && upperCheck(p7) && upperCheck(p11) && upperCheck(p15) ){
            win=true;
        }
    else if( upperCheck(p4) && upperCheck(p8) && upperCheck(p12) && upperCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( upperCheck(p1) && upperCheck(p6) && upperCheck(p11) && upperCheck(p16) ){
            win=true;
        }
    else if( upperCheck(p4) && upperCheck(p7) && upperCheck(p10) && upperCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( upperCheck(p1) && upperCheck(p2) && upperCheck(p5) && upperCheck(p6) ){
            win=true;
        }
    else if( upperCheck(p3) && upperCheck(p4) && upperCheck(p7) && upperCheck(p8) ){
            win=true;
        }
    else if( upperCheck(p9) && upperCheck(p10) && upperCheck(p13) && upperCheck(p14) ){
            win=true;
        }
    else if( upperCheck(p11) && upperCheck(p12) && upperCheck(p15) && upperCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions containing lower.
bool checkBoardLower(){
    int win=false;

    //for row
    if( lowerCheck(p1) && lowerCheck(p2) && lowerCheck(p3) && lowerCheck(p4)    ){
            win=true;
        }
    else if( lowerCheck(p5) && lowerCheck(p6) && lowerCheck(p7) && lowerCheck(p8) ){
            win=true;
        }
    else if( lowerCheck(p9) && lowerCheck(p10) && lowerCheck(p11) && lowerCheck(p12) ){
            win=true;
        }
    else if( lowerCheck(p13) && lowerCheck(p14) && lowerCheck(p15) && lowerCheck(p16) ){
            win=true;
        }
    //for column
    else if( lowerCheck(p1) && lowerCheck(p5) && lowerCheck(p9) && lowerCheck(p13) ){
            win=true;
        }
    else if( lowerCheck(p2) && lowerCheck(p6) && lowerCheck(p10) && lowerCheck(p14) ){
            win=true;
        }
    else if( lowerCheck(p3) && lowerCheck(p7) && lowerCheck(p11) && lowerCheck(p15) ){
            win=true;
        }
    else if( lowerCheck(p4) && lowerCheck(p8) && lowerCheck(p12) && lowerCheck(p16) ){
            win=true;
        }
    //for diagonals
    else if( lowerCheck(p1) && lowerCheck(p6) && lowerCheck(p11) && lowerCheck(p16) ){
            win=true;
        }
    else if( lowerCheck(p4) && lowerCheck(p7) && lowerCheck(p10) && lowerCheck(p13) ){
            win=true;
        }
    //for coner quadrant
    else if( lowerCheck(p1) && lowerCheck(p2) && lowerCheck(p5) && lowerCheck(p6) ){
            win=true;
        }
    else if( lowerCheck(p3) && lowerCheck(p4) && lowerCheck(p7) && lowerCheck(p8) ){
            win=true;
        }
    else if( lowerCheck(p9) && lowerCheck(p10) && lowerCheck(p13) && lowerCheck(p14) ){
            win=true;
        }
    else if( lowerCheck(p11) && lowerCheck(p12) && lowerCheck(p15) && lowerCheck(p16) ){
            win=true;
        }
    return win;
}

//function for checking board for winning conditions.
bool checkBoard(){
    int win = false;
    if(checkBoardVowel() || checkBoardConsonant() || checkBoardStraight() || checkBoardCurved() || checkBoardUpper() || checkBoardLower()){
            win=true;
        }
    return win;
}

//function for displaying Board.
void dispBoard(){
    cout<<"      ---------    Square #\n"
        <<"     |"<<setw(2)<<p1<<setw(2)<<p2<<setw(2)<<p3<<setw(2)<<p4<<" |  1  2  3  4\n"
        <<"     |"<<setw(2)<<p5<<setw(2)<<p6<<setw(2)<<p7<<setw(2)<<p8<<" |  5  6  7  8\n"
        <<"     |"<<setw(2)<<p9<<setw(2)<<p10<<setw(2)<<p11<<setw(2)<<p12<<" |  9 10 11 12\n"
        <<"     |"<<setw(2)<<p13<<setw(2)<<p14<<setw(2)<<p15<<setw(2)<<p16<<" | 13 14 15 16\n"
        <<"      ---------\n"
        <<"     Pieces:     Curved Straight\n"                
        <<"           Upper: "<<upperRowPiecesToPlay<<"\n"
        <<"           Lower: "<<lowerRowPiecesToPlay<<"\n"
        <<"                 Vowel/Consonant\n";
}

//function for cheching validity of int entered.
void checkInt(int position, int& valInt){
    if(position<=16 && position>0){
        if(position==1 && p1=='.'){
            valInt=1; // if valInt is 1 then it's valid.
        }
        if(position==2 && p2=='.'){
            valInt=1;
        }
        if(position==3 && p3=='.'){
             valInt=1;
        }
        if(position==4 && p4=='.'){
            valInt=1;
        }
        if(position==5 && p5=='.'){
            valInt=1;
        }
        if(position==6 && p6=='.'){
            valInt=1;
        }
        if(position==7 && p7=='.'){
            valInt=1;
        }
        if(position==8 && p8=='.'){
            valInt=1;
        }
        if(position==9 && p9=='.'){
            valInt=1;
        }
        if(position==10 && p10=='.'){
            valInt=1;
        }
        if(position==11 && p11=='.'){
            valInt=1;
        }
        if(position==12 && p12=='.'){
            valInt=1;
        }
        if(position==13 && p13=='.'){
            valInt=1;
        }
        if(position==14 && p14=='.'){
            valInt=1;
        }
        if(position==15 && p15=='.'){
            valInt=1;
        }
        if(position==16 && p16=='.'){
            valInt=1;
        }
    }
    else{
        valInt=0;
    }
}

//function for making moves in the board.
void makeMove(int position, char playerEnteredChar){
    if(position<=16 && position>0){
        if(position==1 && p1=='.'){
            p1=playerEnteredChar; //assigning position to player entered character.
        }
        if(position==2 && p2=='.'){
            p2=playerEnteredChar;
        }
        if(position==3 && p3=='.'){
            p3=playerEnteredChar;
        }
        if(position==4 && p4=='.'){
            p4=playerEnteredChar;
        }
        if(position==5 && p5=='.'){
            p5=playerEnteredChar;
        }
        if(position==6 && p6=='.'){
            p6=playerEnteredChar;
        }
        if(position==7 && p7=='.'){
            p7=playerEnteredChar;
        }
        if(position==8 && p8=='.'){
            p8=playerEnteredChar;
        }
        if(position==9 && p9=='.'){
            p9=playerEnteredChar;
        }
        if(position==10 && p10=='.'){
            p10=playerEnteredChar;
        }
        if(position==11 && p11=='.'){
            p11=playerEnteredChar;
        }
        if(position==12 && p12=='.'){
            p12=playerEnteredChar;
        }
        if(position==13 && p13=='.'){
            p13=playerEnteredChar;
        }
        if(position==14 && p14=='.'){
            p14=playerEnteredChar;
        }
        if(position==15 && p15=='.'){
            p15=playerEnteredChar;
        }
        if(position==16 && p16=='.'){
            p16=playerEnteredChar;
        }
    }
}

// function that checks validity of character entered.
void validityChar(int& valChar, char playerEnteredChar, int valInt){

    for(int i=0; i<upperRowPiecesToPlay.length();i++){
            //if its in upperRowPiecesToPlay assigns valChar to 1.
            if((upperRowPiecesToPlay.at(i) == playerEnteredChar) && valInt == 1) {
                valChar=1;
                upperRowPiecesToPlay.replace(i,1, " ");
                break;
            }
            //if its in lowerRowPiecesToPlay assigns valChar to 1.
            else if(lowerRowPiecesToPlay.at(i) == playerEnteredChar && valInt ==1){             
                valChar = 1;
                lowerRowPiecesToPlay.replace(i,1," ") ;
                break;
            }
            else{
                //if its not valid assigns valChar to 0.
                valChar=0;
            }
        }
}

//displays First Menu.
void dispFirstMenu(){
     cout<<"Welcome to the game of Cuatro, where you try to complete a set\n"
        <<"of four pieces that are alike.  Players take turns making moves.\n"   
        <<"On each move your OPPONENT chooses the piece, then YOU get to\n"       
        <<"place it on the board.  If you create a set of four alike when\n"      
        <<"you place your piece, then you win!\n\n"      
        <<"A set of four alike can be completed by using four all upper (or all\n"
        <<"lower) case characters, four all vowels (or all consonants), or four\n"
        <<"all curved (or all straight-lined). Curved letters are 'O' and 'C'\n"
        <<"(upper or lower), and straight-line letters are 'I' and 'Z' (upper or\n"
        <<"lower). Groups of four can be created in a row, column, diagonal, or\n"
        <<"corner quadrant.\n\n"
        <<"When prompted for input you may also enter 'x' or 'X' to exit.\n";
}

//function checks error in inputs and displays error message.
void errorInput(int valInt, int position, int valChar){
    if(valInt==0){
        //if its invalid position.
        if(position>16 || position<=0){
            cout<<"*** Sorry, that destination is invalid.  Please retry.\n"<<endl;
            dispBoard();
        }
        //if its already occupied.
        else{
            cout<<"*** Sorry, that destination is occupied.  Please retry.\n"<<endl;
            dispBoard();
        }
    }
    //if its invalid character.
    else if(valChar==0){
        cout<<"*** Sorry, that is an invalid piece. Please retry.\n"<<endl;
        dispBoard();
    }
}

//checking for win conditions and displaying messages.
// void winConditionCheck(string playerSecond){
    
// }

void swapPlayerTurn(string& playerFirst, string& playerSecond){
    if(playerFirst=="Player 1"){
        playerFirst="Player 2";
        playerSecond="Player 1";
    }
    else{
        playerFirst="Player 1";
        playerSecond="Player 2";
    }
}

int main(){
    //declaring and initialising variables.
    char playerEnteredChar;
    int valInt=0, valChar =0, moveNumber=1, position=0;
    string playerFirst = "Player 1", playerSecond = "Player 2";
    p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16='.';
    
    // displaying first menu and board.
    dispFirstMenu();
    dispBoard();
    
    //initialising loop for game inputs.
    while(moveNumber<=16){
        cout<<moveNumber<<". "<<playerFirst<<" enter piece, and "<<playerSecond<<" enter destination: ";
        cin>>playerEnteredChar; //taking character input.

        //checking for exit condition.
        if(playerEnteredChar=='x' || playerEnteredChar =='X'){
            cout<<"\nExiting program...";
            exit( 0);
        }
        cin>>position; //taking position input.

        //checking validity of inputs.
        valInt=0;
        checkInt(position, valInt);
        valChar=0;
        validityChar(valChar, playerEnteredChar, valInt);

        //proceeding if valid inputs are entered.
        if(valChar==1 && valInt==1){
            cout<<endl;
            makeMove(position, playerEnteredChar);
            //checking for winning conditions and swapping turns.
            if(checkBoard()){
                dispBoard();
                cout<<endl;
                cout<<"*** "<<playerSecond<<" you won!"<<endl;
                break;
            }
            swapPlayerTurn(playerFirst, playerSecond);
            dispBoard();
            moveNumber++;
        }
        //if invalid inputs are entered displaying error messages.
        else{
            errorInput(valInt, position, valChar);
        }
    }
    return 0;
}