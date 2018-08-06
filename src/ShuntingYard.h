#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Arithmetic.h"
#include "TokenInfo_AffixTable_wEvaluation.h"

// In ascending order
typedef enum{
  BINARY_PLUS_MINUS,
  BINARY_MULTIPLICATION_DIVISION_REMAINDER,
  UNARY_PLUS_MINUS
} Presidence;

Token *shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack);
Token *operationOnStacks(StackBlock *operatorStack, StackBlock *operandStack);
void pushOperandStack(StackBlock *operandStack, Token *token);
void pushOperatorStack(StackBlock *operatorStack, Token *token);
OperatorType determineTokenOperatorType(Tokenizer *tokenizer, Token *prevToken);

#endif // _SHUNTINGYARD_H
