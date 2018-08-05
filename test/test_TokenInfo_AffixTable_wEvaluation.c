#include "unity.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "CException.h"
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

void test_checkOperatorsAffixPossibilities_given_plus_and_multiply_expect_TRUE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ -");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_plus_and_minus_expect_FALSE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ *");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_plus_and_divide_expect_FALSE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ /");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_plus_expect_TRUE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("* +");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_minus_expect_TRUE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("* -");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_multiply_expect_FALSE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("* *");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_divide_expect_FALSE(void){
  int result;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("* /");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
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

void test_checkTokenAffix_given_minus_sign_and_2_expect_PREFIX(void){
  Affix affix;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2");

  affix = checkTokenAffix(tokenizer);
  TEST_ASSERT_EQUAL(PREFIX, affix);
}

void test_checkTokenAffix_given_minus_sign_and_2point123_expect_PREFIX(void){
  Affix affix;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2.123");

  affix = checkTokenAffix(tokenizer);
  TEST_ASSERT_EQUAL(PREFIX, affix);
}

void test_checkTokenAffix_given_minus_sign_and_minus_expect_INFIX(void){
  Affix affix;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("--");

  affix = checkTokenAffix(tokenizer);
  TEST_ASSERT_EQUAL(INFIX, affix);
}

void test_checkTokenAffix_given_abc_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Affix affix;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("abc");


  Try{
    affix = checkTokenAffix(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
    freeError(e);
  }
}

void test_checkTokenAffix_given_plus_and_ddd_expect_ERR_WRONG_TOKENTYPE(void){
  CEXCEPTION_T e;
  Affix affix;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+ddd");


  Try{
    affix = checkTokenAffix(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_WRONG_TOKENTYPE. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_WRONG_TOKENTYPE, e->errorCode);
    freeError(e);
  }
}

void test_checkTokenAffix_given_plus_and_multiply_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;

  Tokenizer *tokenizer = NULL;

  // Expected 0x5A5A5A5A Was 0x02771D50. Unhandled Exception!
  // if there is no spacing this error was thrown
  tokenizer = createTokenizer("+*");

  Try{
    affix = checkTokenAffix(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
    freeError(e);
  }
}
void test_determinieOperatorType_given_minus_2_expect_1_UNARY(void){
  Tokenizer *tokenizer = NULL;
  OperatorType ans;
  tokenizer = createTokenizer("-2");
  ans = determinieOperatorType(tokenizer);

  TEST_ASSERT_EQUAL(1, ans);
}
void test_determinieOperatorType_given_2_divide_2_expect_2_BINARY(void){
  Tokenizer *tokenizer = NULL;
  OperatorType ans;
  tokenizer = createTokenizer("2/2");
  ans = determinieOperatorType(tokenizer);

  TEST_ASSERT_EQUAL(2, ans);
}
/*
void test_numberOfOperatorTokenInTokenizer_given_2_plus_sign_expect_2(void){
  int numberOfOperatorToken;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("++");

  numberOfOperatorToken = numberOfOperatorTokenInTokenizer(tokenizer);
  TEST_ASSERT_EQUAL(2, numberOfOperatorToken);
}
*/
