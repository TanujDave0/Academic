#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct nodeStruct {

         int data; 

         struct nodeStruct *next; 

}node; 

typedef node* nodeptr; 


int main ( ){

     nodeptr  temp = (nodeptr) malloc(sizeof(node)); 

return 0; 

}