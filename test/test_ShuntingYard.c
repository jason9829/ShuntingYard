#include "unity.h"
#include "ShuntingYard.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"
#include "Arithmetic.h"

#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_pushTokensToRespectiveStack_given_3_plus_2_expect_push_all_tones_to_Stack(void){
  Tokenizer *tokenizer  = NULL;
  Token *poppedOperand_1_token;
  Token *poppedOperand_2_token;
  Token *poppedOperator_1_token;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedOperand_1;
  StackItem *poppedOperand_2;
  StackItem *poppedOperator_1;

  tokenizer = createTokenizer(" 3 + 2 ");

  pushTokensToRespectiveStack(tokenizer,&operatorStack, &operandStack);

  poppedOperand_1 = popStack(&operandStack);
  poppedOperand_1_token = (Token*)(poppedOperand_1->data);
  //TEST_ASSERT_EQUAL(3, ((IntegerToken*)poppedOperand_1_token)->value);

  poppedOperand_2 = popStack(&operandStack);
  poppedOperand_2_token = (Token*)(poppedOperand_1->data);
  TEST_ASSERT_EQUAL(2, ((IntegerToken*)poppedOperand_2_token)->value);

  poppedOperator_1 = popStack(&operatorStack);
  poppedOperator_1_token = (Token*)(poppedOperand_1->data);
  TEST_ASSERT_EQUAL('+', ((OperatorToken*)poppedOperator_1_token)->str);


}
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

void test_operateOnTokens_given_1_plus_2_expect_3(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 1 +2");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL(3, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}
/*
void test_operateOnTokens_given_2point5_multiply_2_expect_5point0(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2.5 * 2 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(5.0, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

void test_operateOnTokens_given_20point5_minus_1point30_expect_19point20(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 20.5 - 1.30 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(19.20, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

void test_operateOnTokens_given_20000point5_divide_1point75_expect_11428point86(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2000.5 /1.75 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(1143.14, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

void test_operateOnTokens_given_3_plus_negative2_expect_1(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;
  tokenizer = createTokenizer(" 3 + - 2");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL(1, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}

// 3~4
// 3+--2
// 3++4
void test_operateOnTokens_given_3_plus_minus_negative2_expect_1(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;
  tokenizer = createTokenizer(" 3 + -- 2");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL(5, ((IntegerToken*)answerToken)->value);
  //TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  //TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}

void test_operateOnTokens_given_3_plus_plus_2point12_expect_5point12(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;
  tokenizer = createTokenizer(" 3 + + 2.12");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(5.12, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}

void test_operateOnTokens_given_3_divide_minus_1point5_expect_minus_2point0(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 3 / - 1.5");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(-2.0, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}


void test_operateOnTokens_given_10_multiply_minus_1point5_expect_minus_15point0(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 10 *- 1.5");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(-15.0, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}
*/
void test_operationOnStacksIfOperatorIsInfix_given_2_plus_10_expect_12(void){
    StackBlock operatorStack = { NULL, NULL, 0};
    StackBlock operandStack  = { NULL, NULL, 0};

    Token *token = NULL;
    Token *ans = NULL;
    Tokenizer *tokenizer = NULL;

    tokenizer = createTokenizer(" 2 + 10");
    token = getToken(tokenizer);
    pushOperandStack(&operandStack, token);

    token = getToken(tokenizer);
    pushOperatorStack(&operatorStack, token);

    token = getToken(tokenizer);
    pushOperandStack(&operandStack, token);

    ans = operationOnStacksIfOperatorIsInfix(&operatorStack, &operandStack);

    TEST_ASSERT_EQUAL(12, ((IntegerToken*)ans)->value);
}

void test_operationOnStacksIfOperatorIsInfix_given_2_multiply_10point5_expect_21point0(void){
    StackBlock operatorStack = { NULL, NULL, 0};
    StackBlock operandStack  = { NULL, NULL, 0};

    Token *token = NULL;
    Token *ans = NULL;
    Tokenizer *tokenizer = NULL;

    tokenizer = createTokenizer(" 2 * 10.5");
    token = getToken(tokenizer);
    pushOperandStack(&operandStack, token);

    token = getToken(tokenizer);
    pushOperatorStack(&operatorStack, token);

    token = getToken(tokenizer);
    pushOperandStack(&operandStack, token);

    ans = operationOnStacksIfOperatorIsInfix(&operatorStack, &operandStack);

    TEST_ASSERT_EQUAL_FLOAT(21.0, ((FloatToken*)ans)->value);
}

void test_operationOnStacksIfOperatorIsInfix_given_2_multiply_expect_ERR_STACK_INSUFFICIENT(void){
  CEXCEPTION_T e;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  Token *token = NULL;
  Token *ans = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 2 *");
  token = getToken(tokenizer);
  pushOperandStack(&operandStack, token);

  token = getToken(tokenizer);
  pushOperatorStack(&operatorStack, token);
  Try{
  ans = operationOnStacksIfOperatorIsInfix(&operatorStack, &operandStack);
  TEST_FAIL_MESSAGE("Expect ERR_STACK_INSUFFICIENT. But no exception thrown.");
  }
  Catch(e){
  printf(e->errorMsg);
  TEST_ASSERT_EQUAL(ERR_STACK_INSUFFICIENT, e->errorCode);
  freeError(e);
  }


}
/*
void test_determineTokenOperatorType_given_2_minus_1_expect_BINARY_2(void){
  OperatorType tokenOperatorType;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 2 - 1");
  token = getToken(tokenizer);

  tokenOperatorType = determineTokenOperatorType(tokenizer, token);
  TEST_ASSERT_EQUAL(2, tokenOperatorType);
}
/*
void test_determineTokenOperatorType_given_minus_2_expect_UNARY_1(void){
  OperatorType tokenOperatorType;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" -2");
  token = getToken(tokenizer);

  tokenOperatorType = determineTokenOperatorType(tokenizer, token);
  TEST_ASSERT_EQUAL(1, tokenOperatorType);
}
*/
