#include "unity.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void){}
void tearDown(void){}

/*    Before encode
 *    Affix     = PREFIX              = 0x0002 0000
 *    TokenType = TOKEN_OPERATOR_TYPE = 0x0000 0004
 *
 *    After encode
 *    TokenType = 0x0002 0004 = 131076 (decimals)
 */
void test_encodeAffix_given_minus_sign_expect_131076_after_encode(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(token,PREFIX);
  TEST_ASSERT_EQUAL(131076,token->type);

}
/*  FiRST ENCODE (Same result as previous test)
 *  Before
 *  TokenType = 0x0002 0004 = 131076 (decimals)
 *
 *  After (getAffix)
 *  TokenType = 0x0002 0000 = 131072 (decimals)
 */
void test_getAffix_given_minus_sign_expect_PREFIX(void){
  Affix affix;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(token,PREFIX);
  affix = getAffix(token);

  TEST_ASSERT_EQUAL(131076,token->type);
  TEST_ASSERT_EQUAL(PREFIX,affix);
}

/*  FiRST ENCODE (Same result as previous test)
 *  Before
 *  TokenType = 0x0002 0004 = 131076 (decimals)
 *
 *  After (getTokenType)
 *  TokenType = 0x0000 0004 = 4 (decimals)
 */
void test_getTokenType_given_minus_sign_expect_TOKEN_OPERATOR_TYPE(void){
  TokenType tokenType;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(token,PREFIX);
  tokenType = getTokenType(token);

  TEST_ASSERT_EQUAL(131076,token->type);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,tokenType);
}

/*  FIRST Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0002 0004 = 131076 (decimals)
 *  getAffix
 *  TokenType = 0x0002 0000 = 131072 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0004 = 4 (decimals)
 *
 *  SECOND Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0001 0003 = 65539 (decimals)
 *  getAffix
 *  TokenType = 0x0001 0000 = 65536 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0003 = 3 (decimals)
 */
void test_TokenAffix_three_functions_encodeAffix_getAffix_getTokenType_given_minus_2_expect_minus_PREFIX_TOKEN_OPERATOR_TYPE_and_2_NO_AFFIX_and_TOKEN_INTEGER_TYPE(void){
  Affix affix;
  TokenType tokenType;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-2");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(token,PREFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(131076,token->type);
  TEST_ASSERT_EQUAL(PREFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,tokenType);

  // should get operand '2'
  token = getToken(tokenizer);
  encodeAffix(token,NO_AFFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(65539,token->type);
  TEST_ASSERT_EQUAL(NO_AFFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,tokenType);

}

/*  FIRST Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0002 0004 = 131076 (decimals)
 *  getAffix
 *  TokenType = 0x0002 0000 = 131072 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0004 = 4 (decimals)
 *
 *  SECOND Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0001 0003 = 65539 (decimals)
 *  getAffix
 *  TokenType = 0x0001 0000 = 65536 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0003 = 3 (decimals)
 *
 *  THIRD Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0004 0004 = 262148 (decimals)
 *  getAffix
 *  TokenType = 0x0004 0000 = 262144 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0004 = 4 (decimals)
 *
 *  FOURTH Cycle
 *  ------------
 *  encodeAffix
 *  TokenType = 0x0001 0003 = 65539 (decimals)
 *  getAffix
 *  TokenType = 0x0001 0000 = 65536 (decimals)
 *  getTokenType
 *  TokenType = 0x0000 0003 = 3 (decimals)
 */

void test_TokenAffix_three_functions_encodeAffix_getAffix_getTokenType_given_minus_2_plus_3_expect_minus_PREFIX_TOKEN_OPERATOR_TYPE_and_2_NO_AFFIX_and_TOKEN_INTEGER_TYPE_and_plus_POST_AFFIX_TOKEN_OPERATOR_TYPE_and_3_NO_AFFIX_and_TOKEN_INTEGER_TYPE(void){
  Affix affix;
  TokenType tokenType;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-2+ 3");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(token,PREFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(131076,token->type);
  TEST_ASSERT_EQUAL(PREFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,tokenType);

  // should get operand '2'
  token = getToken(tokenizer);
  encodeAffix(token,NO_AFFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(65539,token->type);
  TEST_ASSERT_EQUAL(NO_AFFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,tokenType);

  // should get operator '+'
  token = getToken(tokenizer);
  encodeAffix(token, SUFFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(262148,token->type);
  TEST_ASSERT_EQUAL(SUFFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,tokenType);

  // should get operand '3'
  token = getToken(tokenizer);
  encodeAffix(token,NO_AFFIX);
  affix = getAffix(token);
  tokenType = getTokenType(token);
  TEST_ASSERT_EQUAL(65539,token->type);
  TEST_ASSERT_EQUAL(NO_AFFIX,affix);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,tokenType);
}
/*
void test_extractAffix_given_operatorToken_expect_affix_PREFIX(void){
  Affix affix;

  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("-2");

  token = getToken(tokenizer);
  StackItem TOKEN_operator = {NULL, (void *)token};
  StackBlock operatorStack = {&TOKEN_operator, &TOKEN_operator,1};

  StackItem TOKEN_operand = {NULL ,(void *) token};
  StackBlock operandStack = {&TOKEN_operand, &TOKEN_operand,1};

  token = getToken(tokenizer);
  affix = extractAffix(&operatorStack, &operandStack);

  TEST_ASSERT_EQUAL(PREFIX, affix);
}
*/
