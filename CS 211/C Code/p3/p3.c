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
    int* ptr; // pointer to the stack data.
    struct Cstruct *prev; // pointer to the previous node.
} node;

void init(node** head);
bool isEmpty(node* head);
void push(node** head , int x , int y , bool debugMode);
void pop(node** head , bool debugMode);
node* top(node* head);
void clear(node** head);
void print(node* head);
bool isEnd(node* head, maze* maze);
int unvisitedNeighbour(node** head, maze* maze, int *coins);
void finalMessage(node* head, int coins);

int main(int argc , char** argv) {
    maze m1;
    int coins = 0;
    int xpos , ypos;
    int i , j;
    int x , y;
    char temp;
    FILE* file;
    node* head;
    init(&head);

    /* verify the proper number of command line arguments were given */
    if (argc != 2) {
        printf("Usage: %s <input file name>\n" , argv[0]);
        exit(-1);
    }

    /* Try to open the input file. */
    if ((file = fopen(argv[1] , "r")) == NULL) {
        printf("Can't open input file: %s" , argv[1]);
        exit(-1);
    }

    /* read in the size, starting and ending positions in the maze */
    if (fscanf(file , "%d %d" , &m1.xsize , &m1.ysize) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(1);
    }
    // checking for errors.
    if (m1.xsize <= 0 || m1.ysize <= 0) {
        fprintf(stderr , "Maze sizes must be greater than 0.\n");
        exit(-1);
    }
    if (fscanf(file , "%d %d" , &m1.xstart , &m1.ystart) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(1);
    }
    if (fscanf(file , "%d %d" , &m1.xend , &m1.yend) == EOF) {
        fprintf(stderr , "Invalid data file.\n");
        exit(1);
    }
    // checking for errors.
    if (m1.xstart <= 0 || m1.xstart > m1.xsize ||
        m1.ystart <= 0 || m1.ystart > m1.ysize ||
        m1.xend <= 0 || m1.xend > m1.xsize ||
        m1.yend <= 0 || m1.yend > m1.ysize) {
        fprintf(stderr , "Start/End position outside of maze range.\n");
        exit(-1);
    }

    /* print them out to verify the input */
    printf("size: %d, %d\n" , m1.xsize , m1.ysize);
    printf("start: %d, %d\n" , m1.xstart , m1.ystart);
    printf("end: %d, %d\n" , m1.xend , m1.yend);

    // dynamically allocating the memory.
    m1.arr = (char**)malloc(sizeof(char*) * (m1.ysize + 1));
    for (int i = 0; i < m1.ysize; i++) {
        m1.arr[i] = (char*)malloc(sizeof(char) * (m1.xsize + 1));
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
        if (x == m1.xstart && y == m1.ystart) {
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
            m1.arr[x][y] = temp; /*Coin positions are marked by 'c'*/
        }
    }

    /*Close the file*/
    fclose(file);

    /* print out the initial maze */
    for (i = 0; i < m1.xsize + 2; i++) {
        for (j = 0; j < m1.ysize + 2; j++)
            printf("%c" , m1.arr[i][j]);
        printf("\n");
    }

    // pushing start on the top of stack and marking it visited.
    push(&head , m1.xstart , m1.ystart , false);
    m1.arr[m1.xstart][m1.ystart] = 'v';
    // finding the path to end.
    do {
        if(isEnd(head, &m1)) {
            break;
        }
        int n = unvisitedNeighbour(&head, &m1, &coins);
        if (n == 0) { // if neoghbour checked.
            pop(&head, false);
        }
    } while (!isEmpty(head));

    // printing  the final message and stack.
    finalMessage(head, coins);
    print(head);
    printf("end\n");
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
    node* temp = (node*) malloc(sizeof(node));

    temp->ptr = (int*)malloc(sizeof(int)*2);
    temp->ptr[0] = x;
    temp->ptr[1] = y;
    temp->prev = *head;
    *head = temp;
    if (debugMode) {
        printf("(%d,%d) pushed into the stack.\n" , x , y);
    }
}

// function to pop the first element of the stack.
void pop(node** head , bool debugMode) {
    node* temp = *head;
    if ((*head)->prev != NULL) {
        *head = temp->prev;
        free(temp);
        if (debugMode) {
            printf("(%d,%d) was popped from the stack.\n" , (*head)->ptr[0] , (*head)->ptr[1]);
        }
    } else {
        free(*head);
        *head = NULL;
    }
}

// function that returns the topmost node of the stack.
node* top(node* head) {
    return head;
}

// function to clear the stack for next run.
void clear(node** head) {
    node* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->prev;
        free(temp);
    }
}

// printing the solution/stack.
void print(node* head) {
    if (head != NULL) {
        print(head->prev);
        printf("(%d,%d) " , top(head)->ptr[0] , top(head)->ptr[1]);
    }
}

// checks if the current node is the end node.
bool isEnd(node* head, maze* maze) {
    if(head == NULL) {
        return false;
    }
    if (top(head)->ptr[0] == maze->xend && top(head)->ptr[1] == maze->yend){
        return true;
    }
    return false;
}

// checking for unvisited neighbours and updating the stack and coins.
int unvisitedNeighbour(node** head, maze* maze, int *coins) {
    node* temp = *head;
    // checking right
    char curr = maze->arr[top(temp)->ptr[0] + 1][top(temp)->ptr[1]];
    if (curr != 'v' && curr != '*') {
        push(head, top(temp)->ptr[0] + 1, top(temp)->ptr[1], false);
        if (maze->arr[top(temp)->ptr[0] + 1][top(temp)->ptr[1]] == 'c') { // if coin found.
            (*coins)++;
        }
        maze->arr[top(temp)->ptr[0] + 1][top(temp)->ptr[1]] = 'v';
        return 1; // returns 1 if nieghbour is not checked.
    }
    // checking down
    curr = maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] + 1];
    if (curr != 'v' && curr != '*') {
        push(head, top(temp)->ptr[0], top(temp)->ptr[1] + 1, false);
        if (maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] + 1] == 'c') {
            (*coins)++;
        }
        maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] + 1] = 'v';
        return 1;
    }
    // checking left
    curr = maze->arr[top(temp)->ptr[0] - 1][top(temp)->ptr[1]];
    if (curr != 'v' && curr != '*') {
        push(head, top(temp)->ptr[0] - 1, top(temp)->ptr[1], false);
        if (maze->arr[top(temp)->ptr[0] - 1][top(temp)->ptr[1]] == 'c') {
            (*coins)++;
        }
        maze->arr[top(temp)->ptr[0] - 1][top(temp)->ptr[1]] = 'v';
        return 1;
    }
    // checking up
    curr = maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] - 1];
    if (curr != 'v' && curr != '*') {
        push(head, top(temp)->ptr[0], top(temp)->ptr[1] - 1, false);
        if (maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] - 1] == 'c') {
            (*coins)++;
        }
        maze->arr[top(temp)->ptr[0]][top(temp)->ptr[1] - 1] = 'v';
        return 1;
    }
    return 0; // no unchecked neighbours
}

// printing the final message.
void finalMessage(node* head, int coins) {
    if (head = NULL) {
        printf("\nThis maze has no solution.\n");
    }
    else {
        printf("\nThis maze has a solution.\nThe number of coins collected: %d\n", coins);
        printf("The path from start to end:\n");
    }
}