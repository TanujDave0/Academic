#ifndef linked_list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define linked_list

typedef struct NODE {
    char* name;
    int burgers;
    int salads;
    char status;
    struct NODE* next;
} node;

void clearToEoln();
void doAdd(node** head);
void doCallAhead(node** head);
void doWaiting(node* head);
void doRetrieve(node** head);
void doList(node* head);
void doDisplay(node* head);
void doEstimateTime(node* head);
bool equal(char* a , char* b);
bool doesNameExist(node* head , char* name);
void addToList(node** head , char* name , int burgers , int salads , char status) ;
bool updateStatus(node* head , char* name);
char* retrieveAndRemove(node** head , int burgers , int salads);
int countOrdersAhead(node* head , char* name);
int displayWaitingTime(node* head , char* name);
void displayOrdersAhead(node* head , char* name);
void displayListInformation(node* head);
int getNextNWSChar();
int getPosInt();
char* getName();
void clearToEoln();
void printCommands();
int main();

#endif
