// Project-1, CS 211.
// Name: Tanuj Dave, NetId: tdave6.

#include <stdio.h>
#include <stdlib.h>

// function that makes copy of arr into arr2
void makeArrayCopy(int arr[] , int arr2[] , int size) {
    for (int i = 0; i < size; i++) {
        arr2[i] = arr[i];
    }
}

// swaps elements at index pos and pos2 inside arr.
void swap(int arr[] , int pos , int pos2) {
    int temp = arr[pos];
    arr[pos] = arr[pos2];
    arr[pos2] = temp;
}

// selection sort for arr.
void myFavoriteSort(int arr[] , int size) {
    int pos;
    for (int i = 0; i < size - 1; i++) {
        pos = i;
        for (int j = i; j < size; j++) {
            if (arr[pos] > arr[j]) {
                pos = j;
            }
        }
        swap(arr , i , pos);
    }
}

// compares unsortedArray and sortedArray for same elements at same index.
void indexComparison(int unsortedArray[] , int sortedArray[] , int size , int* counter) {
    for (int i = 0; i < size; i++) {
        if (unsortedArray[i] == sortedArray[i]) {
            (*counter)++;
        }
    }
}

// sweeps arr for elements that add upto target, returns 1 if found and -1 if not found.
int targetSum(int arr[] , int size , int target , int* index1 , int* index2) {
    int* pointer1 = &arr[0];
    int* pointer2 = &arr[size - 1];

    while (pointer1 != pointer2) {
        if (*pointer1 + *pointer2 < target) {
            pointer1++;
            (*index1)++;
        } else if (*pointer2 + *pointer1 > target) {
            pointer2--;
            (*index2)--;
        } else if (*pointer2 + *pointer1 == target) {
            return 1;
        }

    }
    return -1;
}

// the main.
int main(int argc , char** argv) {
    int val;
    int counter = 0;
    int actSize = 0;
    int userInput;
    int size = 4;
    int* arr = (int*)malloc(sizeof(int) * size);
    int* arr2;

    printf("Enter in a list of numbers to be stored in a dynamic array.\n");
    printf("End the list with the terminal value of -999\n");

    int i = 0;
    scanf("%d" , &val);
    while (val != -999) {
        if (i >= size) {
            int* tmp = arr;
            /*allocate new space for the larger array*/
            arr = (int*)malloc(sizeof(int) * size * 2);

            for (int k = 0; k < size; k++)
                arr[k] = tmp[k];
            for (int k = size; k < size * 2; k++)
                arr[k] = -999;

            free(tmp);
            size = size * 2;
        }

        arr[i] = val;
        i++;
        scanf("%d" , &val);
    }
    actSize = i; // actual size.

    // making sorted copy arr.
    arr2 = (int*)malloc(sizeof(int) * actSize);
    makeArrayCopy(arr , arr2 , actSize);
    myFavoriteSort(arr2 , actSize);

    /* Prompt user to enter a value to pick a task */
    printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
    scanf("%d" , &userInput);

    // looping till a valid input.
    while (userInput != 1 && userInput != 2) {
        printf("Invalid input. Enter 1 or 2.\n");
        scanf("%d" , &userInput);
    }
    if (userInput == 1) {
        /* If user input is 1, perform index comparison */
        indexComparison(arr , arr2 , actSize , &counter);
        if (counter) {
            printf("%d values are in the same location in both arrays.\n" , counter);
        } else {
            printf("All elements change location in the sorted array.\n");
        }
    } else {
        /* If user input is 2, perform target sum */
        printf("Enter in a list of numbers to use for searching.  \n");
        printf("End the list with a terminal value of -999\n");
        scanf("%d" , &val);

        while (val != -999) {
            int index1 = 0 , index2 = actSize - 1;
            /* call function to perform target sum operation */
            if (targetSum(arr2 , actSize , val , &index1 , &index2) != -1) {
                printf("Success! Elements at indices %d and %d add up to %d\n" , index1 , index2 , val);
            } else {
                printf("Target sum failed!\n");
            }

            scanf("%d" , &val); /* get next value */
        }
    }

    printf("Good bye");

    // freeing the allocated memory.
    free(arr);
    free(arr2);
    return 0;
}
