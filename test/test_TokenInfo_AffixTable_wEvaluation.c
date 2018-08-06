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

void test_checkTokenAffix_given_2_and_minus_sign_expect_INFIX(void){
  Affix affix;
  Affix getAffix_ans;
  Token *token = NULL;
  TokenType prevTokenType;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("2-");
  token = getToken(tokenizer);

  affix = checkTokenAffix(tokenizer, token);
  TEST_ASSERT_EQUAL(INFIX, affix);
  // validation for encoding
  token = getToken(tokenizer);
  getAffix_ans = getAffix(token);
  TEST_ASSERT_EQUAL(INFIX, getAffix_ans);
}

void test_checkTokenAffix_given_minus_sign_and_two_expect_PREFIX(void){
  Affix affix;
  Affix getAffix_ans;
  Token *token = NULL;
  TokenType prevTokenType;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2");
  token = getToken(tokenizer);

  affix = checkTokenAffix(tokenizer, token);
  TEST_ASSERT_EQUAL(PREFIX, affix);

  // validation for encoding
  token = getToken(tokenizer);
  getAffix_ans = getAffix(token);
  TEST_ASSERT_EQUAL(PREFIX, getAffix_ans);
}

void test_checkTokenAffix_given_12_and_12point1_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("12 12.1");
  token = getToken(tokenizer);

  Try{
  affix = checkTokenAffix(tokenizer, token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
  printf(e->errorMsg);
  TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  freeError(e);
  }
}

void test_checkTokenAffix_given_minus_and_divide_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("- /");
  token = getToken(tokenizer);

  Try{
  affix = checkTokenAffix(tokenizer, token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
  printf(e->errorMsg);
  TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  freeError(e);
  }
}

void test_checkTokenAffix_given_minus_sign_and_minus_sign_expect_PREFIX(void){
  Affix affix;
  Affix getAffix_ans;
  Token *token = NULL;
  TokenType prevTokenType;
  Tokenizer *tokenizer = NULL;

  // prevToken is INFIX so nextToken should be prefix
  tokenizer = createTokenizer("++");
  token = getToken(tokenizer);

  affix = checkTokenAffix(tokenizer, token);
  TEST_ASSERT_EQUAL(PREFIX, affix);
  // validation for encoding
  token = getToken(tokenizer);
  getAffix_ans = getAffix(token);
  TEST_ASSERT_EQUAL(PREFIX, getAffix_ans);
}

/*
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
}*/

void test_determineOperatorType_given_INFIX_expect_2_BINARY(void){
  Affix tokenAffix;
  tokenAffix = INFIX;
  OperatorType ans;
  ans = determineOperatorType(tokenAffix);

  TEST_ASSERT_EQUAL(2, ans);
}

void test_determineOperatorType_given_PREFIX_expect_1_UNARY(void){
  Affix tokenAffix;
  tokenAffix = PREFIX;
  OperatorType ans;

  ans = determineOperatorType(tokenAffix);
  TEST_ASSERT_EQUAL(1, ans);
}

void test_determineOperatorType_given_SUFFIX_expect_1_UNARY(void){
  Affix tokenAffix;
  tokenAffix = SUFFIX;
  OperatorType ans;

  ans = determineOperatorType(tokenAffix);
  TEST_ASSERT_EQUAL(1, ans);
}

void test_determineOperatorType_given_NULL_expect_ERR_INVALID_OPERATOR_TYPE(void){
  CEXCEPTION_T e;
  Affix tokenAffix;
  tokenAffix = NO_AFFIX;
  OperatorType ans;

  Try{
    ans = determineOperatorType(tokenAffix);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR_TYPE. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR_TYPE, e->errorCode);
    freeError(e);
  }
}

void test_combinePrefixWithToken_given_minus_2_expect_minus2_in_a_token(void){
  Token *token = NULL;
  Token *Ans;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2");
  token = getToken(tokenizer);

  Ans = combinePrefixWithToken(tokenizer, token);
  TEST_ASSERT_EQUAL(-2,((IntegerToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_minus_2point123_expect_minus2point123_in_a_token(void){
  Token *token = NULL;
  Token *Ans;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2.123");
  token = getToken(tokenizer);

  Ans = combinePrefixWithToken(tokenizer, token);
  TEST_ASSERT_EQUAL(-2.123,((FloatToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_plus_2_expect_2_in_a_token(void){
  Token *token = NULL;
  Token *Ans;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+2");
  token = getToken(tokenizer);

  Ans = combinePrefixWithToken(tokenizer, token);
  TEST_ASSERT_EQUAL(2,((IntegerToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_plus_2point123_expect_2point123_in_a_token(void){
  Token *token = NULL;
  Token *Ans;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("+2.123");
  token = getToken(tokenizer);

  Ans = combinePrefixWithToken(tokenizer, token);
  TEST_ASSERT_EQUAL(2.123,((FloatToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_2_and_3_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Token *token = NULL;
  Token *Ans;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("2 3");
  token = getToken(tokenizer);

  Try{
    Ans = combinePrefixWithToken(tokenizer, token);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
    freeError(e);
  }
}
