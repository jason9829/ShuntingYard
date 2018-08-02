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

void test_calculationOnTokens_given_2_plus_2_expect_4(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            = NULL;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2 +2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(4,((IntegerToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10_plus_10_expect_20(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;

  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10+10");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = additionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(20,((IntegerToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10point123_plus_10point123_expect_20point246(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.123 +10.123");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = additionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(20.246,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10point123_plus_10_expect_20point123(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.123 +10");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = additionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(20.123,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10_plus_10point999_expect_20point999(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer("  10 + 10.999");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = additionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(20.999,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_abcd_and_4124aaexpect_ERR_INVALID_OPERAND(void){
  CEXCEPTION_T e;

  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer("  abcd + 4124");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Try{
      Ans = additionOf2Tokens(token_1, token_2);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERAND. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, e->errorCode);
    freeError(e);
  }

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
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}
void test_subtractionOf2Tokens_given_10_minus_10_expect_0(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;

  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10- 10");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = subtractionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(0,((IntegerToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}


void test_additionOf2Tokens_given_10point123_minus_10_expect_0point123(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.123 -10");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = subtractionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(0.123,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10point123_minus_negative_12point123_expect_negative2(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.123 -12.123");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = subtractionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(-2,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_10_minus_1point12_expect_8point88(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10 -1.12");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = subtractionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(8.88,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

/*
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

void test_calculationOnTokens_given_2point123_plus_2_expect_4point123(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Token *Ans            ;
  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer(" 2.12+ 2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  Ans = calculationOnTokens(token_1, token_2, token_operator);

  TEST_ASSERT_EQUAL(4.123,((FloatToken*)Ans)->value);

}
*/
