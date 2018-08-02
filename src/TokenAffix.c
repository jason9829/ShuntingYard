#include "TokenAffix.h"
#include "Token.h"
#include "Stack.h"

/*// find the Affix type of the token
Affix extractAffix(StackBlock *operatorStack, StackBlock *operandStack){
  Affix affix;

  if(operatorStack->head == NULL){
    return affix = NO_AFFIX;
  }
  else{
    // if operatorStack and operandStack only have one stack
    // the operator must be
    if(operatorStack->count == 1){
        return affix = PREFIX;
    }

  }
}*/
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
