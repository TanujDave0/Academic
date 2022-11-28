#include "linked_list.h"

void doAdd(node** head) {
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0) {
        printf("Error: Add command requires an integer value of at least 0\n");
        printf("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0) {
        printf("Error: Add command requires an integer value of at least 0\n");
        printf("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get group name from input */
    char* name = getName();
    if (NULL == name) {
        printf("Error: Add command requires a name to be given\n");
        printf("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    printf("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n" , name , NumBurgers , NumSalads);

    // add code to perform this operation here
    addToList(head, name, NumBurgers, NumSalads, 'i');
}

void doCallAhead(node** head) {
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0) {
        printf("Error: Call-ahead command requires an integer value of at least 0\n");
        printf("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0) {
        printf("Error: Call-ahead command requires an integer value of at least 0\n");
        printf("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }


    /* get group name from input */
    char* name = getName();
    if (NULL == name) {
        printf("Error: Call-ahead command requires a name to be given\n");
        printf("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }

    printf("Adding Call-ahead order for %s: %d burgers and %d salads\n" , name , NumBurgers , NumSalads);

    // add code to perform this operation here
    addToList(head, name, NumBurgers, NumSalads, 'c');
}

void doWaiting(node* head) {
    /* get order name from input */
    char* name = getName();
    if (NULL == name) {
        printf("Error: Waiting command requires a name to be given\n");
        printf("Wait command format: w <name>\n");
        return;
    }

    printf("Call-ahead order \"%s\" is now waiting in the restaurant\n" , name);

    // add code to perform this operation here
    updateStatus(head, name);
}

void doRetrieve(node** head) {
    /* get info of prepared food ready on the counter from input */
    int PreparedBurgers = getPosInt();
    if (PreparedBurgers < 0) {
        printf("Error: Retrieve command requires an integer value of at least 0\n");
        printf("Retrieve command format: r <# burgers> <# salads>\n");

        return;
    }

    int PreparedSalads = getPosInt();
    if (PreparedSalads < 0) {
        printf("Error: Retrieve command requires an integer value of at least 0\n");
        printf("Retrieve command format: r <# burgers> <# salads>\n");
        return;
    }

    clearToEoln();
    printf("Retrieve and remove the first group that can pick up the order of %d burgers and %d salads\n" , PreparedBurgers , PreparedSalads);

    // add code to perform this operation here
    char* name = retrieveAndRemove(head, PreparedBurgers, PreparedSalads);
}

void doList(node* head) {
    /* get order name from input */
    char* name = getName();
    if (NULL == name) {
        printf("Error: List command requires a name to be given\n");
        printf("List command format: l <name>\n");
        return;
    }

    printf("Order for \"%s\" is behind the following orders\n" , name);

    // add code to perform this operation here
    displayOrdersAhead(head, name);
}

void doDisplay(node* head) {
    clearToEoln();
    printf("Display information about all orders\n");

    displayListInformation(head);
}


void doEstimateTime(node* head) {
    /* get order name from input */
    char* name = getName();
    if (NULL == name) {
        printf("Error: Time command requires a name to be given\n");
        printf("Time command format: t <name>\n");
        return;
    }

    // add code to perform this operation here 
    int mins  = displayWaitingTime(head, name);
    printf(" Estimated wait time for %s is %d minutes:\n", name , mins);  
}