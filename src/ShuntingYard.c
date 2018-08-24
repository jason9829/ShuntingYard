#include "ShuntingYard.h"
#include "Arithmetic.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include "Common.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "OperatorPrecedence_wTable.h"

#include <stdio.h>
#include <stdlib.h>

#define START 1
#define STOP 0

void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Token *token;
  Token *prevToken;
  TokenType prevTokenType;
  prevTokenType = TOKEN_NULL_TYPE;

  int condition = START;
  int openBracketCounter = 0 ;
  int closeBracketCounter = 0 ;

  while(condition == START){
    token = getToken(tokenizer);

    if(!isTokenValid(token, prevTokenType) && token->type != TOKEN_NULL_TYPE){
      throwException(ERR_INVALID_TOKEN, token, "'%s' should not be here", token->str);
    }

    if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      pushOperandStack(operandStack, token);
      prevTokenType = getTokenType(token);
      prevToken = token;
      continue;
    }

    else if (token->type == TOKEN_OPERATOR_TYPE){
      noOperatorBetweenBrackets(token ,prevToken);
      if(isOpenBracketToken(token)){
        openBracketCounter +=1;
      }
      if(isClosingBracketToken(token)){
        closeBracketCounter +=1;
      }
      closeBracketFoundButNoOpenBracket(token, openBracketCounter, closeBracketCounter);
      encodeTokenAffix(token, prevToken, tokenizer, prevTokenType);
      pushIfprevTokenIsOpenBracket(operatorStack, token);

      if(openBracketCounter!=0 && isClosingBracketToken(token)){
        operateIfBracket(operatorStack, operandStack, token);
        openBracketCounter -=1;
        closeBracketCounter -=1;
      }
		  pushOperator(operatorStack, operandStack, token);
      prevTokenType = getTokenType(token);
      prevToken = token;
      }

    else{
      ifNullTokenOperateUntilOperatorStackIsEmpty(operatorStack, operandStack, token);
      matchBracket(token,openBracketCounter ,closeBracketCounter);
      condition = STOP;
      freeToken(prevToken);
      freeToken(token);
      freeTokenizer(tokenizer);
    }
  }
}

// This function will thrown an error when ')' was found and there is no '('
void closeBracketFoundButNoOpenBracket(Token *token,int openBracketCounter, int closeBracketCounter){
  if(openBracketCounter == 0 && closeBracketCounter !=0){
    throwException(ERR_MISSING_BRACKET, token, "Expecting '(' before '%s'", token->str);
  }
}

// This function will throw an exception when there is not '+', '-' ,'*' or '/'
//          ) (
//   --------^
void noOperatorBetweenBrackets(Token *token, Token *prevToken){
 char prevTokenOperator;
 char currTokenOperator;
 TokenType prevTokenType;
 TokenType currTokenType;

 prevTokenType = getTokenType(prevToken);
 currTokenType = getTokenType(token);

 if(currTokenType == TOKEN_OPERATOR_TYPE && prevTokenType == TOKEN_OPERATOR_TYPE){
   prevTokenOperator = *((OperatorToken*)prevToken)->str;
   currTokenOperator = *((OperatorToken*)token)->str;
   if(prevTokenOperator == ')' && currTokenOperator == '('){
     throwException(ERR_MISSING_OPERATOR, prevToken, "Expecting an operation operator after here '%s'", prevToken->str);
   }
 }

}

void matchBracket(Token *token,int openBracketCounter, int closeBracketCounter){
  if(openBracketCounter !=0 && (openBracketCounter!=closeBracketCounter)){
    throwException(ERR_MISSING_BRACKET,token, "Expecting ')' but not found");
  }

  else if(closeBracketCounter !=0 && (openBracketCounter !=closeBracketCounter)){
    throwException(ERR_MISSING_BRACKET,token, "Expecting '(' but not found");
  }
}

// Assume open bracket is already found
void operateIfBracket(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  if(operatorStack->count !=0){
    Token *headOp = (Token*)(operatorStack->head->data);
    if(((OperatorToken*)headOp)->str[0] != '('){
      Token *headOperatorToken;
      Affix headOperatorAffix;
      if(isClosingBracketToken(token)){
        while(operatorStack->count != 0 && !isOpenBracketToken((Token*)(operatorStack->head->data))){
          headOperatorToken = (Token*)(operatorStack->head->data);
          headOperatorAffix = getAffix(headOperatorToken);
          operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
        }
        cancelBracket(operatorStack, token);
      }
    }
  }
}

void pushIfCurrentOpenBracket(StackBlock *operatorStack, Token *token){
    if(operatorStack->count !=0){
      char operatorSymbol;
      Token *headOperatorToken;
      headOperatorToken = (Token*)(operatorStack->head->data);
      // HeadTokenIsInfix
        if(headOperatorToken != token){
          operatorSymbol = *((OperatorToken*)token)->str;
          if(operatorSymbol == '('){
            pushOperatorStack(operatorStack, token);
          }
        }
      }
}

void pushIfprevTokenIsOpenBracket(StackBlock *operatorStack, Token *token){
  if(isClosingBracketToken(token)){
    cancelBracket(operatorStack,token);
  }
  else if (operatorStack->count !=0 && (Token*)(operatorStack->head->data) != token && isOpenBracketToken((Token*)(operatorStack->head->data))){
		pushOperatorStack(operatorStack, token);
	}
}

void cancelBracket(StackBlock *operatorStack, Token *token){
  if(operatorStack->count != 0 && (Token*)(operatorStack->head->data) != token && isOpenBracketToken((Token*)(operatorStack->head->data)) && isClosingBracketToken(token)){
  popStack(operatorStack);
  //freeToken(token);
  }
}

void pushOperator(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
    if(!isClosingBracketToken(token)){
      pushIfOperatorStackIsEmpty(operatorStack, token);
      //pushIfprevTokenIsOpenBracket(operatorStack, token);
      pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(operatorStack, token);
      pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(operatorStack,operandStack, token);
      operateIfHeadTokenOfStackIsHigherPrecedence(operatorStack, operandStack, token);
      pushIfCurrentOpenBracket(operatorStack, token);
    }

}

void operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;
  Affix headOperatorAffix;
  Token *headOperatorToken;

  if(operatorStack->count !=0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(headOperatorToken);
    currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token);
    headOperatorAffix = getAffix(headOperatorToken);

  if(areAssociativitiesSame(headOperatorAndAssociativity, currentOperatorAndAssociativity)){
      if((headOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT && currentOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT) && ((headOperatorAndAssociativity-> bindingPower == currentOperatorAndAssociativity-> bindingPower))){
          operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
      }
    }
  }

}


void ifNullTokenOperateUntilOperatorStackIsEmpty(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  Affix headOperatorAffix;
  Token *headOperatorToken;
  char operatorSymbol;
  if(token->type == TOKEN_NULL_TYPE){
    while(operatorStack->count !=0 && operatorSymbol != '(' && operatorSymbol != ')'){
      headOperatorToken = (Token*)operatorStack->head->data;
      headOperatorAffix = getAffix(headOperatorToken);
      operatorSymbol = *((OperatorToken*)headOperatorToken)->str;
      if(operatorSymbol != '(' && operatorSymbol != ')'){
          operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
      }

    }
  }

}

// comparePrevTokenAndNextTokenPrecedence == 1 (headToken Higher)
//                                        == 2 equal
//                                        == 0 (headToken lower)
void operateIfHeadTokenOfStackIsHigherPrecedence(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  Token *headOperatorToken;
  char headOperatorSymbol;
  Affix headOperatorAffix;
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;

  if(((Token*)(operatorStack->head->data) != token) && !isClosingBracketToken(token) && !isOpenBracketToken(token)){
      while(operatorStack->count !=0 && (comparePrevTokenAndNextTokenPrecedence(token, (Token*)(operatorStack->head->data)) == 1 )){
        headOperatorAffix = getAffix(headOperatorToken);
        if(operatorStack->count ==0){
          pushOperatorStack(operatorStack,token);
        }
        operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
        if(operatorStack->count !=0){
          headOperatorToken = (Token*)operatorStack->head->data;
          headOperatorSymbol = *((OperatorToken*)headOperatorToken)->str;
          if(headOperatorSymbol != '(' && headOperatorSymbol != ')'){
            headOperatorAffix = getAffix(headOperatorToken);
          }
        }
      }
      pushIfprevTokenIsOpenBracket(operatorStack, token);
      pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(operatorStack, operandStack, token);
      pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(operatorStack, token);
      pushIfOperatorStackIsEmpty(operatorStack, token);
    }
  }


void pushIfOperatorStackIsEmpty(StackBlock *operatorStack, Token *token){
  if(operatorStack->count == 0){
    pushOperatorStack(operatorStack, token);
  }
}

void pushIfOperandStackIsEmpty(StackBlock *operandStack, Token *token){
  if(operandStack->count == 0){
    pushOperandStack(operandStack, token);
  }
}

// Check for Associativity (depend on affix) if same return 1
int areAssociativitiesSame(OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity, OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity){
  if(headOperatorAndAssociativity->associativity == currentOperatorAndAssociativity->associativity){
    return 1;
  }
  else{
    return 0;
  }
}

// Example
//               (+) - PREFIX
//
//     +----+
//    |  +  |   -- PREFIX
//    +----+
// For this case the precedence are the same so it will push the (+) operator
void pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(StackBlock *operatorStack,StackBlock *operandStack, Token *token){
  Affix affixOfHeadOperatorToken;
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;
  Token *headOperatorToken;
  TokenType prevTokenType;

  if(!isClosingBracketToken(token) && !isOpenBracketToken(token) && operatorStack->count != 0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    //prevTokenType = getTokenType(headOperatorToken);
    headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(headOperatorToken);
    currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token);

    // HeadTokenIsInfix
      if(headOperatorToken != token){
        if (comparePrevTokenAndNextTokenPrecedence(token, headOperatorToken) == 2){
            operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(operatorStack, operandStack, token);
            pushOperatorStack(operatorStack, token);
          }
      }
  }
}

/*
 *  affixOfCurrentToken         Associativity
 *      PREFIX                  RIGHT-TO-LEFT
 *      INFIX                   LEFT-TO-RIGHT
 *      SUFFIX                  LEFT-TO-RIGHT
 */
Associativity getTokenAssociativity(Token *currentToken){
  Affix affixOfCurrentToken;

  affixOfCurrentToken = getAffix(currentToken);

  if(affixOfCurrentToken == PREFIX){
    return RIGHT_TO_LEFT;
  }
  else if(affixOfCurrentToken == INFIX){
    return LEFT_TO_RIGHT;
  }
  else if(affixOfCurrentToken == SUFFIX){
    return LEFT_TO_RIGHT;
  }
  else{
    throwException(ERR_INVALID_AFFIX, currentToken, "'%s' has an invalid affix, it should not be here", currentToken->str);
  }
}

//  Example
//               (+) - PREFIX
//
//     +----+
//    |  +  |   -- INFIX
//    +----+
// For this case the precedence of head of Stack is lower, thus the PREFIX (-) will be pushed
void pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(StackBlock *operatorStack, Token *token){
  Affix affixOfHeadOperatorToken;
  Token *headOperatorToken;
  TokenType prevTokenType;

  if(operatorStack->count !=0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    prevTokenType = getTokenType(headOperatorToken);
    affixOfHeadOperatorToken = getAffix(token);
    // HeadTokenIsInfix
      if(headOperatorToken != token){
        if(!operatorStackHeadIsPrefix(operatorStack)){
          if(!comparePrevTokenAndNextTokenPrecedence(token, headOperatorToken)){  // If 1 mean headOperator is higher precedence
             pushOperatorStack(operatorStack, token);
          }
        }
    }
  }
}

int operatorStackHeadIsPrefix(StackBlock *operatorStack){
  Affix affixOfHeadOperatorToken;
  affixOfHeadOperatorToken = getAffix((Token*)(operatorStack->head->data));

  if(affixOfHeadOperatorToken != PREFIX){
    return 0;
  }
  else{
    return 1;
  }
}

int operatorStackHeadIsInfix(StackBlock *operatorStack){
  Affix affixOfHeadOperatorToken;
  affixOfHeadOperatorToken = getAffix((Token*)(operatorStack->head->data));

  if(affixOfHeadOperatorToken != INFIX){
    return 0;
  }
  else{
    return 1;
  }
}

// checking the validity of Token
int isTokenValid(Token *token, TokenType lastTokenType){
  if(token->type == TOKEN_FLOAT_TYPE || token->type == TOKEN_INTEGER_TYPE){
    switch (lastTokenType) {
      case TOKEN_NULL_TYPE     : return 1;
      case TOKEN_OPERATOR_TYPE : return 1;
      default : return 0;
    }
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    switch (lastTokenType) {
      case TOKEN_NULL_TYPE      : return 1;
      case TOKEN_INTEGER_TYPE   : return 1;
      case TOKEN_FLOAT_TYPE     : return 1;
      case TOKEN_OPERATOR_TYPE  : return 1;
      default : return 0;
    }
  }
  else{
    return 0;
  }
}

int isOpenBracketToken(Token *token){
  char TokenSymbol;
  TokenSymbol = *((OperatorToken*)token)->str;

  if(TokenSymbol == '('){
    return 1;
  }
  else{
    return 0;
  }
}

int isClosingBracketToken(Token *token){
  char TokenSymbol;
  TokenSymbol = *((OperatorToken*)token)->str;

  if(TokenSymbol == ')'){
    return 1;
  }
  else{
    return 0;
  }
}

// This function will choose what operation to do depend the affix
void operateOnStacksDependOnAffix(StackBlock *operatorStack, StackBlock *operandStack, Affix affix){
  Token *ans;
  switch (affix) {
    case INFIX  : ans = operationOnStacksIfOperatorIsInfix(operatorStack,  operandStack);
                  pushOperandStack(operandStack, ans);
                  break;
    case PREFIX : ans = operationOnStacksIfOperatorIsPrefix(operatorStack, operandStack);
                  pushOperandStack(operandStack, ans);
                  break;
  }
}

Token *operationOnStacksIfOperatorIsPrefix(StackBlock *operatorStack, StackBlock *operandStack){
  StackItem *poppedToken_1;
  StackItem *poppedToken_operator;

  Token *token_1;
  Token *token_operator;
  Token *ans;

  if(operatorStack->count >=1 && operandStack->count >=1){
    poppedToken_1 = popStack(operandStack);
    poppedToken_operator = popStack(operatorStack);
    token_1 = (Token*)(poppedToken_1->data);
    token_operator = (Token*)(poppedToken_operator->data);
    ans = combinePrefixWithOperandToken(token_operator, token_1);
    //freeToken(token_1);
    //freeToken(token_operator);
    return ans;
  }
  else{
    throwException(ERR_STACK_INSUFFICIENT, operandStack->head->data, "Only '%d' operator and '%d' operand was found, thus no operation can be done", operatorStack->count, operandStack->count);
  }

}

Token *operationOnStacksIfOperatorIsInfix(StackBlock *operatorStack, StackBlock *operandStack){
    StackItem *poppedToken_1;
    StackItem *poppedToken_2;
    StackItem *poppedToken_operator;

    Token *token_1;
    Token *token_2;
    Token *token_operator;
    Token *ans;

    if(operatorStack->count >=1 && operandStack->count >=2){
      poppedToken_1 = popStack(operandStack);
      poppedToken_2 = popStack(operandStack);
      poppedToken_operator = popStack(operatorStack);
      token_1 = (Token*)(poppedToken_1->data);
      token_2 = (Token*)(poppedToken_2->data);
      token_operator = (Token*)(poppedToken_operator->data);
      ans = calculationOnTokens(token_2, token_1, token_operator);
      //freeToken(token_1);
      //freeToken(token_2);
      //freeToken(token_operator);
      //pushStack(operandStack, ans);
      return ans;
    }
    else{
      throwException(ERR_STACK_INSUFFICIENT, operandStack->head->data,  "Only '%d' operator and '%d' operand was found, thus no operation can be done", operatorStack->count, operandStack->count);
    }
}

void pushOperandStack(StackBlock *operandStack, Token *token){
  pushStack(operandStack, token);
}

void pushOperatorStack(StackBlock *operatorStack, Token *token){
  pushStack(operatorStack, token);
}
