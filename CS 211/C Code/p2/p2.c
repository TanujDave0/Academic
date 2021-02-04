#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct CStruct {
    char* ptr;
    int size;
    int head;
} stack;

void init(stack* data) {
    data->ptr = (char*)malloc(sizeof(char) * 4);
    data->size = 4;
    data->head = 0;
}

bool isEmpty(stack* data) {
    if (data->head == 0) {
        return true;
    }
    return false;
}
void push(stack* data , char word , bool debugMode) {
    char* temp;

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

void pop(stack* data , bool debugMode) {
    if (data->head) {
        if (debugMode) {
            printf("Character %c was popped from the stack.\n" , data->ptr[data->head]);
        }
        data->head--;
    }
}

char top(stack* data) {
    if (isEmpty(data)) {
        return '0';
    }
    return data->ptr[data->head - 1];
}

void clear(stack* data) {
    free(data->ptr);
    init(data);
}

bool inArr(char a , char arr[5]) {
    for (int i = 0; i < 4; i++) {
        if (a == arr[i]) {
            return true;
        }
    }
    return false;
}

int findPos(char a , char arr[5]) {
    for (int i = 0; i < 4; i++) {
        if (a == arr[i]) {
            return i;
        }
    }
    return -1;
}

void printWord(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (inArr(word[i] , "abcd")) {
            printf("%c" , word[i]);
        }
    }
}

void lower(char* arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        arr[i] = tolower(arr[i]);
    }
}

void decode(stack* data , char* words[15] , int numWords , bool debugMode) {
    char L[5] = "abcd";
    char L2[5] = "mnop";
    char temp;
    int pos;
    bool decoded = false;

    printf("in\n");

    for (int i = 0; i < numWords; i++) {
        bool msgWord = true;
        for (int j = 0; j < words[i][j] != '\0'; j++) {
            if (inArr(words[i][j] , L)) {
                push(data , words[i][j] , debugMode);
            } else if (inArr(words[i][j] , L2)) {
                if (isEmpty(data)) {
                    msgWord = false;
                    break;
                }
                temp = top(data);
                pos = findPos(temp , L);
                if (L2[pos] == words[i][j]) {
                    pop(data , debugMode);
                } else {
                    break;
                }
            }
        }
        if (isEmpty(data) && msgWord) {
            if (decoded) {
                printf(" ");
            }
            printWord(words[i]);
            decoded = true;
        }
        clear(data);
    }

    printf("out\n");
    if (!decoded) {
        printf("No valid word decoded\n");
    }
    printf("\n");
}

int main(int argc , char const* argv[]) {
    char input[300];
    stack data;
    init(&data);
    bool debugMode = false;

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
        for (int i = 0;i < numWords;i++) {
            free(wordList[i]);
        }
    }

    printf("\nGoodbye\n");

    return 0;
}
