#ifndef _OPERATORPRECEDENCE_WTABLE_H
#define _OPERATORPRECEDENCE_WTABLE_H

#include "Token.h"
#include "Tokenizer.h"

typedef struct OperatorPrecedence OperatorPrecedence;
struct OperatorPrecedence{
  int bindingPower;
};

OperatorPrecedence *getTokenPrecedence(Token *token);
int comparePrevTokenAndNextTokenPrecedence(Tokenizer *tokenizer, Token *prevToken);
#endif // _OPERATORPRECEDENCE_WTABLE_H
