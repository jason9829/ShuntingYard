#include "unity.h"
#include "OperatorPrecedence_wTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "Common.h"
#include "Exception.h"
#include "CException.h"
#include "Error.h"

void setUp(void){}
void tearDown(void){}

// plus and minus sign has the same binding power
void test_getTokenPrecedence_given_plus_sign_expect_1(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  precedence = getTokenPrecedence(token);

  TEST_ASSERT_EQUAL(1, precedence->bindingPower);
}

void test_getTokenPrecedence_given_plus_1_expect_1(void){
  Token *token = NULL;
  Token *nextToken = NULL;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("+1");
  token = getToken(tokenizer);

  precedence = getTokenPrecedence(token);

  TEST_ASSERT_EQUAL(1, precedence->bindingPower);
}

// multiply and divide sign has the same binding power
void test_getTokenPrecedence_given_divide_sign_expect_2(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("/");
  token = getToken(tokenizer);


  precedence = getTokenPrecedence(token);
  TEST_ASSERT_EQUAL(2, precedence->bindingPower);

}

void test_getTokenPrecedence_given_a_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("a");
  token = getToken(tokenizer);

  Try{
      precedence = getTokenPrecedence(token);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
    }
      Catch(e){
      dumpTokenErrorMessage(e, 1);
      TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
    }

}

void test_comparePrevTokenAndNextTokenPrecedence_given_plus_and_multiply_expect_0(void){
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("+*");

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);

  ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);

  TEST_ASSERT_EQUAL(0, ans);
}

void test_comparePrevTokenAndNextTokenPrecedence_given_divide_and_minus_expect_1(void){
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("/-");

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);
  ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);

  TEST_ASSERT_EQUAL(1, ans);
}

void test_comparePrevTokenAndNextTokenPrecedence_given_plus_and_plus_expect_2(void){
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("++");

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);
  ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);

  TEST_ASSERT_EQUAL(2, ans);
}
