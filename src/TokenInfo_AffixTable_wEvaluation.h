#ifndef _TOKENINFO_AFFIXTABLE_WEVALUATION_H
#define _TOKENINFO_AFFIXTABLE_WEVALUATION_H

#include "Token.h"
#include "Tokenizer.h"

typedef struct TokenInfo TokenInfo;
struct TokenInfo{
 int Attribute;
};

typedef enum{
  UNARY = 1,
  BINARY = 2
}OperatorType;

int checkOperatorsAffixPossibilities(Token *currToken, Tokenizer *nextTokens);
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo);
Affix checkTokenAffix(Tokenizer *tokenizer, Token *prevToken);
void checkTokenAffixAndEncodeAffix(Tokenizer *tokenizer, Token *prevToken);
OperatorType determineOperatorType(Affix tokenAffix);
Token *combinePrefixWithToken(Tokenizer *tokenizer, Token *prefixToken);
#endif // _TOKENINFO_AFFIXTABLE_WEVALUATION_H
