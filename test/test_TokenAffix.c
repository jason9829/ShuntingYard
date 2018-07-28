#include "unity.h"
#include "TokenAffix.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void){}
void tearDown(void){}

void test_TokenAffix_given_minus_2_expect_minus_PREFIX(void){
  int affix;
  int type;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("-2");

  // should get operand '2'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,type);
  TEST_ASSERT_EQUAL(PREFIX,affix);

  // should get operand '2'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,type);

}

void test_TokenAffix_given_minus_2_plus_3_expect_minus_PREFIX_plus_INFIX(void){
  int affix;
  int type;
  Token *token = NULL;
  Tokenizer *tokenizer;
  tokenizer = createTokenizer("-2 +3 ");

  // should get operator '-'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,type);
  TEST_ASSERT_EQUAL(PREFIX,affix);

  // should get operand '2'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,type);


  // should get opeator '+'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,type);
  TEST_ASSERT_EQUAL(INFIX,affix);

  // should get operand '3'
  token = getToken(tokenizer);
  encodeAffix(&token,PREFIX);
  affix = getAffix(&token);
  type = getTokenType(&token);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,type);


}
