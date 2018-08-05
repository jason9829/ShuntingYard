#ifndef _TOKENINFO_AFFIXTABLE_WEVALUATION_H
#define _TOKENINFO_AFFIXTABLE_WEVALUATION_H

#include "Token.h"
#include "Stack.h"
#include "Tokenizer.h"

typedef struct TokenInfo TokenInfo;
struct TokenInfo{
 int Attribute;
};

int checkOperatorsAffixPossibilities(Token *currToken, Tokenizer *nextTokens);
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo);
Affix checkTokenAffix(Token *currToken, Tokenizer *nextTokens);
#endif // _TOKENINFO_AFFIXTABLE_WEVALUATION_H
