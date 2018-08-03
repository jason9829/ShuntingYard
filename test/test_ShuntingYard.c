#include "unity.h"
#include "ShuntingYard.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"

#include <stdarg.h>
#include <stdio.h>


void setUp(void){}
void tearDown(void){}
/*
void test_operateOnTokens_given_1_plus_2_exptect_3(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            = NULL;
  Tokenizer *tokenizer  = NULL;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer(" 1 +2");

  token_1 = getToken(tokenizer);
  pushStack(&operandStack, token_1);
  token_operator = getToken(tokenizer);
  pushStack(&operatorStack, token_operator);
  token_2 = getToken(tokenizer);
  pushStack(&operandStack, token_2);

  Ans = operateOnTokens(operatorStack, operandStack);
}*/
