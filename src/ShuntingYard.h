#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Stack.h"
#include "TokenAffix.h"

Token operateOnTokens(StackBlock *operatorStack, StackBlock *operandStack);
Token *calculationOnTokens(Token *token_1, Token *token_2, Token *token_operator);
Token *additionOf2Tokens(Token *token_1, Token *token_2);
Token *subtractionOf2Tokens(Token *token_1, Token *token_2);
Token *multiplicationOf2Tokens(Token *token_1, Token *token_2);
Token *divisionOf2Tokens(Token *token_1, Token *token_2);

#endif // _SHUNTINGYARD_H
