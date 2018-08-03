#include "ShuntingYard.h"
#include "Token.h"
#include "TokenAffix.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include "Common.h"
#include <stdio.h>
/*
Token operateOnTokens(StackBlock *operatorStack, StackBlock *operandStack){
  if(operatorStack->head == NULL || operandStack->head == NULL){
    throwSimpleError(ERR_STACK_NULL, "Empty Stack detected");
  }
  else{
    Token *token_1;
    Token *token_2;
    Token *token_operator;
    if(operatorStack->count >=1 && operandStack->count >=2){
      popStack()
    }
  }
}
*/

// Example
//
//     operatorStack
//            +-----+
//  tail-->   +  *  + <---
//            +-----+    | next
//            +  -  +  __|
//            +-----+
//      head----^
//  *For this example expect return '1'
// Check for operators precendence return '1' if next operator presidence is higher
int checkForOperatorPrecedence(StackBlock *operatorStack){
  if(operatorStack->head == NULL || operatorStack->tail == NULL){
    throwSimpleError(ERR_STACK_NULL,"Operator Stack is empty");
  }
  else{
      if(){

      }
  }
}

int comparePrecedenceOf2_Operator(char operator1, char operator2){

}
