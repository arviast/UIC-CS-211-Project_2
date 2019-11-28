// Arvinbayar Jamsranjav
// CS 211 FALL 2019
// Project 2
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int debugMode;  // declaring variable for debugging
int foundL;     // to check if we have L or not

// implementing the stack
// ...
typedef struct origNode {
    int top;
    int size;
    char* origPtr;
} origNode;

// initializing the stack
// ...
void initialize(origNode *stack) {
    stack->size = 4;
    stack->top= 0;
    char* array = (char *)malloc(sizeof(char)*(stack->size));
    stack->origPtr = array;
}

// checking if the stack is emptry or not
// ...
int checkIfEmpty(origNode *stack) {
    if(stack->top == 0){
        return 1;
    }
    return 0;
}

// push and grow function
// whenever my stack is full it grows by 4
// when in debugMode it displays push, pop, also
// after each grow it displays prev size, new size,
// # of items coppied
// ...
void push(origNode *stack, char valueInput) {
    if(stack->top == stack->size) {
        char *temP = (char *)malloc((sizeof(char) * (stack->size) + 4));
        int i;
        for(i = 0; i < stack->size; i++) {
            temP[i] = stack->origPtr[i];
        }
        if (debugMode == TRUE) {
            printf("\nDEBUG MODE: # of items are coppied: %d\n", i);
        }
        free(stack->origPtr);
        stack->origPtr = temP;
        if(debugMode == TRUE) {
            printf("\n*** Change in the Size ***\nSize was: %d", stack->size);
        }
        stack->size = (stack->size + 4);
        if(debugMode == TRUE) {
            printf("\nSize now: %d\n", stack->size);
        }
    }
    stack->origPtr[stack->top] = valueInput;
    if(debugMode == TRUE) {
        printf("\nDEBUG MODE: %c is pushed to the stack\n", valueInput);
    }
    ++(stack->top);  // implementing top by one after push
}

// pop function
// decrementing top by one
// removes 1 value from the top of the stack
// included Debug info
// ...
void pop(origNode *stack) {
    if(debugMode == TRUE) {
        printf("\nDEBUG MODE: %c is popped from the stack\n", stack->origPtr[stack->top-1]);
    }
    (stack->top) -= 1;
    stack->origPtr[stack->top] = 0;
}

// return to the top function
char acessTop(origNode *stack) {
    return stack->origPtr[stack->top-1];
}

// we perform opeartions on wordList[m]
// then clear before wordList[m]
// ...
void clearStack(origNode* stack) {
    stack->size = 4;
    stack->top = 0;
    char *newTemp = (char*) malloc(sizeof(char) * (stack->size));
    free(stack->origPtr);
    stack->origPtr = newTemp;
}

// iterating through characters
// if iterator equals eraseChar value
// then skip that char
// ...
void RemoveChars(char *word, char eraseChar)
{
    int finisher = 0;
    int iterator = 0;
    
    while (word[iterator])
    {
        if (word[iterator]!=eraseChar)
        {
            word[finisher++] = word[iterator];
        }
        iterator++;
    }
    word[finisher]=0;  // starts from the 0 on every eraseChar
}

int main(int argc,char** argv)
{
    debugMode = FALSE;  // initial debugMode value is 0 (no parameter)
    foundL = FALSE;
    
    // Checks if there is parameter "-d"
    // ...
    int i;
    for(i = 0; i <argc; i++) {
        if(strcmp(argv[i], "-d") == 0)
            debugMode = TRUE;
    }
	char input[300];
    
    // Message that says debugMODE is ON
    // when parameter -d is given
    // ...
    if( debugMode == TRUE) {
        printf("Debugging Information \n");
    }
    
	 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);
   origNode stack;      // declaration of the stack
   initialize(&stack);  // initializing it
     
   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
     if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) ) {
         break;
     }
     
   printf ("%s\n", input);
   /*Start tokenizing the input into words separated by space
    We use strtok() function from string.h*/
   /*The tokenized words are added to an array of words*/
   
   char delim[] = " ";
   char *ptr = strtok(input, delim);
   int j = 0 ; 
   char *wordList[15];
   int counter = 0;  // counting how many words we have in input
   char decoded[40];
   decoded[0] = '\0';

	while (ptr != NULL)
	{	
		wordList[++j] = ptr;
		ptr = strtok(NULL, delim);
        counter++;
	}
     
   /*Run the algorithm to decode the message*/
     char *travel;  // declaration of pointer to the wordList[m]
     // iterates through every word in the wordList
     // started from 1, cuz 0 was null
     // ...
     int m;
     for (m = 1; m < counter+1; m++) {
         travel = wordList[m];
         // iterates through every char in wordList[m]
         // pushes only a, b, c, d
         // foundL is true (condition for matching)
         // ...
         int j;
         for(j = 0; j < strlen(wordList[m]); j++) {
             if (*travel == 'a' || *travel == 'b' || *travel == 'c' || *travel == 'd') {
                 foundL = TRUE;
                 push(&stack, *travel);
                 ++travel;
             }
             // checks if the letters map to L
             // if does, pop top
             // ...
             else if (*travel == 'm') {
                 if (acessTop(&stack) == 'a') {
                     pop(&stack);
                     ++travel;
                 }
                 else {
                     ++travel;
                     continue;
                 }
             }
             else if (*travel == 'n') {
                 if (acessTop(&stack) == 'b') {
                     pop(&stack);
                     ++travel;
                 }
                 else {
                     ++travel;
                     continue;
                 }
             }
             else if (*travel == 'o') {
                 if (acessTop(&stack) == 'c') {
                     pop(&stack);
                     ++travel;
                 }
                 else {
                     ++travel;
                     continue;
                 }
             }
             else if (*travel == 'p') {
                 if (acessTop(&stack) == 'd') {
                     pop(&stack);
                     ++travel;
                 }
                 else {
                     ++travel;
                     continue;
                 }
             }
             else{
                 ++travel;
             }
         }
         
         // modify wordList string if conditions are met
         // use removeChars function to erase extra letters
         if(checkIfEmpty(&stack) == 1 && foundL == TRUE) {
             char eraseChar;
             for(int y = 0; y < strlen(wordList[m]); y++) {
                 if (wordList[m][y] > 'd' || wordList[m][y] < 'a') {
                     eraseChar = wordList[m][y];
                     RemoveChars(wordList[m], eraseChar);
                     y--;
                 }
             }
             // saving my modified array
             // print
             // clear my array for next word
             // ...
             strcat(decoded, wordList[m]);
             strcat(decoded, " ");
             printf("%s",decoded);
             decoded[0] = '\0';
         }
         clearStack(&stack);
     }
 }
 printf ("\nGoodbye\n");

// abhcgmsopa bqcedpwon abmnpc abcdponm dfajbbmmn cabnmo
    
	return 0;
}
