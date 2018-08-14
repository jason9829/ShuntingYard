#include "unity.h"
#include "OperatorPrecedence_wTable.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "Common.h"
#include "Exception.h"
#include "CException.h"
#include "Error.h"

void setUp(void){}
void tearDown(void){}

void test_getTokenPrecedenceAndAssociativity_given_INFIX_PLUS_expect_bindingPower_1_associativity_LEFT_TO_RIGHT(void){
  Token *token = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedenceAndAssociativity *OperatorPrecedenceAndAssociativity = NULL;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token, affix);
  OperatorPrecedenceAndAssociativity = getTokenPrecedenceAndAssociativity(token);

  TEST_ASSERT_EQUAL(1, OperatorPrecedenceAndAssociativity->bindingPower);
  TEST_ASSERT_EQUAL(LEFT_TO_RIGHT, OperatorPrecedenceAndAssociativity->associativity);
}

void test_getTokenPrecedenceAndAssociativity_given_CLOSE_BREACKET_expect_bindingPower_3_associativity_RIGHT_TO_LEFT(void){
  Token *token = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedenceAndAssociativity *OperatorPrecedenceAndAssociativity = NULL;

  tokenizer = createTokenizer("-");
  token = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token, affix);
  OperatorPrecedenceAndAssociativity = getTokenPrecedenceAndAssociativity(token);

  TEST_ASSERT_EQUAL(3, OperatorPrecedenceAndAssociativity->bindingPower);
  TEST_ASSERT_EQUAL(RIGHT_TO_LEFT, OperatorPrecedenceAndAssociativity->associativity);
}

void test_getTokenPrecedenceAndAssociativity_given_CLOSE_BREACKET_expect_bindingPower_0_associativity_LEFT_TO_RIGHT(void){
  Token *token = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedenceAndAssociativity *OperatorPrecedenceAndAssociativity = NULL;

  tokenizer = createTokenizer(")");
  token = getToken(tokenizer);
  affix = SUFFIX;
  encodeAffix(token, affix);
  OperatorPrecedenceAndAssociativity = getTokenPrecedenceAndAssociativity(token);

  TEST_ASSERT_EQUAL(0, OperatorPrecedenceAndAssociativity->bindingPower);
  TEST_ASSERT_EQUAL(LEFT_TO_RIGHT, OperatorPrecedenceAndAssociativity->associativity);
}

void test_getTokenPrecedenceAndAssociativity_given_and_sign_expect_bindingPower_0_associativity_0(void){
  Token *token = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedenceAndAssociativity *OperatorPrecedenceAndAssociativity = NULL;

  tokenizer = createTokenizer("&");
  token = getToken(tokenizer);
  affix = SUFFIX;
  encodeAffix(token, affix);
  OperatorPrecedenceAndAssociativity = getTokenPrecedenceAndAssociativity(token);

  TEST_ASSERT_EQUAL(0, OperatorPrecedenceAndAssociativity->bindingPower);
  TEST_ASSERT_EQUAL(0, OperatorPrecedenceAndAssociativity->associativity);
}



void test_getTokenPrecedenceAndAssociativity_given_plus_NO_AFFIX_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Token *token = NULL;
  OperatorPrecedenceAndAssociativity *OperatorPrecedenceAndAssociativity = NULL;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("+");

  token = getToken(tokenizer);

  Try{
    OperatorPrecedenceAndAssociativity = getTokenPrecedenceAndAssociativity(token);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }

}

// plus and minus sign has the same binding power
void test_getTokenPrecedence_given_plus_sign_expect_1(void){
  Token *token = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token, affix);
  precedence = getTokenPrecedence(token);

  TEST_ASSERT_EQUAL(3, precedence->bindingPower);
}

void test_getTokenPrecedence_given_plus_1_expect_1(void){
  Token *token = NULL;
  Token *nextToken = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("+1");
  token = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token, affix);
  precedence = getTokenPrecedence(token);

  TEST_ASSERT_EQUAL(3, precedence->bindingPower);
}

// multiply and divide sign has the same binding power
void test_getTokenPrecedence_given_divide_sign_expect_2(void){
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  Affix affix;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("/");
  token = getToken(tokenizer);

  affix = INFIX;
  encodeAffix(token, affix);

  precedence = getTokenPrecedence(token);
  TEST_ASSERT_EQUAL(2, precedence->bindingPower);

}

void test_getTokenPrecedence_given_a_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;
  OperatorPrecedence *precedence = NULL;

  tokenizer = createTokenizer("a");
  token = getToken(tokenizer);

  Try{
      precedence = getTokenPrecedence(token);
      TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
    }
      Catch(e){
      dumpTokenErrorMessage(e, 1);
      TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
    }

}

void test_comparePrevTokenAndNextTokenPrecedence_given_plus_and_multiply_expect_0(void){
  CEXCEPTION_T e;
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;

  Affix affix;
  Affix affixNextToken;
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("+ *");

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);

  affix         = INFIX;
  affixNextToken= INFIX;
  encodeAffix(token, affix);
  encodeAffix(nextToken, affixNextToken);

  Try{
    ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);
    TEST_ASSERT_EQUAL(0, ans);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }

}
void test_comparePrevTokenAndNextTokenPrecedence_given_divide_and_minus_expect_1(void){
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;
  Affix affix;
  Affix affixNextToken;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("/-");

  affix         = INFIX;
  affixNextToken= PREFIX;

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);
  encodeAffix(token, affix);
  encodeAffix(nextToken, affixNextToken);

  ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);

  TEST_ASSERT_EQUAL(0, ans);
}

void test_comparePrevTokenAndNextTokenPrecedence_given_plus_and_plus_expect_2(void){
  int ans;
  Token *token = NULL;
  Token *nextToken = NULL;
  Affix affix;
  Affix affixNextToken;

  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("++");

  affix         = INFIX;
  affixNextToken= PREFIX;

  token = getToken(tokenizer);
  nextToken = getToken(tokenizer);
  encodeAffix(token, affix);
  encodeAffix(nextToken, affixNextToken);

  // nextToken > token
  // in function compare by token < nextToken return 0
  ans = comparePrevTokenAndNextTokenPrecedence(nextToken, token);

  TEST_ASSERT_EQUAL(0, ans);
}
