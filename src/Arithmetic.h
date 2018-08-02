#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#include "Stack.h"
#include "TokenAffix.h"

Token *calculationOnTokens(Token *token_1, Token *token_2, Token *token_operator);
Token *additionOf2Tokens(Token *token_1, Token *token_2);
Token *subtractionOf2Tokens(Token *token_1, Token *token_2);
Token *multiplicationOf2Tokens(Token *token_1, Token *token_2);
Token *divisionOf2Tokens(Token *token_1, Token *token_2);
#endif // _ARITHMETIC_H
