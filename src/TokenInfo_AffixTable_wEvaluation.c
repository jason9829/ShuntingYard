#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define PREFIX_TYPE 4
#define INFIX_TYPE 2
#define SUFFIX_TYPE 1     // Suffix == Postfix

TokenInfo AffixPossibilities[50] = {
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
//   ---------------------------------------------
//  | currOperator | nextOperator| Acceptable (*)| Yes - * / No - Blank
//   ---------------------------------------------
//  |     '+'      |      '+'    |       *       |
//  |     '+'      |      '-'    |       *       |
//  |     '+'      |      '*'    |               |
//  |     '+'      |      '/'    |               |
//  ----------------------------------------------
//  |     '-'      |      '+'    |       *       |
//  |     '-'      |      '-'    |       *       |
//  |     '-'      |      '*'    |               |
//  |     '-'      |      '/'    |               |
//  ----------------------------------------------
//  |     '*'      |      '+'    |       *       |
//  |     '*'      |      '-'    |       *       |
//  |     '*'      |      '*'    |               |
//  |     '*'      |      '/'    |               |
//  ----------------------------------------------
//  |     '/'      |      '+'    |       *       |
//  |     '/'      |      '-'    |       *       |
//  |     '/'      |      '*'    |               |
//  |     '/'      |      '/'    |               |
//  ----------------------------------------------
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

    else{
      // getTokenInfo only accept '+', '-', '*', '/'
      // else error already thrown at getTokenInfo
      throwSimpleError(ERR_INVALID_OPERATOR, "nextToken is not an operator");
    }
  }
  else{
    // getTokenInfo only accept '+', '-', '*', '/'
    // else error already thrown at getTokenInfo
    throwSimpleError(ERR_INVALID_OPERATOR, "Token is not an operator");
  }

}

// This function will compare currOperator and nextOperator the Attribute from AffixPossibilities
int compareCurrTokenAndNextTokenWithTable(TokenInfo *currTokenInfo, TokenInfo *nextTokenInfo){
  if(currTokenInfo->Attribute == 7){         // 4 | 2 | 1 = 7  (refer to #define)
    switch (nextTokenInfo->Attribute) {
      case 7 : return 1;
      case 2 : return 0;
      // getTokenInfo only give 2 or 7
      // else error already thrown at getTokenInfo
      default: throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
    }
  }
  else if(currTokenInfo->Attribute == 2){
    switch (nextTokenInfo->Attribute) {
      case 7 : return 1;
      case 2 : return 0;
      // getTokenInfo only give 2 or 7
      // else error already thrown at getTokenInfo
      default: throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
    }
  }
  // getTokenInfo only give 2 or 7
  // else error already thrown at getTokenInfo
  else{
   throwSimpleError(ERR_INVALID_TOKENINFO, "Invalid attribute from TokenInfo");
  }

}


// If infix pop two TOKEN prefix pop one token
// The function check the affix of first operator token of tokenizer
Affix checkTokenAffix(Tokenizer *tokenizer, Token *prevToken){
  TokenType prevTokenType;
  int  PossibleAffixCombination;

  prevTokenType = prevToken->type;
  Token *nextToken = NULL;

  OperatorType currTokenOperatorType;
  nextToken = getToken(tokenizer);

  // (2)(+) / (2)(-) / (2)(*) / (2)(/)  return operator infix
  if(prevTokenType == TOKEN_FLOAT_TYPE || prevTokenType == TOKEN_INTEGER_TYPE){
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
        encodeAffix(nextToken, INFIX);
        pushBackToken(tokenizer, nextToken);
        return INFIX;
    }
    else{
      pushBackToken(tokenizer, nextToken);
      throwSimpleError(ERR_INVALID_AFFIX, "Invalid affix (currentToken and nextToken is not OperatorType)");
    }
  }

  // For example (+)(-) [(+) is preToken and (-) is nextToken]
  // (-) should be infix
  else if (prevTokenType == TOKEN_OPERATOR_TYPE){
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
      pushBackToken(tokenizer, nextToken);
      PossibleAffixCombination = checkOperatorsAffixPossibilities(prevToken, tokenizer);
      if(PossibleAffixCombination == 1){
          encodeAffix(nextToken, PREFIX);
          return PREFIX;
      }
      else{
        throwSimpleError(ERR_INVALID_AFFIX, "current operator is valid (INFIX or PREFIX) but nextToken is either '*' or '/' (INFIX)");
      }
    } // Example (-)(2) return PREFIX
    else{
      encodeAffix(nextToken, PREFIX);
      pushBackToken(tokenizer, nextToken);
      return PREFIX;
    }

  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator found");
  }
}

// check next Token affix and encode it
// needed to decode it later (getAffixType)
void checkTokenAffixAndEncodeAffix(Tokenizer *tokenizer, Token *prevToken){
  TokenType prevTokenType;
  int  PossibleAffixCombination;

  prevTokenType = prevToken->type;
  Token *nextToken = NULL;

  OperatorType currTokenOperatorType;
  nextToken = getToken(tokenizer);

  // (2)(+) / (2)(-) / (2)(*) / (2)(/)  return operator infix
  if(prevTokenType == TOKEN_FLOAT_TYPE || prevTokenType == TOKEN_INTEGER_TYPE){
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
        encodeAffix(nextToken, INFIX);
        pushBackToken(tokenizer, nextToken);
    }
    else{
      pushBackToken(tokenizer, nextToken);
      throwSimpleError(ERR_INVALID_AFFIX, "Invalid affix (currentToken and nextToken is not OperatorType)");
    }
  }

  // For example (+)(-) [(+) is preToken and (-) is nextToken]
  // (-) should be infix
  else if (prevTokenType == TOKEN_OPERATOR_TYPE){
    if(nextToken->type == TOKEN_OPERATOR_TYPE){
      pushBackToken(tokenizer, nextToken);
      PossibleAffixCombination = checkOperatorsAffixPossibilities(prevToken, tokenizer);
      if(PossibleAffixCombination == 1){
          encodeAffix(nextToken, PREFIX);
      }
      else{
        throwSimpleError(ERR_INVALID_AFFIX, "current operator is valid (INFIX or PREFIX) but nextToken is either '*' or '/' (INFIX)");
      }
    } // Example (-)(2) return PREFIX
    else{
      encodeAffix(nextToken, PREFIX);
      pushBackToken(tokenizer, nextToken);
    }

  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator found");
  }
}
// No need
/*
OperatorType determineOperatorType(Affix tokenAffix){
  if(tokenAffix == INFIX){
    return BINARY;
  }
  else if (tokenAffix == PREFIX || tokenAffix == SUFFIX){
    return UNARY;
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR_TYPE, "No affix founded");
  }
}
*/


// This function will combine the prefix and the number together
// For example, (-)(2)---->(-2)
Token *combinePrefixWithToken(Tokenizer *tokenizer, Token *prefixToken){
  Token *nextToken;
  char  prefixSymbol;

  if(prefixToken->type == TOKEN_OPERATOR_TYPE){
    prefixSymbol = *((OperatorToken*)prefixToken)->str;
    nextToken = getToken(tokenizer);
    // If nextToken is numbers then do the operation else throw error
    if(nextToken->type == TOKEN_INTEGER_TYPE || nextToken->type == TOKEN_FLOAT_TYPE){
      switch(nextToken->type){
        case TOKEN_INTEGER_TYPE : if(prefixSymbol == '+'){
                                    return nextToken;
                                  }
                                  else if (prefixSymbol == '-'){
                                    int operand;
                                    operand = ((IntegerToken*)nextToken)->value;
                                    operand = -operand;
                                    ((IntegerToken*)nextToken)->value = operand;
                                    return nextToken;
                                  }
                                  else{
                                    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator to combine (* or / found)");
                                  }
        case TOKEN_FLOAT_TYPE    : if(prefixSymbol == '+'){
                                    return nextToken;
                                  }
                                  else if (prefixSymbol == '-'){
                                    float operand;
                                    operand = ((FloatToken*)nextToken)->value;
                                    operand = -operand;
                                    ((FloatToken*)nextToken)->value = operand;
                                    return nextToken;
                                  }
                                  else{
                                    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator to combine (* or / found)");
                                  }
          default : throwSimpleError(ERR_INVALID_TOKEN, "Invalid Token to combined");
      }
    }
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR ,"prefixToken is not an operator");
  }
}
