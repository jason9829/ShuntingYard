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

// 3++4
// 3+*4
// 3 + - + 5

void test_getTokenInfo_given_plus_sign_expect_attribute_7(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(7, affix->Attribute);
}
void test_getTokenInfo_given_minus_sign_expect_attribute_7(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("-");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(7, affix->Attribute);
}
void test_getTokenInfo_given_multiply_sign_expect_attribute_7(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("*");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(2, affix->Attribute);
}
void test_getTokenInfo_given_divide_sign_expect_attribute_7(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("/");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(2, affix->Attribute);
}

void test_getTokenInfo_given_open_bracket_sign_expect_attribute_4(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("(");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(4, affix->Attribute);
}

void test_getTokenInfo_given_close_bracket_sign_expect_attribute_1(void){
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer(")");
  token = getToken(tokenizer);
  affix = getTokenInfo(token);

  TEST_ASSERT_EQUAL(1, affix->Attribute);
}


void test_getTokenInfo_given_abc_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Token *token ;
  Tokenizer *tokenizer ;
  TokenInfo *affix ;

  tokenizer = createTokenizer("abc");
  token = getToken(tokenizer);


  Try{
    affix = getTokenInfo(token);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }

}


void test_checkOperatorsAffixPossibilities_given_open_bracket_and_multiply_expect_ERR_INVALID_OPERATOR(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("(*");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}


void test_checkOperatorsAffixPossibilities_given_plus_and_plus_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+ +");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_plus_and_multiply_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+ -");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_plus_and_minus_expect_FALSE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+ *");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_plus_and_divide_expect_FALSE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+ /");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_plus_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* +");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_minus_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* -");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_multiply_expect_FALSE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* *");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_divide_expect_FALSE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* /");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_open_bracket_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* (");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_multiply_and_close_bracket_expect_FALSE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("* )");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(0, result);
}

void test_checkOperatorsAffixPossibilities_given_close_bracket_and_close_bracket_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer(") )");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}


void test_checkOperatorsAffixPossibilities_given_open_bracket_and_open_bracket_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer(") )");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkOperatorsAffixPossibilities_given_open_bracket_and_minus_expect_TRUE(void){
  int result;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("( - ");
  token = getToken(tokenizer);

  result = checkOperatorsAffixPossibilities(token, tokenizer);
  TEST_ASSERT_EQUAL(1, result);
}
// TokenInfo = (7) -------------> PREFIX_TYPE | INFIX_TYPE | SUFFIX_TYPE = 7
void test_compareCurrTokenAndNextTokenWithTable_given_TokenInfo_7_and_7_expect_TRUE_1(void){
  int result;
  Token *token_1 ;
  Token *token_2 ;
  TokenInfo *tokenInfo_1 ;
  TokenInfo *tokenInfo_2 ;
  Tokenizer *tokenizer ;

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
  Token *token_1 ;
  Token *token_2 ;
  TokenInfo *tokenInfo_1 ;
  TokenInfo *tokenInfo_2 ;
  Tokenizer *tokenizer ;

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
  Token *token_1 ;
  Token *token_2 ;
  TokenInfo *tokenInfo_1 ;
  TokenInfo *tokenInfo_2 ;
  Tokenizer *tokenizer ;

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
  Token *token_1 ;
  Token *token_2 ;
  TokenInfo *tokenInfo_1 ;
  TokenInfo *tokenInfo_2 ;
  Tokenizer *tokenizer ;

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
  Token *token ;
  TokenType prevTokenType;
  Tokenizer *tokenizer ;

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
  Token *token ;
  TokenType prevTokenType;
  Tokenizer *tokenizer ;

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
  Token *token;
  Tokenizer *tokenizer;

  tokenizer = createTokenizer("12 12.1");
  token = getToken(tokenizer);

  Try{
  affix = checkTokenAffix(tokenizer, token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
  dumpTokenErrorMessage(e, 1);
  TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }
}

void test_checkTokenAffix_given_minus_and_divide_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;
  Token *token ;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("- /");
  token = getToken(tokenizer);

  Try{
  affix = checkTokenAffix(tokenizer, token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
  dumpTokenErrorMessage(e, 1);
  TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);;
  }
}

void test_checkTokenAffix_given_minus_sign_and_minus_sign_expect_PREFIX(void){
  Affix affix;
  Affix getAffix_ans;
  Token *token ;
  TokenType prevTokenType;
  Tokenizer *tokenizer ;

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

void test_checkTokenAffixAndEncodeAffix_given_2_plus_3_expect_infix(void){
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Tokenizer *tokenizer ;
  TokenType prevTokenType;

  tokenizer = createTokenizer("2 + 3");
  token = getToken(tokenizer);
  prevTokenType = TOKEN_INTEGER_TYPE;
  encodedToken = getToken(tokenizer);

  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,prevTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(INFIX, affix);

}

void xtest_checkTokenAffixAndEncodeAffix_given_minus_2_expect_prefix(void){
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Tokenizer *tokenizer ;
  TokenType prevTokenType;

  tokenizer = createTokenizer("-2");
  token = getToken(tokenizer);
  prevTokenType = TOKEN_NULL_TYPE ;

  checkTokenAffixAndEncodeAffix(token, tokenizer,prevTokenType);
  affix = getAffix(token);
  TEST_ASSERT_EQUAL(PREFIX, affix);

}

void test_checkTokenAffixAndEncodeAffix_given_2_plus_minus_3_expect_plus_infix_minus_prefix(void){
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Token *encodedToken_next ;
  Tokenizer *tokenizer ;
  TokenType encodedTokenType;

  tokenizer = createTokenizer("2 +- 3");
  token = getToken(tokenizer);
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_INTEGER_TYPE;
  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(INFIX, affix);

  // now the encodedToken -> type is encoded with affix and TokenType
  // so need to decode it
  encodedTokenType = TOKEN_OPERATOR_TYPE;
  token = getToken(tokenizer);
  checkTokenAffixAndEncodeAffix(token, tokenizer,encodedTokenType);
  affix = getAffix(token);
  TEST_ASSERT_EQUAL(PREFIX, affix);
}

void test_checkTokenAffixAndEncodeAffix_given_2_plus_open_bracket_minus_3_close_bracket_expect_plus_infix_open_bracket_prefix_minus_prefix_close_bracket_suffix(void){
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Token *encodedToken_next ;
  Tokenizer *tokenizer ;
  TokenType encodedTokenType;

  tokenizer = createTokenizer("2 + (-3)");
  token = getToken(tokenizer);

  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_INTEGER_TYPE;
  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(INFIX, affix);


  // now the encodedToken -> type is encoded with affix and TokenType
  // so need to decode it
  // for '('
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_OPERATOR_TYPE;
  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(PREFIX, affix);

  // for '-'
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_OPERATOR_TYPE;
  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(PREFIX, affix);

  token = getToken(tokenizer);
  // for ')'
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_INTEGER_TYPE;
  checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
  affix = getAffix(encodedToken);
  TEST_ASSERT_EQUAL(SUFFIX, affix);
}

void test_checkTokenAffixAndEncodeAffix_given_2_open_bracket_3__close_bracket_expect_plus_infix_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Tokenizer *tokenizer ;
  TokenType encodedTokenType;

  tokenizer = createTokenizer("2 (3)");
  token = getToken(tokenizer);
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_INTEGER_TYPE;

  Try{
      checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }
}

void test_checkTokenAffixAndEncodeAffix_given_2_plus_multiply_3_expect_plus_infix_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Affix affix;
  Token *token ;
  Token *encodedToken ;
  Token *encodedToken_next ;
  Tokenizer *tokenizer ;
  TokenType encodedTokenType;

  // for '+'
  tokenizer = createTokenizer("2 + * 3");
  token = getToken(tokenizer);
  encodedToken = getToken(tokenizer);
  encodedTokenType = TOKEN_INTEGER_TYPE;


  Try{
    checkTokenAffixAndEncodeAffix(encodedToken, tokenizer,encodedTokenType);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }
}

void test_combinePrefixWithToken_given_minus_2_expect_minus2_in_a_token(void){
  Token *prefixToken ;
  Token *operandToken ;
  Token *Ans;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("-2");
  prefixToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  Ans = combinePrefixWithOperandToken(prefixToken, operandToken);
  TEST_ASSERT_EQUAL(-2,((IntegerToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_minus_2point123_expect_minus2point123_in_a_token(void){
  Token *prefixToken ;
  Token *operandToken ;
  Token *Ans;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("-2.123");
  prefixToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  Ans = combinePrefixWithOperandToken(prefixToken, operandToken);
  TEST_ASSERT_EQUAL(-2.123,((FloatToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_plus_2_expect_2_in_a_token(void){
  Token *prefixToken ;
  Token *operandToken ;
  Token *Ans;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+2");
  prefixToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  Ans = combinePrefixWithOperandToken(prefixToken, operandToken);
  TEST_ASSERT_EQUAL(2,((IntegerToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_plus_2point123_expect_2point123_in_a_token(void){
  Token *prefixToken ;
  Token *operandToken ;
  Token *Ans;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("+2.123");
  prefixToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  Ans = combinePrefixWithOperandToken(prefixToken, operandToken);
  TEST_ASSERT_EQUAL(2.123,((FloatToken*)Ans)->value);
}

void test_combinePrefixWithToken_given_2_and_3_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Token *prefixToken ;
  Token *operandToken ;
  Token *Ans;
  Tokenizer *tokenizer ;

  tokenizer = createTokenizer("2 3");
  prefixToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  Try{
    Ans = combinePrefixWithOperandToken(prefixToken, operandToken);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }
}
