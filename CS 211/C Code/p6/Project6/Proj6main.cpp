#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include "island.h"
#include "list.h"
#include "myStack.h"
#include "myQueue.h"

using namespace std;

class ArchipelagoExpedition {
private:
    // Create the Data Members for the Archipelago Network here
    myList<string> files;  // for storing files
    island* islands;  // pointer to array of islands.
    int Size;  // the size.

    // private so that no user can access these.
    // doing a depth first search, using dfs recursive function.
    void depthFirstSearchHelper(int x , int y) {
        //mark all islands as unvisited;
        for (int i = 0; i < Size; i++) {
            islands[i].changeVisit(false);
        }
        // if there is a route.
        if (dfs(x , y)) {
            cout << "You can get from island " << x + 1 << " to island " << y << " in one or more ferry rides" << endl;
        } else {  // if there is no route.
            cout << "You can NOT get from island " << x + 1 << " to island " << y << " in one or more ferry rides" << endl;
        }
    }

    // depth first search recursive.
    // Finds if there is a route from a to b.
    bool dfs(int a , int b) {
        // for islands that we can visit from a in one ferry ride.
        for (int i = 0; i < islands[a].ferriesOut(); i++) {
            int c = islands[a].getNth(i);  // the island number.
            if (c == b) {  // if we found it.
                return true;
            }
            if (c == int{}) {  // if there is no element left to search.
                return false;
            }
            // if we have not visited c.
            if (!islands[c - 1].visited()) {
                // mark island c as visited;
                islands[c - 1].changeVisit(true);
                if (dfs(c - 1 , b))  // see if we can reach from c to b.
                    return true;  // if possible return true.
            }
        }
        return false;  // if no way to reach from a to b.
    }

    // breadth first search from x+1 to y.
    myStack breadthFirstSearch(int x , int y) {
        // mark all islands as unvisited(set all previousLocation to - 1);
        for (int i = 0; i < Size; i++) {
            islands[i].changeVisit(false);
            islands[i].changePrev(-1);
        }
        // set the list IslandQueue to be empty
        // add x to the end of the IslandQueue
        myQueue IslandQueue;
        IslandQueue.insertNode(x + 1);

        // performing the bfs.
        if (!bfs(y , IslandQueue)) {  // if we didnt find a path.
            cout << "You can NOT get from island " << x + 1 << " to island " << y << endl;
            myStack empty;
            return empty;
        } else {  // if we found a path.
            cout << "You can get from island " << x + 1 << " to island " << y << endl;
            myStack pathList;  // declaring the stack.

            int curr = y;
            pathList.insertNode(curr);
            // adding all the nodes.
            do {
                curr = islands[curr - 1].getPrev();
                pathList.insertNode(curr); // add currentIsland to front of pathList
            } while (curr != x + 1);
            return pathList; // returning the list.
        }
    }

    bool bfs(int b , myQueue &IslandQueue) {
        while (!IslandQueue.isEmpty()) {
            // Set a to be the Island at the front of the IslandQueue
            int a = IslandQueue.getFront();
            // Remove Island at the front of the IslandQueue
            IslandQueue.pop();
            
            for (int i = 0; i < islands[a - 1].ferriesOut(); i++) {
                int c = islands[a - 1].getNth(i);  // the island number.
                if (islands[c - 1].visited()) {  // if the island is already visited.
                    continue;
                }
                // changing the visit status and prev.
                islands[c - 1].changeVisit(true);
                islands[c - 1].changePrev(a);
                if (c == b) {  // if we found it.
                    return true;
                }
                // add c to the end of the IslandQueue
                IslandQueue.insertNode(c);
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
            // command = strtok(input , " \n\t");
            command = strtok(input , " \r\n\t");

            printf("*%s*\n" , command);

            if (command == NULL)
                printf("Blank Line\n");
            else if (strcmp(command , "q") == 0)
                exit(1);
            else if (strcmp(command , "?") == 0)
                showCommands();
            else if (strcmp(command, "s") == 0)
                doShortestPath();
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
                cout << "";
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
        printf("  s <int1> <int2> \n");
        printf("  t <int1> <int2> \n");
        printf("  r <int> \n");
        printf("  i <int1> <int2> \n");
        printf("  d <int1> <int2> \n");
        printf("  l \n");
        printf("  f <filename> \n");
    }

    // finding the shortest path using breadth first search.
    void doShortestPath() {
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

        // if invalid island(s) entered.
        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the shortest path Command from %d to %d\n" ,
            val1 , val2);

        //use depth first seach to find if travelling from a to b possible.
        myStack ans = breadthFirstSearch(val1 - 1 , val2);

        // if the list is not empty we found a path.
        if (!ans.isEmpty()) {
            cout << "shortest path from " << val1 << " to " << val2 << ": ";
            ans.print();
        }
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

        // if invalid island(s) entered.
        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the Travel Command from %d to %d\n" ,
            val1 , val2);

        //use depth first seach to find if travelling from a to b possible.
        depthFirstSearchHelper(val1 - 1 , val2);
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

        // clearing all the linked lists of islands.
        for (int i = 0; i < Size; i++) {
            islands[i].clear();
        }
        delete[] islands;  // clearing all the islands.

        islands = new island[val1];  // creating a new array.
        Size = val1;  // setting size.
    }

    void doInsert() {
        int val1 , val2;
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

        // if wrong island number.
        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the Insert Command for %d\n" , val1);
        islands[val1 - 1].insertNode(val2);  // inserting the ferry ride from val1 to val2.
    }

    void doDelete() {
        int val1 , val2;
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

        // if wrong island number given.
        if (val1 > Size || val2 > Size) {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the Delete Command for %d\n" , val1);

        islands[val1 - 1].deleteNode(val2);  // deleting the ferry ride from val1 to val2.
    }

    void doList() {
        printf("Displaying the adjacency list:\n");
        // iterating over the islands and printing their ferry rides.
        for (int i = 0; i < Size; i++) {
            cout << i + 1;
            islands[i].print();
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

        // if the file already is in use.
        if (files.exists(fileName)) {
            cout << "File is already in use\n";
            return;
        }

        // inserting it inside node if it isnt in use.
        files.insertNode(fileName);

        FILE* file = fopen(fname , "r");  // opening the file.
        if (file == nullptr) {
            cout << "Cannot open the file\n";
            return;
        }

        // next steps:  (if any step fails: print an error message and return ) 
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns

        processCommandLoop(file);  //performing all the commands in file.
        fclose(file); // closing the file.
        files.deleteNode(fileName);  // deleting the file from file list.
    }

    // function to clear all the data.
    void clear() {
        for (int i = 0; i < Size; i++) {
            islands[i].clear();
        }
        delete[] islands;
        files.clear();
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
    islandData.clear();

    return 1;
}
