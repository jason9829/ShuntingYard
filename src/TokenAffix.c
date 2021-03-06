#include "TokenAffix.h"
#include "Token.h"
#include "Stack.h"

// Combine TokenType and Affix
void encodeAffix(Token *token, Affix affix){
  // both are the same
  //token->type |= affix;
  token->type = token->type | affix;
}

// get the affixType
//        Affix           TokenType
//    ------^------   ------^-------
//    0 | 0 | 1 | 1 | 0 | 0 | 1 | 0
Affix getAffix(Token *token){
  return token->type & 0xffff0000;
}

// get the tokenType
TokenType getTokenType(Token *token){
    return token->type & 0x0000ffff;
}
