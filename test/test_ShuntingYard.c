#include "unity.h"
#include "ShuntingYard.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"
#include "Arithmetic.h"

#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

/* Starting from empty stack then push to the tokens to respective Stack
 * Then expect both operand popped and operator popped then do the Arithmetic
 *
 *             Operand Stack         Operator Stack
 *              +-----+               +-----+
 *    tail--->  +  1  +               +  +  +
 *              +-----+               +-----+
 *              +  2  +           head---^
 *              +-----+           tail---^
 *          head---^
 *
 */

void test_operateOnTokens_given_1_plus_2_exptect_3(void){
  Token *Ans            = NULL;
  Tokenizer *tokenizer  = NULL;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer(" 1 +2");

  Ans = shuntingYard(tokenizer, &operatorStack, &operandStack);

  TEST_ASSERT_EQUAL(3, ((IntegerToken*)Ans) ->value);

}

void test_pushBackToken(void){
  Token *token_1;
  Token *token_2;
  Token *token_3;

  Token *token_1_afterPush;
  Token *token_2_afterPush;
  Token *token_3_afterPush;

  Tokenizer *tokenizer  = NULL;

  tokenizer = createTokenizer("1 2 3");

  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);
  token_3 = getToken(tokenizer);

  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_1->type);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_2->type);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_3->type);

  pushBackToken(tokenizer, token_3);
  pushBackToken(tokenizer, token_2);
  pushBackToken(tokenizer, token_1);

  token_1_afterPush = getToken(tokenizer);
  token_2_afterPush = getToken(tokenizer);
  token_3_afterPush = getToken(tokenizer);

  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_1_afterPush->type);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_2_afterPush->type);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, token_3_afterPush->type);

}
