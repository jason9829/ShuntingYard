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
        case 0 : pushBackToken(nextTokens, nextToken);
                 return 0;
        case 1 : pushBackToken(nextTokens, nextToken);
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

// The function check the affix of first operator token of tokenizer
Affix checkTokenAffix(Tokenizer *tokenizer){
  int  compareWithTableResult;
  char currOperatorSymbol;
  char nextOperatorSymbol;

  Token *currToken = NULL;
  Token *nextToken = NULL;

  TokenInfo *currTokenInfo;
  TokenInfo *nextTokenInfo;

  OperatorType currTokenOperatorType;
  currTokenOperatorType = determinieOperatorType(tokenizer);
  currToken = getToken(tokenizer);

  if(currToken ->type == TOKEN_OPERATOR_TYPE){
    currOperatorSymbol = *((OperatorToken*)currToken)->str;
    nextToken = getToken(tokenizer);
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
    nextOperatorSymbol = *((OperatorToken*)nextToken)->str;
    }
    currTokenInfo = getTokenInfo(currToken);

    switch (nextToken->type) {
      case TOKEN_INTEGER_TYPE   : pushBackToken(tokenizer, nextToken);
                                  pushBackToken(tokenizer, currToken);
                                  return PREFIX;
      case TOKEN_FLOAT_TYPE     : pushBackToken(tokenizer, nextToken);
                                  pushBackToken(tokenizer, currToken);
                                  return PREFIX;
      case TOKEN_OPERATOR_TYPE  : nextTokenInfo = getTokenInfo(nextToken);
                                  compareWithTableResult = compareCurrTokenAndNextTokenWithTable(currTokenInfo, nextTokenInfo);
                                  if(compareWithTableResult == 1){
                                    pushBackToken(tokenizer, nextToken);
                                    pushBackToken(tokenizer, currToken);
                                    return INFIX;
                                   }
                                  else{
                                    pushBackToken(tokenizer, nextToken);
                                    pushBackToken(tokenizer, currToken);
                                    throwSimpleError(ERR_INVALID_AFFIX, "Invalid affix found (nextToken is either '*' or '/') ");
                                  }

      default:   throwSimpleError(ERR_WRONG_TOKENTYPE, "Tokentype was wrong");
    }
  }/*
  else if (currToken ->type == TOKEN_INTEGER_TYPE || currToken ->type == TOKEN_FLOAT_TYPE){
    Token *nextNextToken;
    nextToken = getToken(tokenizer);
    switch (nextToken->type) {
      case TOKEN_INTEGER_TYPE   : pushBackToken(nextToken, tokenizer);
                                  throwSimpleError(ERR_WRONG_TOKENTYPE, "Expected an operator but integer was found");
      case TOKEN_FLOAT_TYPE     : pushBackToken(nextToken, tokenizer);
                                  throwSimpleError(ERR_WRONG_TOKENTYPE, "Expected an operator but float was found");
      case TOKEN_OPERATOR_TYPE  : pushBackToken(nextToken, tokenizer);
                                  return SUFFIX;
      default:   throwSimpleError(ERR_WRONG_TOKENTYPE, "Tokentype was wrong");
    }
  }*/
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator found");
  }
}

OperatorType determinieOperatorType(Tokenizer *tokenizer){
  Token *token_1;
  Token *token_2;
  Token *token_3;

  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  token_3 = getToken(tokenizer);

  if(token_1 ->type == TOKEN_INTEGER_TYPE || token_1 ->type == TOKEN_FLOAT_TYPE){
    if(token_2 ->type == TOKEN_OPERATOR_TYPE){
        if(token_3 ->type != TOKEN_NULL_TYPE){
        pushBackToken(tokenizer, token_3);
        }
        pushBackToken(tokenizer, token_2);
        pushBackToken(tokenizer, token_1);
        return BINARY;
    }
  }
  else{
    pushBackToken(tokenizer, token_3);
    pushBackToken(tokenizer, token_2);
    pushBackToken(tokenizer, token_1);
    return UNARY;
  }
}

/*
int numberOfOperatorTokenInTokenizer(Tokenizer *tokenizer){
  Token *token = NULL;
  int numberOfOperatorToken = 0;
  int pushBackCounter = 0;
  token = getToken(tokenizer);

  if(token->type == TOKEN_NULL_TYPE){
    throwSimpleError(ERR_NULL_TOKEN, "Null token detected");
  }
  else if(token->type == TOKEN_OPERATOR_TYPE){
    numberOfOperatorToken++;
    while(getToken(tokenizer)->type == TOKEN_OPERATOR_TYPE){
      numberOfOperatorToken++;
    }
    pushBackCounter = numberOfOperatorToken;
    while(pushBackCounter !=0){
      pushBackToken(token, tokenizer);
    }

    return numberOfOperatorToken;
  }
  else{
    return 0;
  }

}
*/
