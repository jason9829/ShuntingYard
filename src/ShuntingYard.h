#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Stack.h"
#include "TokenAffix.h"

Token operateOnTokens(StackBlock *operatorStack, StackBlock *operandStack);
Token *calculationOnTokens(Token *token_1, Token *token_2, Token *token_operator);
TokenType typecastTokenType(Token *token);
#endif // _SHUNTINGYARD_H
