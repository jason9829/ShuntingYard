#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define PREFIX_TYPE 4
#define INFIX_TYPE 2
#define SUFFIX_TYPE 1     // Suffix == Postfix

TokenInfo AffixPossibilities[100] = {
  ['+'] = {.Attribute = PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE},
  ['-'] = {.Attribute = PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE},
  ['*'] = {.Attribute = INFIX_TYPE},
  ['/'] = {.Attribute = INFIX_TYPE},
};
// If operator is '+', '-' , '*' or '/' return the
// affix possibilities (in int) else throw error
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

// This function will check currrent operator and next operator possibilities
// The following table show the AffixPossibilities
//   --------------------------------------------------------
//  | currOperator | nextOperator| Unary (*)   | Binary (*) | Yes - * / No - Blank
//   --------------------------------------------------------
//  |     '+'      |      '+'    |      *      |      *     |
//  |     '+'      |      '-'    |      *      |      *     |
//  |     '+'      |      '*'    |             |            |
//  |     '+'      |      '/'    |             |            |
//  ---------------------------------------------------------
//  |     '-'      |      '+'    |      *      |      *      |
//  |     '-'      |      '-'    |      *      |      *      |
//  |     '-'      |      '*'    |             |             |
//  |     '-'      |      '/'    |             |             |
//  ----------------------------------------------------------
//  |     '*'      |      '+'    |      *      |             |
//  |     '*'      |      '-'    |      *      |             |
//  |     '*'      |      '*'    |             |             |
//  |     '*'      |      '/'    |             |             |
//  ---------------------------------------------------------
//  |     '/'      |      '+'    |      *      |             |
//  |     '/'      |      '-'    |      *      |             |
//  |     '/'      |      '*'    |             |             |
//  |     '/'      |      '/'    |             |             |
//  ----------------------------------------------------------
int checkOperatorsAffixPossibilities(Token *currToken, Tokenizer *nextTokens){
  int compareWithTableResult;
  Token *nextToken;
  TokenInfo *currTokenInfo;
  TokenInfo *nextTokenInfo;

  if(currToken->type == TOKEN_OPERATOR_TYPE){
    currTokenInfo = getTokenInfo(currToken);
    nextToken = getToken(nextTokens);

    if(nextToken->type == TOKEN_OPERATOR_TYPE){
      nextTokenInfo = getTokenInfo(nextToken);
      compareWithTableResult = compareCurrTokenAndNextTokenWithTable(currTokenInfo, nextTokenInfo);

      switch (compareWithTableResult) {
        case 0 : pushBackToken(nextToken, nextTokens);
                 return 0;
        case 1 : pushBackToken(nextToken, nextTokens);
                 return 1;
        // compareCurrTokenAndNextTokenWithTable only return 1 or 0
        // else error will be thrown in getTokenInfo
        //default : throwSimpleError(ERR_INVALID_ANSWER, "Invalid answer from compareCurrTokenAndNextTokenWithTable");
      }
    }
    /*
    else{
      // getTokenInfo only accept '+', '-', '*', '/'
      // else error already thrown at getTokenInfo
      throwSimpleError(ERR_INVALID_OPERATOR, "nextToken is not an operator");
    }*/
  } /*
  else{
    // getTokenInfo only accept '+', '-', '*', '/'
    // else error already thrown at getTokenInfo
    throwSimpleError(ERR_INVALID_OPERATOR, "Token is not an operator");
  }*/

}

// This function will compare currOperator and nextOperator the Attribute from AffixPossibilities
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo){
  if(currTokenInfo->Attribute == 7){         // 4 | 2 | 1 = 7  (refer to #define)
    switch (nextTokenInfo->Attribute) {
      case 7 : return 1;
      case 2 : return 0;
      // getTokenInfo only give 2 or 7
      // else error already thrown at getTokenInfo
      //default: throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
    }
  }
  else if(currTokenInfo->Attribute == 2){
    switch (nextTokenInfo->Attribute) {
      case 7 : return 1;
      case 2 : return 0;
      // getTokenInfo only give 2 or 7
      // else error already thrown at getTokenInfo
      //default: throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
    }
  }
  // getTokenInfo only give 2 or 7
  // else error already thrown at getTokenInfo
  //else{
  //  throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
  //}

}

// The function check the affix of currToken
Affix checkTokenAffix(Token *currToken, Tokenizer *nextTokens){
  char operatorSymbol;
  Token *nextToken;
  if(currToken ->type == TOKEN_OPERATOR_TYPE){
    operatorSymbol = *((OperatorToken*)currToken)->str;
    nextToken = getToken(nextTokens);

    switch (nextToken->type) {
      case TOKEN_INTEGER_TYPE   : pushBackToken(nextToken, nextTokens);
                                  return PREFIX;
      case TOKEN_FLOAT_TYPE     : pushBackToken(nextToken, nextTokens);
                                  return PREFIX;
      case TOKEN_OPERATOR_TYPE  : pushBackToken(nextToken, nextTokens);
                                  return INFIX;

      default:   throwSimpleError(ERR_WRONG_TOKENTYPE, "Tokentype was wrong");
    }
  }
  else if (currToken ->type == TOKEN_INTEGER_TYPE || currToken ->type == TOKEN_FLOAT_TYPE){
    Token *nextNextToken;
    nextToken = getToken(nextTokens);
    switch (nextToken->type) {
      case TOKEN_INTEGER_TYPE   : pushBackToken(nextToken, nextTokens);
                                  throwSimpleError(ERR_WRONG_TOKENTYPE, "Expected an operator but integer was found");
      case TOKEN_FLOAT_TYPE     : pushBackToken(nextToken, nextTokens);
                                  throwSimpleError(ERR_WRONG_TOKENTYPE, "Expected an operator but float was found");
      case TOKEN_OPERATOR_TYPE  : pushBackToken(nextToken, nextTokens);
                                  return SUFFIX;
      default:   throwSimpleError(ERR_WRONG_TOKENTYPE, "Tokentype was wrong");
    }
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator found");
  }
}
