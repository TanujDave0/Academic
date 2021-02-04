#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "island.h"
#include "list.h"

using namespace std;

class ArchipelagoExpedition {
private:
    // Create the Data Members for the Archipelago Network here
    myList<string> files;
    island* islands;
    int Size;

    void depthFirstSearchHelper(int x , int y) {
        //mark all islands as unvisited;
        for (int i = 0; i < Size; i++) {
            islands[i].changeVisit(false);
        }
        if (dfs(x , y)) {
            cout << "You can get from island " << x + 1<< " to island " << y << " in one or more ferry rides" << endl;
        } else {
            cout << "You can NOT get from island " << x + 1 << " to island " << y << " in one or more ferry rides" << endl;
        }
    }

    bool dfs(int a , int b) {
        for (int i = 0; i < islands[a].ferriesOut(); i++) {
            int c = islands[a].getNth(i);
            if (c == b){
                return true;
            }
            if (c == int{}) {
                return false;
            }
            if (!islands[c - 1].visited()) {
                // mark island c as visited;
                islands[c - 1].changeVisit(true);
                if (dfs(c - 1 , b))
                    return true;
            }
        }
        return false;
    }

public:
    // Use a constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition() {
        islands = new island[10];
        Size = 10;
    }

    // The main loop for reading in input
    void processCommandLoop(FILE* inFile) {
        char  buffer[300];
        char* input;

        input = fgets(buffer , 300 , inFile);   // get a line of input

        // loop until all lines are read from the input
        while (input != NULL) {
            // process each line of input using the strtok functions 
            char* command;
            command = strtok(input , " \n\t");

            printf("*%s*\n" , command);

            if (command == NULL)
                printf("Blank Line\n");
            else if (strcmp(command , "q") == 0)
                exit(1);
            else if (strcmp(command , "?") == 0)
                showCommands();
            else if (strcmp(command , "t") == 0)
                doTravel();
            else if (strcmp(command , "r") == 0)
                doResize();
            else if (strcmp(command , "i") == 0)
                doInsert();
            else if (strcmp(command , "d") == 0)
                doDelete();
            else if (strcmp(command , "l") == 0)
                doList();
            else if (strcmp(command , "f") == 0)
                doFile();
            else if (strcmp(command , "#") == 0)
                ;
            else
                printf("Command is not known: %s\n" , command);

            input = fgets(buffer , 300 , inFile);   // get the next line of input

        }
    }

    void showCommands() {
        printf("The commands for this project are:\n");
        printf("  q \n");
        printf("  ? \n");
        printf("  # \n");
        printf("  t <int1> <int2> \n");
        printf("  r <int> \n");
        printf("  i <int1> <int2> \n");
        printf("  d <int1> <int2> \n");
        printf("  l \n");
        printf("  f <filename> \n");
    }

    void doTravel() {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL , " \n\t");
        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL , " \n\t");

        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the Travel Command from %d to %d\n" ,
            val1 , val2);
        
        depthFirstSearchHelper(val1 - 1, val2);
    }

    void doResize() {
        int val1 = 0;

        // get an integer value from the input
        char* next = strtok(NULL , " \n\t");
        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        printf("Performing the Resize Command with %d\n" , val1);

        for (int i = 0; i < Size; i++) {
            islands[i].clear();
        }
        delete[] islands;

        islands = new island[val1];
        Size = val1;
    }

    void doInsert() {
        int val1, val2;
        // get an integer value from the input
        char* next = strtok(NULL , " \n\t");
        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL , " \n\t");

        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf ("Performing the Insert Command for %d\n", val1);
        islands[val1 - 1].insertNode(val2);
    }

    void doDelete() {
        int val1, val2;
        // get an integer value from the input
        char* next = strtok(NULL , " \n\t");
        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL , " \n\t");

        // printf("%s\n" , next);
        if (next == NULL) {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next , "0") != 0) {
            printf("Integer value expected\n");
            return;
        }

        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf ("Performing the Delete Command for %d\n", val1);

        islands[val1 - 1].deleteNode(val2);
    }

    void doList() {
        printf ("Displaying the adjacency list:\n");
        for (int i = 0; i < Size; i++) {
            cout << i + 1;
            islands[i].printList();
        }
    }

    void doFile() {
        // get a filename from the input
        char* fname = strtok(NULL , " \r\n\t");
        string fileName(fname);
        if (fname == NULL) {
            printf("Filename expected\n");
            return;
        }
        
        printf("Performing the File command with file: %s\n" , fname);

        if (files.exists(fileName)) {
            cout << "File is already in use\n";
            return;
        }

        files.insertNode(fileName);

        FILE* file = fopen(fname, "r");
        if (file == nullptr) {
            cout << "Cannot open the file\n";
            return;
        }

        // next steps:  (if any step fails: print an error message and return ) 
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns

        processCommandLoop(file);
        fclose(file);
    }
};

int main(int argc , char** argv) {
    // set up the variable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf("\nEnter commands at blank line\n");
    printf("    (No prompts are given because of f command)\n");
    islandData.processCommandLoop(inFile);

    printf("Goodbye\n");
    return 1;
}
