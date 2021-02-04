/*
 * CS 211, Fall 2020
 * Name: Tanuj Dave, NetID: tdave6
 *
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* This program will read the first 3 lines of input
   and prints a static 2D maze*/
typedef struct mazeStruct {
    char** arr;  /* allows for a maze of size 30x30 plus outer walls */
    int xsize , ysize;
    int xstart , ystart;
    int xend , yend;
} maze;

// struct to implement a stack.
typedef struct CStruct {
    int x; // stores the x coordinate.
    int y; // stores the y cordinate.
    struct Cstruct* prev; // pointer to the previous node.
} node;

// fucntion prototypes header and comments in definition.
void init(node** head);
bool isEmpty(node* head);
void push(node** head , int x , int y , bool debugMode);
void pop(node** head , bool debugMode);
node* top(node* head);
void clear(node** head, bool debug);
void print(node* head);
bool isEnd(node* head , maze* maze);
int unvisitedNeighbour(node** head , maze* maze , int *coins, bool debug);
void finalMessage(node* head , int coins);

// main.
int main(int argc , char** argv) {
    int coins = 0;
    int xpos , ypos;
    int i , j;
    int x , y;
    char temp;
    bool debug = false;
    FILE* file;
    maze m1;
    node* head;

    init(&head); // initialising the head to NULL.
    setbuf(stdout, NULL);

    /* verify the proper number of command line arguments were given */
    if (argc > 3 || argc < 2) {
        fprintf(stdout, "Usage: %s <input file name>\n" , argv[0]);
        exit(-1);
    }

    // searching for the debug.
    j = 1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d")==0) {
            debug = true;
            if (i == 1) {
                j = 2;
            }
        }
    }

    /* Try to open the input file. */
    if ((file = fopen(argv[j] , "r")) == NULL) {
        fprintf(stdout, "Can't open input file: %s" , argv[j]);
        exit(-1);
    }

    /* read in the size, starting and ending positions in the maze */
    if (fscanf(file , "%d %d" , &m1.xsize , &m1.ysize) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(-1);
    }
    if (fscanf(file , "%d %d" , &m1.xstart , &m1.ystart) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(-1);
    }
    if (fscanf(file , "%d %d" , &m1.xend , &m1.yend) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(-1);
    }

    // checking for the errors in forst 3 lines..
    if(m1.xsize <= 0 || m1.ysize <=0) {
        fprintf(stderr, "Maze sizes must be greater than 0.\n");
        exit(-1);
    }
    printf ("size: %d, %d\n", m1.xsize, m1.ysize);

    if (m1.xstart <= 0 || m1.xstart > m1.xsize ||
        m1.ystart <= 0 || m1.ystart > m1.ysize) {
        fprintf(stderr , "Start/End position outside of maze range.\n");
        exit(-1);
    }
    fprintf(stdout, "start: %d, %d\n" , m1.xstart , m1.ystart);

    if (m1.xend <= 0 || m1.xend > m1.xsize ||
        m1.yend <= 0 || m1.yend > m1.ysize) {
        fprintf(stderr , "Start/End position outside of maze range.\n");
        exit(-1);
    }
    fprintf(stdout, "end: %d, %d\n" , m1.xend , m1.yend);

    // dynamically allocating the memory for the maze.
    m1.arr = (char**)malloc(sizeof(char*) * (m1.xsize + 2));
    for (int i = 0; i < m1.xsize + 2; i++) {
        m1.arr[i] = (char*)malloc(sizeof(char) * (m1.ysize + 2));
    }

    /* initialize the maze to empty */
    for (i = 0; i < m1.xsize + 2; i++)
        for (j = 0; j < m1.ysize + 2; j++)
            m1.arr[i][j] = '.';

    /* mark the borders of the maze with *'s */
    for (i = 0; i < m1.xsize + 2; i++) {
        m1.arr[i][0] = '*';
        m1.arr[i][m1.ysize + 1] = '*';
    }
    for (i = 0; i < m1.ysize + 2; i++) {
        m1.arr[0][i] = '*';
        m1.arr[m1.xsize + 1][i] = '*';
    }

    /* mark the starting and ending positions in the maze */
    m1.arr[m1.xstart][m1.ystart] = 's';
    m1.arr[m1.xend][m1.yend] = 'e';

    /*This code will only read the first three lines */
    /*Reading the rest of the input and placing blocked and coin positions. */
    while (fscanf(file , "%d %d %c" , &x , &y , &temp) != EOF) {
        if (x > m1.xsize || x <= 0 ||
            y > m1.ysize || y <= 0) {
            fprintf(stderr , "Invalid coordinates: outside of maze range.\n");
            continue;
        }
        if ((x == m1.xstart && y == m1.ystart) ||
            (x == m1.xend && y == m1.yend)) {
            fprintf(stderr , "Invalid coordinates: attempting to block start/end position.\n");
            continue;
        }
        if (temp != 'c' && temp != 'b') {
            fprintf(stderr , "Invalid type: type is not recognized.\n");
            continue;
        }
        /* Blocked positions are marked with 'b' in the input file
        They should be marked by * in the maze */
        if (temp == 'b') {
            m1.arr[x][y] = '*';
        } else {
            m1.arr[x][y] = 'C'; /*Coin positions are marked by 'c'*/
        }
    }

    /*Close the file*/
    fclose(file);

    /* print out the initial maze */
    for (i = 0; i < m1.xsize + 2; i++) {
        for (j = 0; j < m1.ysize + 2; j++)
            fprintf(stdout, "%c" , m1.arr[i][j]);
        fprintf(stdout, "\n");
    }

    // pushing start on the top of stack and marking it visited.
    push(&head , m1.xstart , m1.ystart , debug);
    m1.arr[m1.xstart][m1.ystart] = 'v';
    
    // finding the path to end.
    do {
        if (isEnd(head , &m1)) {
            break;
        }
        int n = unvisitedNeighbour(&head , &m1 , &coins, debug);
        if (n == 0) { // if neoghbour checked.
            pop(&head , debug);
        }
    } while (!isEmpty(head));

    // printing  the final message and stack.
    if (isEmpty(head)) {
        fprintf(stdout, "\nThis maze has no solution.\n");
    } else {
        fprintf(stdout, "\nThe maze has a solution.\n");
        fprintf(stdout, "The amount of coins collected: %d\n" , coins);
        fprintf(stdout, "The path from start to end: \n");
        print(head);
    }

    printf("\n");
    clear(&head, debug); // clearing the memory.

    for (int i = 0; i < m1.xsize + 2; i++) {
        free(m1.arr[i]);
    }

    free(m1.arr); // freeing the maze.
    printf("\n");
    return 0;
}

// function to initialise the stack.
void init(node** head) {
    *head = NULL;
}

// functiont to check if the stack is empty.
bool isEmpty(node* head) {
    if (head == NULL) {
        return true;
    }
    return false;
}

// function to push a value onto the stack.
void push(node** head , int x , int y , bool debugMode) {
    node* temp = (node*)malloc(sizeof(node));

    // temp->ptr = (int*)malloc(sizeof(int) * 2);
    temp->x = x;
    temp->y = y;
    temp->prev = *head;
    *head = temp;
    if (debugMode) {
        fprintf(stdout, "(%d,%d) pushed into the stack.\n" , x , y);
    }
}

// function to pop the first element of the stack.
void pop(node** head , bool debugMode) {
    node* temp = *head;
    if ((*head) != NULL) {
        if (debugMode) {
            fprintf(stdout, "(%d,%d) popped off the stack.\n" , (*head)->x , (*head)->y);
        }
        if(temp->prev == NULL){
            free(*head);
            *head = NULL;
        }
        else{
            *head = temp->prev;
            free(temp);
        }
    }
}

// function that returns the topmost node of the stack.
node* top(node* head) {
    return head;
}

// function to clear the stack for next run.
void clear(node** head, bool debug) {
    node* temp;
    while (*head != NULL) {
        // printf("doing for: %p\n", *head);
        pop(head, debug);
    }
}

// printing the solution/stack.
void print(node* head) {
    if (head != NULL) {
        print(head->prev);
        fprintf(stdout, "(%d,%d) " , top(head)->x , top(head)->y);
    }
}

// checks if the current node is the end node.
bool isEnd(node* head , maze* maze) {
    if (head == NULL) {
        return false;
    }
    if (top(head)->x == maze->xend && top(head)->y == maze->yend) {
        return true;
    }
    return false;
}

// checking for unvisited neighbours and updating the stack and coins.
int unvisitedNeighbour(node** head , maze* maze , int* coins, bool debug) {
    node* temp = *head;
    int x,y;
    // checking right
    char curr = maze->arr[top(temp)->x + 1][top(temp)->y];
    if (curr != 'v' && curr != '*') {
        x =  top(temp)->x + 1;
        y = top(temp)->y;
        push(head , x , y , debug);
        if (maze->arr[top(temp)->x + 1][top(temp)->y] == 'C') { // if coin found.
            (*coins)++;
        }
        maze->arr[top(temp)->x + 1][top(temp)->y] = 'v';
        return 1; // returns 1 if nieghbour is not checked.
    }
    // checking down
    curr = maze->arr[top(temp)->x][top(temp)->y + 1];
    if (curr != 'v' && curr != '*') {
        x =  top(temp)->x;
        y = top(temp)->y + 1;
        push(head , x , y , debug);
        if (maze->arr[top(temp)->x][top(temp)->y + 1] == 'C') {
            (*coins)++;
        }
        maze->arr[top(temp)->x][top(temp)->y + 1] = 'v';
        return 1;
    }
    // checking left
    curr = maze->arr[top(temp)->x - 1][top(temp)->y];
    if (curr != 'v' && curr != '*') {
        x =  top(temp)->x - 1;
        y = top(temp)->y;
        push(head , x , y , debug);
        if (maze->arr[top(temp)->x - 1][top(temp)->y] == 'C') {
            (*coins)++;
        }
        maze->arr[top(temp)->x - 1][top(temp)->y] = 'v';
        return 1;
    }
    // checking up
    curr = maze->arr[top(temp)->x][top(temp)->y - 1];
    if (curr != 'v' && curr != '*') {
        x =  top(temp)->x;
        y = top(temp)->y - 1;
        push(head , x , y , debug);
        if (maze->arr[top(temp)->x][top(temp)->y - 1] == 'C') {
            (*coins)++;
        }
        maze->arr[top(temp)->x][top(temp)->y - 1] = 'v';
        return 1;
    }
    return 0; // no unchecked neighbours
}