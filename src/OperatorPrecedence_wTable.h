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
  INVALID_OPERATOR
} operatorWithAffix;

typedef struct OperatorPrecedence OperatorPrecedence;
struct OperatorPrecedence{
  int bindingPower;
};

typedef struct OperatorPrecedenceAndAssociativity OperatorPrecedenceAndAssociativity;
struct OperatorPrecedenceAndAssociativity{
  int bindingPower;
  Associativity associativity;
};

OperatorPrecedence *getTokenPrecedence(Token *token);
OperatorPrecedenceAndAssociativity *getTokenPrecedenceAndAssociativity(Token *token);
int comparePrevTokenAndNextTokenPrecedence(Token *currToken, Token *prevToken);
#endif // _OPERATORPRECEDENCE_WTABLE_H
