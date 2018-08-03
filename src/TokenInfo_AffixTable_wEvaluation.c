#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Stack.h"
#include "TokenInfo"
#include "Exception.h"
#include "Error.h"




#define PREFIX_TYPE 4
#define INFIX_TYPE 2
#define SUFFIX_TYPE 1

TokenInfo AffixPossibilities[100] = {
  ['+'] = {.Attribute = PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE},
  ['-'] = {.Attribute = PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE},
  ['*'] = {.Attribute = INFIX_TYPE},
  ['/'] = {.Attribute = INFIX_TYPE},
};

TokenInfo *getTokenInfo(Token *token){
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  if(operatorSymbol == '+'){
    return &AffixPossibilities['+'];
  }
  else if(operatorSymbol == '-'){
    return &AffixPossibilities['-'];
  }
  else if(operatorSymbol == '*'){
    return &AffixPossibilities['*'];
  }
  else if(operatorSymbol == '/'){
    return &AffixPossibilities['/'];
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator detected");
  }
}

int checkOperatorsAffixPossibilities(Token *currToken, Tokenizer *nextTokens){
  if(currToken->type == TOKEN_OPERATOR_TYPE){
    currTokenInfo = getTokenInfo(currToken);
    Token *nextToken;
    nextToken = getToken(nextTokens);
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
      nextTokenInfo = getTokenInfo(nextToken);
      
    }
    else{
      throwSimpleError(ERR_INVALID_OPERATOR, "nextToken is not an operator");
    }
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Token is not an operator");
  }

}
