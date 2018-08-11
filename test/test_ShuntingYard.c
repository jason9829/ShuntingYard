#include "unity.h"
#include "ShuntingYard.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "OperatorPrecedence_wTable.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"
#include "Arithmetic.h"
#include "CException.h"

#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}


void test_ifOpenBracketFoundKeepPushingUntilCloseBracket_given_open_bracket_3_close_bracket_expect_3_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" ( 3 ) ");
  operatorToken_1 = getToken(tokenizer);
  operandToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);


  pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(&operatorStack, operatorToken_2, tokenizer);

  TEST_ASSERT_EQUAL(2, operatorStack.count);

}
/*
void test_pushOperatorStackIfHeadTokenOfStackIsSamePrecedence_given_headToken_is_prefix_nextToken_also_prefix_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(operatorToken_1, affix);
  encodeAffix(operatorToken_2, affix);
  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(&operatorStack, operatorToken_2, tokenizer);

  TEST_ASSERT_EQUAL(2, operatorStack.count);

}

void test_pushOperatorStackIfHeadTokenOfStackIsSamePrecedence_given_headToken_is_prefix_nextToken_also_infix_expect_didnt_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix1;
  Affix affix2;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  affix1 = PREFIX;
  affix2 = INFIX;
  encodeAffix(operatorToken_1, affix1);
  encodeAffix(operatorToken_2, affix2);
  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(&operatorStack, operatorToken_2, tokenizer);

  TEST_ASSERT_EQUAL(1, operatorStack.count);

}

void test_pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence_given_headToken_is_infix_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix1;
  Affix affix2;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;
  Token *operandToken_2;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  affix1 = INFIX;
  affix2 = PREFIX;
  encodeAffix(operatorToken_1, affix1);
  encodeAffix(operatorToken_2, affix2);
  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(&operatorStack, operatorToken_2, tokenizer);

  TEST_ASSERT_EQUAL(2, operatorStack.count);

}

void test_pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence_given_headToken_is_prefix_expect_didnt_push(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;
  Token *temp;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  temp = operatorToken_2;
  affix = PREFIX;

  encodeAffix(operatorToken_1, affix);

  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(&operatorStack, operatorToken_2, tokenizer);

  TEST_ASSERT_EQUAL(1, operatorStack.count);
  TEST_ASSERT_EQUAL(temp, operatorToken_2);
}


void test_pushIfOperatorStackIsEmpty_given_empty_stack_and_an_operator_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operandToken_1;
  TokenType prevTokenType;
  StackBlock operatorStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 2 + 3 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);

  prevTokenType =TOKEN_INTEGER_TYPE;

  pushIfOperatorStackIsEmpty(&operatorStack, operatorToken_1, tokenizer, prevTokenType);

  TEST_ASSERT_EQUAL(1, operatorStack.count);

}

void test_pushIfOperatorStackIsEmpty_given_not_empty_stack_an_operator_expect_didnt_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operatorToken_2;
  Token *operandToken_1;
  Token *temp;
  TokenType prevTokenType;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  prevTokenType =TOKEN_INTEGER_TYPE;
  // fake '+' as prefix
  tokenizer = createTokenizer(" 2 +- 3 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  temp = operatorToken_2;

  pushOperatorStack(&operatorStack, operatorToken_1);
  pushIfOperatorStackIsEmpty(&operatorStack, operatorToken_2, tokenizer, prevTokenType);

  TEST_ASSERT_EQUAL(1, operatorStack.count);;
  TEST_ASSERT_EQUAL(temp, operatorToken_2);

}

void test_pushIfOperandStackIsEmpty_given_empty_stack_and_an_operand_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operandToken_1;
  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 2 + 3 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);


  pushIfOperandStackIsEmpty(&operatorStack, operandToken_1);

  TEST_ASSERT_EQUAL(1, operatorStack.count);

}


void test_pushIfOperandStackIsEmpty_given_not_empty_stack_an_operand_expect_didnt_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operatorToken_2;
  Token *operandToken_1;
  TokenType prevTokenType;

  Token *temp;
  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 2 +- 3 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  temp = operatorToken_2;
  prevTokenType = TOKEN_OPERATOR_TYPE;

  pushOperandStack(&operatorStack, operatorToken_1);
  pushIfOperatorStackIsEmpty(&operatorStack, operatorToken_2, tokenizer, prevTokenType);

  TEST_ASSERT_EQUAL(1, operatorStack.count);
  TEST_ASSERT_EQUAL(temp, operatorToken_2);

}

void test_operateIfHeadTokenOfStackIsHigherPrecedence_given_3_multiply_2_then_add_compare_expect_six_push_back(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operatorToken_2;
  Token *operandToken_1;
  Token *operandToken_2;
  Token *calculatedToken;
  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 3 * 2 + ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operandToken_2 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);

  encodeAffix(operatorToken_1,INFIX);
  encodeAffix(operatorToken_2,INFIX);
  pushOperandStack(&operandStack,operandToken_1);
  pushOperandStack(&operandStack,operandToken_2);
  pushOperatorStack(&operatorStack, operatorToken_1);

  operateIfHeadTokenOfStackIsHigherPrecedence(&operatorStack, &operandStack, operatorToken_2);

  calculatedToken = (Token*)(operandStack.head->data);
  TEST_ASSERT_EQUAL(6, ((IntegerToken*)calculatedToken)->value);

}

void test_ifNullTokenOperateUntilOperatorStackIsEmpty_given_3_minus_2__expect_1_push_back(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operandToken_2;
  Token *nullToken;
  Token *calculatedToken;
  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  // fake '+' as prefix
  tokenizer = createTokenizer(" 3 - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operandToken_2 = getToken(tokenizer);
  nullToken = getToken(tokenizer);

  encodeAffix(operatorToken_1,INFIX);
  pushOperandStack(&operandStack,operandToken_1);
  pushOperandStack(&operandStack,operandToken_2);
  pushOperatorStack(&operatorStack, operatorToken_1);

  ifNullTokenOperateUntilOperatorStackIsEmpty(&operatorStack, &operandStack, nullToken);

  calculatedToken = (Token*)(operandStack.head->data);
  TEST_ASSERT_EQUAL(1, ((IntegerToken*)calculatedToken)->value);

}

// (+)(2)  valid
void test_isTokenValid_given_plus_and_2_expect_true(void){
  Tokenizer *tokenizer  = NULL;
  Token * prevToken = NULL;
  Token *token;
  TokenType prevTokenType;

  int ans;

  tokenizer = createTokenizer(" + 2 ");
  prevToken = getToken(tokenizer);
  prevTokenType = getTokenType(prevToken);
  // token is 2
  token = getToken(tokenizer);
  ans = isTokenValid(token, prevTokenType);

  TEST_ASSERT_EQUAL(1, ans);
}

//(+)(+)  valid
void test_isTokenValid_given_plus_and_plus_expect_true(void){
  Tokenizer *tokenizer  = NULL;
  Token * prevToken = NULL;
  Token *token;
  TokenType prevTokenType;

  int ans;

  tokenizer = createTokenizer(" + + ");
  prevToken = getToken(tokenizer);
  prevTokenType = getTokenType(prevToken);
  // token is 2
  token = getToken(tokenizer);
  ans = isTokenValid(token, prevTokenType);

  TEST_ASSERT_EQUAL(1, ans);
}

// (2)(2) valid
void test_isTokenValid_given_two_and_plus_expect_true(void){
  Tokenizer *tokenizer  = NULL;
  Token * prevToken = NULL;
  Token *token;
  TokenType prevTokenType;

  int ans;

  tokenizer = createTokenizer(" 2.112 + ");
  prevToken = getToken(tokenizer);
  prevTokenType = getTokenType(prevToken);
  // token is 2
  token = getToken(tokenizer);
  ans = isTokenValid(token, prevTokenType);

  TEST_ASSERT_EQUAL(1, ans);
}

// (2)(2) invalid
void test_isTokenValid_given_two_and_two_expect_true(void){
  Tokenizer *tokenizer  = NULL;
  Token * prevToken = NULL;
  Token *token;
  TokenType prevTokenType;

  int ans;

  tokenizer = createTokenizer(" 2 2 ");
  prevToken = getToken(tokenizer);
  prevTokenType = getTokenType(prevToken);
  // token is 2
  token = getToken(tokenizer);
  ans = isTokenValid(token, prevTokenType);

  TEST_ASSERT_EQUAL(0, ans);
}

void test_operationOnStacksIfOperatorIsPrefix_given_minus_2_expect_ans_minus_2(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" -2 ");
  operatorToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  pushOperandStack(&operandStack, operandToken);
  pushOperatorStack(&operatorStack, operatorToken);

  answerToken = operationOnStacksIfOperatorIsPrefix(&operatorStack, &operandStack);

  TEST_ASSERT_EQUAL(-2, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

void test_operateOnStacksDependOnAffix_given_2_plus_10_expect_12(void){
  Affix affix;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken_1;
  Token *operandToken_2;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + 10 ");
  operandToken_1 = getToken(tokenizer);
  pushOperandStack(&operandStack, operandToken_1);

  operatorToken = getToken(tokenizer);
  pushOperatorStack(&operatorStack, operatorToken);

  operandToken_2 = getToken(tokenizer);
  pushOperandStack(&operandStack, operandToken_2);

  affix = INFIX;
  operateOnStacksDependOnAffix(&operatorStack, &operandStack, affix);

  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);


  TEST_ASSERT_EQUAL(12, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
}

void test_operateOnStacksDependOnAffix_given_minus_5_expect_negative5(void){
  Affix affix;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken_1;
  Token *operandToken_2;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" -5");

  operatorToken = getToken(tokenizer);
  pushOperatorStack(&operatorStack, operatorToken);

  operandToken_1 = getToken(tokenizer);
  pushOperandStack(&operandStack, operandToken_1);

  affix = PREFIX;
  operateOnStacksDependOnAffix(&operatorStack, &operandStack, affix);

  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);


  TEST_ASSERT_EQUAL(-5, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
}


void test_operatorStackHeadIsPrefix_given_stackhead_PREFIX_expect_1(void){
    Affix affix;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken;
    int ans;

    StackBlock operatorStack = { NULL, NULL, 0};

    tokenizer = createTokenizer(" -2");
    operatorToken = getToken(tokenizer);
    affix = PREFIX;
    encodeAffix(operatorToken,affix);
    pushOperatorStack(&operatorStack, operatorToken);

    ans = operatorStackHeadIsPrefix(&operatorStack);

    TEST_ASSERT_EQUAL(1, ans);
}

void test_operatorStackHeadIsPrefix_given_stackhead_INFIX_expect_0(void){
    Affix affix;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken;
    int ans;

    StackBlock operatorStack = { NULL, NULL, 0};

    // fake minus as INFIX
    tokenizer = createTokenizer(" -2");
    operatorToken = getToken(tokenizer);
    affix = INFIX;
    encodeAffix(operatorToken,affix);
    pushOperatorStack(&operatorStack, operatorToken);

    ans = operatorStackHeadIsPrefix(&operatorStack);

    TEST_ASSERT_EQUAL(0, ans);
}


void test_operatorStackHeadIsInfix_given_stackhead_INFIX_expect_1(void){
    Affix affix;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken;
    int ans;

    StackBlock operatorStack = { NULL, NULL, 0};

    // fake minus as INFIX
    tokenizer = createTokenizer(" -2");
    operatorToken = getToken(tokenizer);
    affix = INFIX;
    encodeAffix(operatorToken,affix);
    pushOperatorStack(&operatorStack, operatorToken);

    ans = operatorStackHeadIsInfix(&operatorStack);

    TEST_ASSERT_EQUAL(1, ans);
}

void test_operatorStackHeadIsInfix_given_stackhead_PREFIX_expect_0(void){
    Affix affix;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken;
    int ans;

    StackBlock operatorStack = { NULL, NULL, 0};

    tokenizer = createTokenizer(" -2");
    operatorToken = getToken(tokenizer);
    affix = PREFIX;
    encodeAffix(operatorToken,affix);
    pushOperatorStack(&operatorStack, operatorToken);

    ans = operatorStackHeadIsInfix(&operatorStack);

    TEST_ASSERT_EQUAL(0, ans);
}

*/
/*
void test_shuntingYard_given_2_plus_3_expect_ans_5(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(5, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_negative2_plus_3_expect_ans_1(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" -2 + 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(1, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_2_plus_negtive3_expect_ans_negative1(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 +- 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-1, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}


void test_shuntingYard_given_10_plus_minus_negtive778_expect_ans_780(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 +-- 778 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(780, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}
void test_shuntingYard_given_10_plus_minus_plus_negtive778_expect_ans_780(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 +-+- 778 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(780, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_negative2_minus_negtive3_expect_ans_negative5(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" - 2 - 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-5, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
}


void test_shuntingYard_given_2_multiply_negtive2_expect_ans_negative4(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 * - 2 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-4, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_2_multiply_20_expect_ans_40(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 * + 20 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(40, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}
void test_shuntingYard_given_2point5_multiply_40_prefix_minus_expect_ans_5point0(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2.5 *  ----------------------------------------2 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(5.0, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}



void test_shuntingYard_given_one_plus_5_multiply_3_expect_ans_16(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 1 + 5 * 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(16, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_one_plus_5_multiply_3_plus_10_minus_2_expect_ans_24(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 1 + 5 * 3 + 10 - 2 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(24, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_10_plus_5_minus_5_multiply_10_divide_2_expect_ans_negative10(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 10 + 5 - 5 * 10 / 2 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-10, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}



void test_shuntingYard_given_10_plus_seven_multiply_2_plus_3_multiply_negative_42_divided_5point1_expect_ans_0point705(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" 10 + 7*2 + 3 * -42 / 5.1");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL_FLOAT(-0.705883, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}
*/
void test_shuntingYard_given_10_plus_seven_multiply_2_plus_3_multiply_negative_42_divided_5point1_expect_ans_222(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" 10 + 7*2 + 3 - 5 *42 - 20 + 60  ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-103, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}
void test_shuntingYard_given_2_2_plus_3_expect_ERR_INVALID_TOKEN(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 2 + 3 ");
  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);

    TEST_FAIL_MESSAGE("Expect ERR_INVALID_TOKEN. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 31);
    TEST_ASSERT_EQUAL(ERR_INVALID_TOKEN, e->errorCode);
  }
}

void test_shuntingYard_given_and_symbol_2_plus_3_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" & 2 + 3 ");
  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);

    TEST_FAIL_MESSAGE("Expect ERR_INVALID_OPERATOR. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 31);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }
}

/*
void test_operationOnStacksIfOperatorIsPrefix_given_plus_2point123_expect_ans_2point123(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" +2.123 ");
  operatorToken = getToken(tokenizer);
  operandToken = getToken(tokenizer);

  pushOperandStack(&operandStack, operandToken);
  pushOperatorStack(&operatorStack, operatorToken);

  answerToken = operationOnStacksIfOperatorIsPrefix(&operatorStack, &operandStack);

  TEST_ASSERT_EQUAL_FLOAT(2.123, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}
/*
void test_pushTokensToRespectiveStack_given_3_plus_2_expect_push_all_tones_to_Stack(void){
  Tokenizer *tokenizer  = NULL;
  Token * ansToken = NULL;
  StackItem *ans;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedOperand_1;
  StackItem *poppedOperand_2;
  StackItem *poppedOperator_1;

  //char operatorSymbol;
  tokenizer = createTokenizer(" 3 + 2 ");

  pushTokensToRespectiveStack(tokenizer,&operatorStack, &operandStack);

  ans = popStack(&operandStack);
  ansToken = (Token*)(ans->data);
  TEST_ASSERT_EQUAL(5, ((IntegerToken*)ansToken)->value);

}

void test_pushTokensToRespectiveStack_given_3_plus__minus_minus_2_expect_push_all_tones_to_Stack(void){
  Tokenizer *tokenizer  = NULL;
  Token * ansToken = NULL;
  StackItem *ans;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedOperand_1;
  StackItem *poppedOperand_2;
  StackItem *poppedOperator_1;

  //char operatorSymbol;
  tokenizer = createTokenizer(" 3 + - 2 ");

  pushTokensToRespectiveStack(tokenizer,&operatorStack, &operandStack);

  ans = popStack(&operandStack);
  ansToken = (Token*)(ans->data);
  TEST_ASSERT_EQUAL(1, ((IntegerToken*)ansToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(0, operatorStack.count);
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
/*
void xtest_operateOnTokens_given_1_plus_2_expect_3(void){
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

void xtest_operateOnTokens_given_5_plus_minus_minus_3_expect_8(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 5 + --3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(5.0, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

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
/*
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
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_STACK_INSUFFICIENT, e->errorCode);
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
