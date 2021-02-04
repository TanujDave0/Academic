//Name:Tanuj Rakesh Dave
//UIN:665028452
//CS141 Class 12pm Sean Deitz

#include <iostream>
#include <iomanip>
using namespace std;

/*
Hello!!
my orignal ASCII art :-

+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
              |||||||||||||||||||||||||
           ||||||||||||||||||||||||||||||
         |||||||---------------------\|||||
       ||||||/                          \||||
     ||||||/                              \||||
    |||||/                                 \||||
   |||||/                                   \||||
 ||||||                                      \||||
||||||                 ||||                    \|||
|||||                  ||||                    |||||
||||       /|||||||  |||||||||    |||||||||    |||||
||||     /|||||||||  |||||||||    |||||||||    |||||
||||    /||||/-----    ||||            ||||    |||||
||||    |||||          ||||      /=====||||    |||||
||||    \||||\  __     ||||\__  ||=====||||    |||||
||||     \|||||||||    |||||||  ||    /||||    |||||
||||\      \|||||||    |||||||  ||===/ |||| ®  |||||
 ||||\                                       /||||
  ||||\                                     /||||
   ||||\                                   /||||
    |||||\                               /|||||
     ||||||\                            /|||||
       |||||||\_______________________/|||||
          ||||||||||||||||||||||||||||||||
           |||||||||||||||||||||||||||||
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
*/

int main()
{
    int menuOption = 0;
    int numSec = 0;

    //displaying menu and asking for user's choice.
    
    cout << "Choose from among the following options:  \n"
         << "1. Display original graphic  \n"
         << "2. Display building          \n"
         << "3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    cout <<endl;

    if(menuOption == 3){
        exit( 0); //exits the program.
    }

    else if(menuOption == 1){
        
        //prints CTA ASCII art.

        for(int i=1; i<=17; i++){
            cout<<"+--"; //prints upper border for art.
        }
        cout<<endl;

        cout<<"              |||||||||||||||||||||||||\n"
            <<"           ||||||||||||||||||||||||||||||\n"
            <<"         |||||||---------------------\\|||||\n"
            <<"       ||||||/                          \\||||\n"
            <<"     ||||||/                              \\||||\n"
            <<"    |||||/                                 \\||||\n"
            <<"   |||||/                                   \\||||\n"
            <<" ||||||                                      \\||||\n"
            <<"||||||                 ||||                    \\|||\n"
            <<"|||||                  ||||                    |||||\n"
            <<"||||       /|||||||  |||||||||    |||||||||    |||||\n"
            <<"||||     /|||||||||  |||||||||    |||||||||    |||||\n"
            <<"||||    /||||/-----    ||||            ||||    |||||\n"
            <<"||||    |||||          ||||      /=====||||    |||||\n"
            <<"||||    \\||||\\  __     ||||\\__  ||=====||||    |||||\n"
            <<"||||     \\|||||||||    |||||||  ||    /||||    |||||\n"
            <<"||||\\      \\|||||||    |||||||  ||===/ |||| ®  |||||\n"
            <<" ||||\\                                       /||||\n"
            <<"  ||||\\                                     /||||\n"
            <<"   ||||\\                                   /||||\n"
            <<"    |||||\\                               /|||||\n"
            <<"     ||||||\\                            /|||||\n"
            <<"       |||||||\\_______________________/|||||\n"
            <<"          ||||||||||||||||||||||||||||||||\n"
             <<"           |||||||||||||||||||||||||||||\n";

        for(int i=1; i<=17;i++){
            cout<<"+--"; //prints lower border. 
        }
        cout<<endl;
    }

    else if( menuOption==2){

        //asks for number of sections user wants in building.

        cout<<"Number of building sections -> ";
        cin>>numSec;
        cout<<endl;
        
        //pritning the building, first it's uppermost part.
        
        if(numSec>=0){
            cout<<setw(numSec+1)<<" " <<" /\\\n"
                <<setw(numSec+1)<<" " <<" ||\n"
                <<setw(numSec+1)<<" " <<" ||\n"
                <<setw(numSec+1)<<" " <<" --\n"
                <<setw(numSec+1)<<" " <<"|++|\n"
                <<setw(numSec+1)<<" " <<"====\n";
        
            //creating a for loop that would print each section of building.

            for( int i=1; i<=numSec; i++){

                //another two for loops that would print the upper and lower halves of the each section.

                for(int j=1; j<=i; j++){
                    cout<<setfill(' ') <<setw(numSec-i+2)<<""<<"|";
                    cout<<setfill(':')<<setw(j-1)<<""<<"\\"<<setw((i-j)*2)<<""<<"/"<<setw(j-1)<<""<<"|\n";
                }
                for(int j=i; j>=1; j--){
                    cout<<setfill(' ')<<setw(numSec-i+2)<<""<<"|";
                    cout<<setw(j-1)<<setfill(':')<<""<<'/'<<setw((i-j)*2)<<""<<"\\"<<setw(j-1)<<""<<"|\n";
                }

                //printing the connecting section between building sections.

                cout<<setfill(' ')<<setw(numSec-i+2)<<""<<setfill('-') <<"/"<<setw((i*2)+2)<<"\\\n";
            }

            //printing the base of the building.

            cout<<" "<<setfill('.')<<setw((2*numSec)+5)<<"\n";
            cout<<setfill('+')<<setw((2*numSec)+7)<<"\n";
            cout<<endl;
        }
    }
    return 0;
}