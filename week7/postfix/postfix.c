#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/stack.h"
#include "../../lib/duy.h"


 int main(int argc, char* argv[]) {
   char express[30];
   printf("Enter the postfix expression: ");
   scanf("%[^\n]", express);
   myfflush();


   node *stack;
   initialize(&stack);
   int i;

   for (i = 0; i < express.length; i++) {
     
   }
   
   return 0;
 }
