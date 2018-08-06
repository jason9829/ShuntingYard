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

Token *shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  StackItem *poppedToken_1;
  StackItem *poppedToken_2;
  StackItem *poppedToken_operator;

  OperatorType tokenOperatorType;
  Affix operatorAffix;
  Token *token;
  Token *prevToken;
  Token *token_1;
  Token *token_2;
  Token *token_operator;
  Token *ans;
  TokenType operatorType;

  token = getToken(tokenizer);
  while(token-> type != TOKEN_NULL_TYPE){
    if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      if(operandStack->head == NULL){
        pushOperandStack(operandStack, token);
        token = getToken(tokenizer);
      }
      else if(tokenOperatorType == BINARY){
        pushOperandStack(operandStack, token);
        ans = operationOnStacks(operatorStack, operandStack);
        return ans;
      }
    }
    else{
      if(operandStack->head != NULL){
        prevToken = (Token*)(operandStack->head->data);
        pushBackToken(tokenizer, token);
        tokenOperatorType = determineTokenOperatorType(tokenizer, prevToken);
        token = getToken(tokenizer);
        operatorType = getTokenType(token);
        token->type = operatorType;
        pushOperatorStack(operatorStack, token);
        token = getToken(tokenizer);
      }
    }
  }
}

Token *operationOnStacks(StackBlock *operatorStack, StackBlock *operandStack){
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
      ans = calculationOnTokens(token_1, token_2, token_operator);
      pushStack(operandStack, ans);
      return ans;
    }
    else{
      throwSimpleError(ERR_STACK_INSUFFICIENT, "Either count in operatorStack or operandStack is insufficient to operate");
    }
}

void pushOperandStack(StackBlock *operandStack, Token *token){
  pushStack(operandStack, token);
}

void pushOperatorStack(StackBlock *operatorStack, Token *token){
  pushStack(operatorStack, token);
}

OperatorType determineTokenOperatorType(Tokenizer *tokenizer, Token *prevToken){
  Affix tokenAffix;
  OperatorType tokenOperatorType;

  tokenAffix = checkTokenAffix(tokenizer, prevToken);
  tokenOperatorType = determineOperatorType(tokenAffix);
  return tokenOperatorType;
}
