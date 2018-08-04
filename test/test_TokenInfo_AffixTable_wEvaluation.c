#include "unity.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"

void setUp(void){}
void tearDown(void){}

void test_getTokenInfo_given_plus_sign_expect_attribute_7(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  TokenInfo *affix = NULL;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(7, affix->Attribute);
}
void test_getTokenInfo_given_minus_sign_expect_attribute_7(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  TokenInfo *affix = NULL;

  tokenizer = createTokenizer("-");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(7, affix->Attribute);
}
void test_getTokenInfo_given_multiply_sign_expect_attribute_7(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  TokenInfo *affix = NULL;

  tokenizer = createTokenizer("*");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(2, affix->Attribute);
}
void test_getTokenInfo_given_divide_sign_expect_attribute_7(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  TokenInfo *affix = NULL;

  tokenizer = createTokenizer("/");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(2, affix->Attribute);
}

void test_getTokenInfo_given_abc_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  TokenInfo *affix = NULL;

  tokenizer = createTokenizer("abc");
  token = getToken(tokenizer);


  Try{
    affix = getTokenInfo(token);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
    freeError(e);
  }

}
void test_checkOperatorsAffixPossibilities_given_plus_and_plus_expect_TRUE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ +");
  token = getToken(tokenizer);


  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

// TokenInfo = (7) -------------> PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE = 7
void test_compareCurrTokenAndNextTokenWithTable_given_TokenInfo_7_and_7_expect_TRUE_1(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  TokenInfo *tokenInfo_1 = NULL;
  TokenInfo *tokenInfo_2 = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ +");
  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  tokenInfo_1 = getTokenInfo(token_1);
  tokenInfo_2 = getTokenInfo(token_2);

  result = compareCurrTokenAndNextTokenWithTable(tokenInfo_1, tokenInfo_2);
  TEST_ASSERT_EQUAL(1, result);
}

void test_compareCurrTokenAndNextTokenWithTable_given_TokenInfo_7_and_2_expect_FALSE_0(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  TokenInfo *tokenInfo_1 = NULL;
  TokenInfo *tokenInfo_2 = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ /");
  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  tokenInfo_1 = getTokenInfo(token_1);
  tokenInfo_2 = getTokenInfo(token_2);

  result = compareCurrTokenAndNextTokenWithTable(tokenInfo_1, tokenInfo_2);
  TEST_ASSERT_EQUAL(0, result);
}

void test_compareCurrTokenAndNextTokenWithTable_given_TokenInfo_2_and_7_expect_TRUE_1(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  TokenInfo *tokenInfo_1 = NULL;
  TokenInfo *tokenInfo_2 = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("*-");
  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  tokenInfo_1 = getTokenInfo(token_1);
  tokenInfo_2 = getTokenInfo(token_2);

  result = compareCurrTokenAndNextTokenWithTable(tokenInfo_1, tokenInfo_2);
  TEST_ASSERT_EQUAL(1, result);
}

void test_compareCurrTokenAndNextTokenWithTable_given_TokenInfo_2_and_2_expect_FALSE_0(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  TokenInfo *tokenInfo_1 = NULL;
  TokenInfo *tokenInfo_2 = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("/*");
  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  tokenInfo_1 = getTokenInfo(token_1);
  tokenInfo_2 = getTokenInfo(token_2);

  result = compareCurrTokenAndNextTokenWithTable(tokenInfo_1, tokenInfo_2);
  TEST_ASSERT_EQUAL(0, result);
}
