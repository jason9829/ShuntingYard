#ifndef _TOKENINFO_AFFIXTABLE_WEVALUATION_H
#define _TOKENINFO_AFFIXTABLE_WEVALUATION_H

#include "Token.h"
#include "Stack.h"
#include "TokenInfo.h"

typedef struct TokenInfo TokenInfo;
struct TokenInfo{
 uint8_t Attribute;
};

int checkOperatorsAffixPossibilities(Token *currOperatorToken, Tokenizer *nextOperators);

#endif // _TOKENINFO_AFFIXTABLE_WEVALUATION_H
