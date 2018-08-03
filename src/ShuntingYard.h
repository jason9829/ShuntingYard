#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Token.h"
#include "Stack.h"

// In ascending order
typedef enum{
  BINARY_PLUS_MINUS,
  BINARY_MULTIPLICATION_DIVISION_REMAINDER,
  UNARY_PLUS_MINUS
} Presidence;

Token operateOnTokens(StackBlock *operatorStack, StackBlock *operandStack);
int checkForOperatorPrecedence(StackBlock *operatorStack);
int comparePrecedenceOf2_Operator(char operator1, char operator2);
#endif // _SHUNTINGYARD_H
