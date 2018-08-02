#ifndef _TOKENAFFIX_H
#define _TOKENAFFIX_H

#include "Token.h"
#include "Stack.h"

//Affix extractAffix(StackBlock *operatorStack, StackBlock *operandStack);
void encodeAffix(Token *token, Affix affix);
Affix getAffix(Token *token);
TokenType getTokenType(Token *token);

#endif // _TOKENAFFIX_H
