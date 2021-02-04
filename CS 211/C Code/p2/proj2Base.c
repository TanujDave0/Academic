#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	
	char input[300];
	
	 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';


   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   printf ("%s\n", input);
   /*Start tokenizing the input into words separated by space
    We use strtok() function from string.h*/
   /*The tokenized words are added to an array of words*/
   
   char delim[] = " ";
   char *ptr = strtok(input, delim);
   int j = 0 ; 

   //Needs proper allocation
   // You can use other methods if you wish
   char *wordList[15];
  
 
	while (ptr != NULL)
	{	
      strcpy(wordList[j], ptr); 
		ptr = strtok(NULL, delim);      
      j++;
      
	}

   /*Run the algorithm to decode the message*/


 }


 printf ("\nGoodbye\n");





	return 0;
}
