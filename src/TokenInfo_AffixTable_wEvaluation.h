#ifndef _TOKENINFO_AFFIXTABLE_WEVALUATION_H
#define _TOKENINFO_AFFIXTABLE_WEVALUATION_H

#include "Token.h"
#include "Stack.h"
#include "Tokenizer.h"

typedef struct TokenInfo TokenInfo;
struct TokenInfo{
 int Attribute;
};

int checkOperatorsAffixPossibilities(Token *currOperatorToken, Tokenizer *nextOperators);
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo);
#endif // _TOKENINFO_AFFIXTABLE_WEVALUATION_H
