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

void test_operateOnTokens_given_1_plus_negative2_exptect_1(void){
  Token *Ans            = NULL;
  Tokenizer *tokenizer  = NULL;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer(" 3 + - 2");

  Ans = shuntingYard(tokenizer, &operatorStack, &operandStack);

  TEST_ASSERT_EQUAL(1, ((IntegerToken*)Ans) ->value);

}
