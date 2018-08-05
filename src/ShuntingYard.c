#include "ShuntingYard.h"
#include "Arithmetic.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include "Common.h"
#include <stdio.h>

Token *shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
    StackItem *poppedToken_1;
    StackItem *poppedToken_2;
    StackItem *poppedToken_operator;

    Token *token;
    Token *token_1;
    Token *token_2;
    Token *token_operator;
    Token *ans;

    token = getToken(tokenizer);
    while(token-> type != TOKEN_NULL_TYPE){
      if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      pushOperandStack(operandStack, token);
      token = getToken(tokenizer);
      }
      else{
      pushOperatorStack(operatorStack, token);
      token = getToken(tokenizer);
      }
    }

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
}

void pushOperandStack(StackBlock *operandStack, Token *token){
  pushStack(operandStack, token);
}

void pushOperatorStack(StackBlock *operatorStack, Token *token){
  pushStack(operatorStack, token);
}
