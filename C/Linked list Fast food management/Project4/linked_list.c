#include "linked_list.h"

// function that checks if two strings are equal.
bool equal(char* a , char* b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    if (strlen(a) != strlen(b)) {
        return false;
    }
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

// This operation is to return a Boolean value indicating whether
// a name already exists in the linked list. This is to be used when
// the a, c, w, t and l commands are given as input.
bool doesNameExist(node* head , char* name) {
    if (head == NULL) {
        return false;
    }
    while (head != NULL) {
        if (equal(head->name , name)) {
            return true;
        }
        head = head->next;
    }
    return false;
}

// This operation is to add a new node to the end of the linked list.
// This is to be used when the a and c commands are given as input.
void addToList(node** head , char* name , int burgers , int salads , char status) {
    bool check = true;
    if (*head == NULL) {
        *head = (node*)malloc(sizeof(node));
        (*head)->next = NULL;
        check = false;
    }

    node* temp = *head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (check) {
        temp->next = (node*)malloc(sizeof(node));
        temp = temp->next;
    }
    temp->name = name;
    temp->burgers = burgers;
    temp->salads = salads;
    temp->status = status;
    temp->next = NULL;
}

// This operation is to change the in-restaurant status when a call-ahead order
// arrives at the restaurant. This operation will return a FALSE value if that
// order is already marked as being in the restaurant. This is to be used when
// the w command is given as input.
bool updateStatus(node* head , char* name) {
    if (!doesNameExist(head , name)) {
        printf("No match found for the given name.Try again!\n");
        return false;
    }

    while (head != NULL) {
        if (equal(head->name , name)) {
            if (head->status == 'c') {
                head->status = 'i';
            } else {
                return false;
            }
        }
        head = head->next;
    }
    return true;
}

// This operation is to find the first in-restaurant order that matches the
// order prepared for pick up at the counter. This operation is to return the
// name of group.This group is to be removed from the linked list. This is to
// be used when the r command is given as input.
char* retrieveAndRemove(node** head , int burgers , int salads) {
    node* temp = *head;
    node* prev = NULL;
    char* name = NULL;
    
    while (temp != NULL) {
        if (temp->burgers <= burgers && temp->salads <= salads && temp->status == 'i') {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            name = (char*)malloc(sizeof(char) * strlen(temp->name));
            strcpy(name , temp->name);
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (name == NULL ) {
        printf("No matching orders found.\n");
    }
    return name;
}

// This operation is to return the number of orders waiting ahead of an order
// with a specific name. This is to be used when the l command is given as input.
int countOrdersAhead(node* head , char* name) {
    int ans = 0;
    while (head != NULL) {
        if (equal(head->name , name)) {
            break;
        }
        ans++;
        head = head->next;
    }
    return ans;
}

// This operation is to return the estimated waiting time for the specific name.
// The function will check the number of burgers and salads ordered ahead of the
// specified name and using known preparing time (5 minutes for burger and 2 minutes for salad)
// calculates the estimated wait time. This is to be used when t command is given as input.
int displayWaitingTime(node* head , char* name) {
    int ans = 0;
    while (head != NULL) {
        if (equal(head->name , name)) {
            break;
        }
        ans += head->burgers * 5;
        ans += head->salads * 2;
        head = head->next;
    }
    return ans;
}

// This operation traverses down the list until a specific order name is encountered.
// As each node is traversed, print out that node’s orders. This command is to be used
// when the l command is given.
void displayOrdersAhead(node* head , char* name) {
    while (head != NULL) {
        if (equal(head->name , name)) {
            break;
        }
        printf(" %s: %d burgers and %d salads \n" , head->name , head->burgers , head->salads);
        head = head->next;
    }
}

// This operation to traverse down the entire list from beginning to end. As each node is traversed,
// print out that node’s name, order details and in-restaurant status. This command is to be used
// when the d command is given as input.
void displayListInformation(node* head) {
    while (head != NULL) {
        if (head->status == 'i') {
            printf("%s: %d burgers and %d salads, currently in the restaurant.\n" , head->name , head->burgers , head->salads);
        } else if (head->status == 'c') {
            printf("%s: %d burgers and %d salads, currently not in the restaurant.\n" , head->name , head->burgers , head->salads);
        }
        head = head->next;
    }
}