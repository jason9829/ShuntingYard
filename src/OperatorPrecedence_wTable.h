#ifndef _OPERATORPRECEDENCE_WTABLE_H
#define _OPERATORPRECEDENCE_WTABLE_H

#include "Token.h"
#include "Tokenizer.h"


typedef enum{
  INFIX_PLUS,
  INFIX_MINUS,
  INFIX_MULTIPLY,
  INFIX_DIVIDE,
  PREFIX_PLUS,
  PREFIX_MINUS,
  OPEN_BRACKET,
  CLOSE_BRACKET,
} operatorWithAffix;

typedef struct OperatorPrecedence OperatorPrecedence;
struct OperatorPrecedence{
  int bindingPower;
};

OperatorPrecedence *getTokenPrecedence(Token *token);
int comparePrevTokenAndNextTokenPrecedence(Token *currToken, Token *prevToken);
#endif // _OPERATORPRECEDENCE_WTABLE_H
