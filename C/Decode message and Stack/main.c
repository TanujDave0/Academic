//
// CS 211 Fall 2020
// Name: Tanuj Dave, NetID: tdave6
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// struct to implement a stack.
typedef struct CStruct {
    char* ptr; // pointer to the stack data.
    int size; // size of the stack.
    int head; // pointer to the head of the stack (not the top).
} stack;

// prototypes, go to definition for the explanation.
void init(stack* data);
bool isEmpty(stack* data);
void push(stack* data , char word , bool debugMode);
void pop(stack* data , bool debugMode);
char top(stack* data);
void clear(stack* data);
bool inArr(char a , char arr[5]);
int findPos(char a , char arr[5]);
void printWord(char* word);
void lower(char* arr);
void decode(stack* data , char* words[15] , int numWords , bool debugMode);

int main(int argc , char const* argv[]) {
    char input[300];
    stack data; // the stack
    bool debugMode = false;

    init(&data); // initialising the stack.
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i] , "-d") == 0) {
            debugMode = true;
        }
    }

    /* set up an infinite loop */
    while (1) {
        /* get line of input from standard input */
        printf("\nEnter input to check or q to quit\n");
        fgets(input , 300 , stdin);

        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0') {
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ((strcmp(input , "q") == 0) || (strcmp(input , "Q") == 0))
            break;

        printf("%s\n" , input);
        /*Start tokenizing the input into words separated by space
         We use strtok() function from string.h*/
         /*The tokenized words are added to an array of words*/
        char delim[] = " ";
        char* ptr = strtok(input , delim);
        int j = 0;

        //Needs proper allocation
        // You can use other methods if you wish
        char* wordList[15];
        while (ptr != NULL) {
            lower(ptr);
            wordList[j] = (char*)malloc(sizeof(char) * strlen(ptr));
            strcpy(wordList[j] , ptr);
            ptr = strtok(NULL , delim);
            j++;
        }

        int numWords = j;
        /*Run the algorithm to decode the message*/
        decode(&data , wordList , numWords , debugMode);
        for (int i = 0; i < numWords; i++) {
            free(wordList[i]); // freeing the memory.
        }
    }

    free(data.ptr);
    printf("\nGoodbye\n");

    return 0;
}

// function to initialise the stack.
void init(stack* data) {
    data->ptr = (char*)malloc(sizeof(char) * 4); // allocating the stack a memory for 4 chars.
    data->size = 4;
    data->head = 0;
}

// functiont to check if the stack is empty.
bool isEmpty(stack* data) {
    if (data->head == 0) {
        return true;
    }
    return false;
}

// function to push a value onto the stack.
void push(stack* data , char word , bool debugMode) {
    char* temp;

    // growing the stack if stack is full.
    if (data->head == data->size) {
        if (debugMode) {
            printf("The stack has grown from %d to %d, and a total of %d values were copied into the larger array.\n" , data->size , data->size + 4 , data->size);
        }
        temp = data->ptr;
        data->ptr = (char*)malloc(sizeof(char) * (data->size + 4));
        data->size += 4;

        for (int i = 0; i < data->size; i++) {
            data->ptr[i] = temp[i];
        }
        free(temp);
    }

    data->ptr[data->head] = word;
    data->head++;
    if (debugMode) {
        printf("Character %c was pushed into the stack.\n" , word);
    }
}

// function to pop the first element of the stack.
void pop(stack* data , bool debugMode) {
    if (data->head) {
        if (debugMode) {
            printf("Character %c was popped from the stack.\n" , data->ptr[data->head - 1]);
        }
        data->head--;
    }
}

// function that returns the topmost value of the stack.
char top(stack* data) {
    if (isEmpty(data)) {
        return '0';
    }
    return data->ptr[data->head - 1];
}

// function to clear the stack for next run.
void clear(stack* data) {
    free(data->ptr);
    init(data);
}

// function to check if char a is present in the array arr.
bool inArr(char a , char arr[5]) {
    for (int i = 0; i < 4; i++) {
        if (a == arr[i]) {
            return true;
        }
    }
    return false;
}

// finding the position of char a in array arr.
int findPos(char a , char arr[5]) {
    for (int i = 0; i < 4; i++) {
        if (a == arr[i]) {
            return i;
        }
    }
    return -1; // if not found.
}

// function to print the decoded msg out of the word.
void printWord(char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (inArr(word[i] , "abcd")) {
            printf("%c" , word[i]);
        }
    }
}

// function that lowers the characters int the array.
void lower(char* arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        arr[i] = tolower(arr[i]);
    }
}

// function for performing the decode task, 
void decode(stack* data , char* words[15] , int numWords , bool debugMode) {
    char L[5] = "abcd";
    char L2[5] = "mnop";
    char* message[15];
    char temp;
    int pos;
    bool decoded = false;
    char space = ' ';

    // looping over the list of words.
    for (int i = 0; i < numWords; i++) {
        bool msgWord = false;
        for (int j = 0; j < words[i][j] != '\0'; j++) {
            if (inArr(words[i][j] , L)) { // if the character is in L.
                push(data , words[i][j] , debugMode);
            } else if (inArr(words[i][j] , L2)) { // if the character is in L2.
                if (isEmpty(data)) {
                    msgWord = false;
                    break;
                }
                msgWord = true;
                temp = top(data);
                pos = findPos(temp , L);
                if (L2[pos] == words[i][j]) {
                    pop(data , debugMode);
                } else {
                    break;
                }
            }
        }
        if (isEmpty(data) && msgWord) { // if the word is msg word.
            decoded = true;
        } else {
            strcpy(words[i] , "\0"); // if not the msg word, makes it empty string.
        }
        clear(data); // clear the stack for next word.
    }

    // printing the message.
    int k = 0;
    for (int i = 0; i < numWords; i++) {
        if (strcmp(words[i] , "\0") != 0) {
            if (k != 0) {
                printf(" ");
            }
            printWord(words[i]);
            k++;
        }
    }
    // if no words decoded.
    if (!decoded) {
        printf("No valid word decoded\n");
    }
    printf("\n");
}
