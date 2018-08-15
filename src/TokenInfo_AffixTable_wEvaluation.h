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
int checkOperatorTokensAffixPossibilities(Token *currToken, Token *nextToken);
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo);
int areAffixesCombinationValid(Affix leftAffix, Affix thisAffix);

Affix checkTokenAffix(Tokenizer *tokenizer, Token *prevToken);
void checkTokenAffixAndEncodeAffix(Token *token, Tokenizer *tokenizer,TokenType prevTokenType);
void encodeTokenAffix(Token *token, Token *prevToken, Tokenizer *tokenizer,TokenType prevTokenType);
// encodeTokenAffix compare prevToken because need to check for '('

Token *combinePrefixWithOperandToken(Token *prefixToken, Token *operandToken);
#endif // _TOKENINFO_AFFIXTABLE_WEVALUATION_H
