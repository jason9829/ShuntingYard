#include "unity.h"
#include "ShuntingYard.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"

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

void test_calculationOnTokens_given_2_plus_2_expect_4(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            ;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2 +2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(4,((IntegerToken*)Ans)->value);

}


void test_calculationOnTokens_given_2_minus_2_expect_0(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            ;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2-  2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(0,((IntegerToken*)Ans)->value);

}

void test_calculationOnTokens_given_2_multiply_3_expect_6(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            ;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2 *    3");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(6,((IntegerToken*)Ans)->value);

}

void test_calculationOnTokens_given_2_div_2_expect_1(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            ;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2 /2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(1,((IntegerToken*)Ans)->value);

}
