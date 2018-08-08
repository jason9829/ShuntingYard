#include "unity.h"
#include "Arithmetic.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"

void setUp(void){}
void tearDown(void){}

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

  TEST_ASSERT_EQUAL_FLOAT(20.246,((FloatToken*)Ans)->value);
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

  TEST_ASSERT_EQUAL_FLOAT(20.123,((FloatToken*)Ans)->value);
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

  TEST_ASSERT_EQUAL_FLOAT(20.999,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_additionOf2Tokens_given_abcd_and_4124aa_expect_ERR_INVALID_OPERAND(void){
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
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND, e->errorCode);

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


void test_subtractionOf2Tokens_given_10point123_minus_10_expect_0point123(void){
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

  TEST_ASSERT_EQUAL_FLOAT(0.123,((FloatToken*)Ans)->value);
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

  TEST_ASSERT_EQUAL_FLOAT(-2.000,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_subtractionOf2Tokens_given_10_minus_1point12_expect_8point88(void){
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

  TEST_ASSERT_EQUAL_FLOAT(8.88,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

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
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}

void test_multiplicationOf2Tokens_given_10_multiply_2_expect_20(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10 * 2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = multiplicationOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(20,((IntegerToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}
void test_multiplicationOf2Tokens_given_10point5_multiply_2_expect_21(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.5 * 2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = multiplicationOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL_FLOAT(21.0,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_multiplicationOf2Tokens_given_10000_multiply_2point5_expect_25000(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10000 * 2.5");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = multiplicationOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(25000.0,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_multiplicationOf2Tokens_given_10000point1_multiply_2point99_expect_25000(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10000.1 * 2.99");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = multiplicationOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(29900.299,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

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
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}

void test_multiplicationOf2Tokens_given_10_div_2_expect_5(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10 / 2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = divisionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(5,((IntegerToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,Ans->type);

}
void test_divisionOf2Tokens_given_10point222_div_2_expect_5point111(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 10.222 / 2");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = divisionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(5.111,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_divisionOf2Tokens_given_999_div_2point5_expect_808point907(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 999 / 1.235");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = divisionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(808.907,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_divisionOf2Tokens_given_999point99_div_2point99_expect_334point445(void){
  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer(" 999.99 / 2.99");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Ans = divisionOf2Tokens(token_1, token_2);

  TEST_ASSERT_EQUAL(334.445,((FloatToken*)Ans)->value);
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE,Ans->type);

}

void test_calculationOnTokens_given_invalid_operator_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;

  Token *token_1        = NULL;
  Token *token_2        = NULL;
  Token *token_operator = NULL;
  Tokenizer *tokenizer  = NULL;
  Token *Ans            = NULL;


  // no need operator bcz the function is already an addition
  tokenizer = createTokenizer("  123 a; 4124");
  token_1 = getToken(tokenizer);
  token_operator = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  Try{
      Ans = calculationOnTokens(token_1, token_2, token_operator);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }

}
