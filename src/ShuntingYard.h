#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Arithmetic.h"
#include "TokenInfo_AffixTable_wEvaluation.h"

void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack);
Token *operationOnStacksIfOperatorIsInfix(StackBlock *operatorStack, StackBlock *operandStack);
void pushOperandStack(StackBlock *operandStack, Token *token);
void pushOperatorStack(StackBlock *operatorStack, Token *token);
OperatorType determineTokenOperatorType(Tokenizer *tokenizer, Token *prevToken);

#endif // _SHUNTINGYARD_H
