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


//
 //    ***************************************************************************
 //    | TESTS for void pushOpenBracket(StackBlock *operatorStack, Token *token) |
 //    ***************************************************************************
 //    | 1. This function will push the '(' token when operatorStack is empty    |
 //    | 2. else do nothing                                                      |                                                                                                |
 //    ***************************************************************************
 //
void test_pushIfCurrentOpenBracket_given_non_Empty_Stack_open_Bracket_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *token;
  TokenType prevTokenType;

  StackBlock operatorStack = { NULL, NULL, 0};
  tokenizer = createTokenizer(" + ( ");

  token = getToken(tokenizer);
  pushOperatorStack(&operatorStack, token);

  token = getToken(tokenizer);
  pushIfCurrentOpenBracket(&operatorStack, token);

  TEST_ASSERT_EQUAL(2, operatorStack.count);


}


void test_pushIfCurrentOpenBracket_given_Empty_Stack_plus_expect_nothing_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Token *token;
  TokenType prevTokenType;

  StackBlock operatorStack = { NULL, NULL, 0};
  tokenizer = createTokenizer(" +  ");

  token = getToken(tokenizer);
  pushIfCurrentOpenBracket(&operatorStack, token);

  TEST_ASSERT_EQUAL(0, operatorStack.count);


}
///
 //    ************************************************************************
 //    | TESTS for int isTokenValid(Token *token, TokenType lastTokenType)    |
 //    ************************************************************************
 //    | 1. This function will compare the currentTokenType and lastTokenType,|
 //    |    if the combination is possible then return 1                      |
 //    | 2. else return 0                                                     |
 //    ************************************************************************
 //
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
///
 //    ************************************************************************
 //    | TESTS for int isOpenBracketToken(Token *token)                       |
 //    ************************************************************************
 //    | 1. This function will return 1 if the token is open bracket          |
 //    | 2. else rreturn 0                                                    |
 //    ************************************************************************
 //

void test_isOpenBracketToken_given_open_bracket_expect_1(void){
  int result;
  Token *token_1 = NULL;

  Tokenizer *tokenizer = NULL;


  tokenizer = createTokenizer("( ");
  token_1 = getToken(tokenizer);

  result = isOpenBracketToken(token_1);

  TEST_ASSERT_EQUAL(1, result);

}

void test_isOpenBracketToken_given_plus_expect_0(void){
  int result;
  Token *token_1 = NULL;

  Tokenizer *tokenizer = NULL;


  tokenizer = createTokenizer("+ ");
  token_1 = getToken(tokenizer);

  result = isOpenBracketToken(token_1);

  TEST_ASSERT_EQUAL(0, result);



}

///
 //    ************************************************************************
 //    | TESTS for int ClosingBracketToke(Token *token)                       |
 //    ************************************************************************
 //    | 1. This function will return 1 if the token is closing bracket       |
 //    | 2. else return 0                                                     |
 //    ************************************************************************
 //

void test_isClosingBracketToken_given_closing_bracket_expect_1(void){
  int result;
  Token *token_1 = NULL;

  Tokenizer *tokenizer = NULL;


  tokenizer = createTokenizer(")");
  token_1 = getToken(tokenizer);

  result = isClosingBracketToken(token_1);

  TEST_ASSERT_EQUAL(1, result);

}


void test_isClosingBracketToken_given_logical_and_sign_expect_0(void){
  int result;
  Token *token_1 = NULL;

  Tokenizer *tokenizer = NULL;


  tokenizer = createTokenizer("&");
  token_1 = getToken(tokenizer);

  result = isClosingBracketToken(token_1);

  TEST_ASSERT_EQUAL(0, result);

}

///
 //    ************************************************************************
 //    | TESTS for int operatorStackHeadIsPrefix(StackBlock *operatorStack)   |
 //    ************************************************************************
 //    | 1. This function will return 1 if the headOperatorToken is PREFIX    |
 //    |    (must encode before hand)                                         |
 //    | 2. else  return 0                                                    |
 //    ************************************************************************
 //
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

///
 //    ***********************************************************************
 //    | TESTS for int operatorStackHeadIsInfix(StackBlock *operatorStack)   |
 //    ***********************************************************************
 //    | 1. This function will return 1 if the headOperatorToken is INFIX    |
 //    |    (must encode before hand)                                        |
 //    | 2. else  return 0                                                   |
 //    ***********************************************************************
 //
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

//
 //    ***************************************************************************
 //    | TESTS for int areAssociativitiesSame(OperatorPrecedenceAndAssociativity |
 //    |  *headOperatorAndAssociativity,                                         |
 //    |  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity)   |
 //    **************************************************************************
 //    | 1. This function will compare the associativity, if the prevToken and   |
 //    |    nextToken associativity both are same return 1                       |
 //    | 2. else return 0                                                        |
 //    ***************************************************************************
 //

void test_areAssociativitiesSame_given_LEFT_TO_RIGHT_and_LEFT_TO_RIGHT_expect_1(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;

  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;

  tokenizer = createTokenizer("+ - ");
  token_1 = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token_1, affix);

  token_2 = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token_2, affix);

  headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_1);
  currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_2);

  result = areAssociativitiesSame(headOperatorAndAssociativity, currentOperatorAndAssociativity);

  TEST_ASSERT_EQUAL(1, result);

}

void test_areAssociativitiesSame_given_LEFT_TO_RIGHT_and_RIGHT_TO_LEFT_expect_0(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;

  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;

  tokenizer = createTokenizer("+ - ");
  token_1 = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token_1, affix);

  token_2 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_2, affix);

  headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_1);
  currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_2);

  result = areAssociativitiesSame(headOperatorAndAssociativity, currentOperatorAndAssociativity);

  TEST_ASSERT_EQUAL(0, result);

}

void test_areAssociativitiesSame_given_both_NO_ASSOCIATIVITY_expect_1(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
  Affix affix;
  Tokenizer *tokenizer = NULL;

  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;

  tokenizer = createTokenizer(" & & ");
  token_1 = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token_1, affix);

  token_2 = getToken(tokenizer);
  affix = INFIX;
  encodeAffix(token_2, affix);

  headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_1);
  currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token_2);

  result = areAssociativitiesSame(headOperatorAndAssociativity, currentOperatorAndAssociativity);

  TEST_ASSERT_EQUAL(1, result);


}
///
 //    *************************************************************************
 //    | TESTS for void closeBracketFoundButNoOpenBracket(Token *token,        |
 //    |  int openBracketCounter, int closeBracketCounter)                     |
 //    *************************************************************************
 //    | 1. it will check the number of open and close brackets if the number  |
 //    |    of close bracket > open bracket then an exception will be thrown   |
 //    | 2. else it will do nothing                                            |
 //    *************************************************************************
 //


void test_closeBracketFoundButNoOpenBracket_given_1_open_bracket_no_close_bracket_expect_ERR_MISSING_BRACKET(void){
  CEXCEPTION_T e;
  int openBracketCounter = 0;
  int closeBracketCounter = 1;
  Tokenizer *tokenizer = NULL;
  Token *token;
  tokenizer = createTokenizer(")");
  token = getToken(tokenizer);

  Try{
    closeBracketFoundButNoOpenBracket(token, openBracketCounter, closeBracketCounter);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_ASSERT_EQUAL(ERR_MISSING_BRACKET, e->errorCode);
  }

}
///
 //    *************************************************************************
 //    | TESTS for void matchBracket(Token *token,int openBracketCounter,      |
 //    | int closeBracketCounter)                                              |
 //    *************************************************************************
 //    | 1. it will check the number of open and close brackets if the number  |
 //    |    not matched it will throw an Exception                             |
 //    | 2. else it will do nothing                                            |
 //    *************************************************************************
 //

void test_matchBracket_given_1_open_bracket_no_close_bracket_expect_ERR_MISSING_BRACKET(void){
  CEXCEPTION_T e;
  int openBracketCounter = 1;
  int closeBracketCounter = 0;
  Tokenizer *tokenizer = NULL;
  Token *token;
    tokenizer = createTokenizer(" (  ");
  token = getToken(tokenizer);


  Try{
    matchBracket(token, openBracketCounter, closeBracketCounter);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_ASSERT_EQUAL(ERR_MISSING_BRACKET, e->errorCode);
  }

}

///
 //    *************************************************************************
 //    | TESTS for void cancelBracket(StackBlock *operatorStack, Token *token) |
 //    *************************************************************************
 //    | 1. if head of operatorStack is an open bracket, it will push          |
 //    |    currentToken to closing bracket, it will                           |
 //    |    cancel out the bracket                                             |
 //    | 2. else it will do nothing                                            |
 //    *************************************************************************
 //

void test_cancelBracket_given_previous_token_is_open_bracket_currentToken_is_closeing_bracket_expect_pushed(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer("( ) ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
  pushOperatorStack(&operatorStack, token_1);
  token_2 = getToken(tokenizer);


  cancelBracket(&operatorStack, token_2);

	TEST_ASSERT_EQUAL(0, operatorStack.count);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}


void test_cancelBracket_given_previous_token_is_open_bracket_currentToken_is_plus_expect_pushed(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer("( + ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
  pushOperatorStack(&operatorStack, token_1);
  token_2 = getToken(tokenizer);


  cancelBracket(&operatorStack, token_2);

	TEST_ASSERT_EQUAL(1, operatorStack.count);
  TEST_ASSERT_EQUAL(token_1, operatorStack.head->data);
  TEST_ASSERT_EQUAL(token_1, operatorStack.tail->data);

}



///
 //    ***************************************************************************
 //    | TESTS for void noOperatorBetweenBrackets(Token *token, Token *prevToken)|
 //    ***************************************************************************
 //    | 1. if () () between bracket has no operation symbol,                    |
 //    |    an exception will be thrown                                          |
 //    | 2. else it will do nothing                                              |
 //    ***************************************************************************
 //
void test_noOperatorBetweenBrackets_given_no_operator_between_2_brackets_expect_ERR_MISSING_OPERATOR(void){
    CEXCEPTION_T e;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken_1;
    Token *operatorToken_2;
    StackItem *poppedAns;

    Token *answerToken;

    StackBlock operatorStack = { NULL, NULL, 0};
    StackBlock operandStack  = { NULL, NULL, 0};
    StackItem *poppedStackItem;

    tokenizer = createTokenizer(") ("); //                  ') ('
                                        // throw an error-----^
    operatorToken_1 = getToken(tokenizer);

    operatorToken_2 = getToken(tokenizer);
    Try{
      // Since there is no operator between closing bracket and open bracet
      // Nothing will done to the stacks
      noOperatorBetweenBrackets(operatorToken_2, operatorToken_1);
      TEST_FAIL_MESSAGE("Expect ERR_MISSING_OPERATOR. But no exception thrown.");
    }
    Catch(e){
      dumpTokenErrorMessage(e, 1);
      TEST_ASSERT_EQUAL(ERR_MISSING_OPERATOR, e->errorCode);
    }


  }

void test_noOperatorBetweenBrackets_given_operator_between_2_brackets_expect_do_nothing(void){
    CEXCEPTION_T e;
    Tokenizer *tokenizer  = NULL;
    Token *operatorToken_1;
    Token *operatorToken_2;
    StackItem *poppedAns;

    Token *answerToken;

    StackBlock operatorStack = { NULL, NULL, 0};
    StackBlock operandStack  = { NULL, NULL, 0};
    StackItem *poppedStackItem;

    tokenizer = createTokenizer(") + (");
    operatorToken_1 = getToken(tokenizer);
    operatorToken_2 = getToken(tokenizer);

    Try{
      // Since there is a operator between closing bracket and open bracet
      // Nothing will done to the stacks
      noOperatorBetweenBrackets(operatorToken_2, operatorToken_1);
      TEST_ASSERT_EQUAL(operatorStack.count, 0);
      TEST_ASSERT_EQUAL(operatorStack.head, NULL);
      TEST_ASSERT_EQUAL(operatorStack.tail, NULL);
    }
    Catch(e){
      dumpTokenErrorMessage(e, 1);
    }
  }


  ///
   //    ***********************************************************************
   //    | TESTS for void pushIfprevTokenIsOpenBracket                         |
   //    |  (StackBlock *operatorStack, Token *token)                          |
   //    ***********************************************************************
   //    | 1. if head of operatorStack is an open bracket, it will             |
   //    |     push currentToken to the stack                                  |
   //    | 2. else it will do nothing                                          |
   //    ***********************************************************************
   //
void test_pushIfprevTokenIsOpenBracket_given_previous_token_is_open_bracket_expect_pushed(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer("( + ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
  pushOperatorStack(&operatorStack, token_1);
  token_2 = getToken(tokenizer);

  pushIfprevTokenIsOpenBracket(&operatorStack, token_2);

	TEST_ASSERT_EQUAL(2, operatorStack.count);
  TEST_ASSERT_EQUAL(token_2, operatorStack.head->data);
  TEST_ASSERT_EQUAL(token_1, operatorStack.tail->data);

}

void test_pushIfprevTokenIsOpenBracket_given_previous_token_is_plus_expect_nothing_happen(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer("+ - ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
  pushOperatorStack(&operatorStack, token_1);
  token_2 = getToken(tokenizer);

  pushIfprevTokenIsOpenBracket(&operatorStack, token_2);

  // still reamain 1 bcz didn't push
	TEST_ASSERT_EQUAL(1, operatorStack.count);
  TEST_ASSERT_EQUAL(token_1, operatorStack.head->data);
  TEST_ASSERT_EQUAL(token_1, operatorStack.tail->data);
}


///
 //    *************************************************************************
 //    | TESTS for void pushIfprevTokenIsOpenBracket                           |
 //    |  (StackBlock *operatorStack, Token *token)                            |
 //    *************************************************************************
 //    | 1. This function will the opration in a bracket                       |
 //    | 2. else it will do nothing                                            |
 //    *************************************************************************
 //

void test_operateIfBracket_given_previous_token_is_open_bracket_2_plus_2_closing_bracket_expect_4(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *token_3 = NULL;
  Token *token_4 = NULL;
	Token *token_5 = NULL;

	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer(" ( 2 + 2) ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
	pushOperatorStack(&operatorStack, token_1);
	token_2 = getToken(tokenizer);
	pushOperandStack(&operandStack, token_2);

	token_3 = getToken(tokenizer);
	affix = INFIX;
	encodeAffix(token_3, affix);
	pushOperatorStack(&operatorStack, token_3);

	token_4 = getToken(tokenizer);
	pushOperandStack(&operandStack, token_4);
	token_5 = getToken(tokenizer);
	operateIfBracket(&operatorStack, &operandStack, token_5);

	poppedStackItem = popStack(&operandStack);
	poppedToken = (Token*)(poppedStackItem->data);

	TEST_ASSERT_EQUAL(4, ((IntegerToken*)poppedToken)->value);

}


void test_operateIfBracket_given_previous_token_is_open_bracket_2_plus_2_expect_nothing_happen(void){
  int result;
  Token *token_1 = NULL;
  Token *token_2 = NULL;
	Token *token_3 = NULL;
  Token *token_4 = NULL;
	Token *token_5 = NULL;

	Token *poppedToken = NULL;

  Affix affix;
  Tokenizer *tokenizer = NULL;
	StackItem *poppedStackItem;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};

  tokenizer = createTokenizer(" ( 2 + 2 ");
  token_1 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(token_1, affix);
	pushOperatorStack(&operatorStack, token_1);
	token_2 = getToken(tokenizer);
	pushOperandStack(&operandStack, token_2);

	token_3 = getToken(tokenizer);
	affix = INFIX;
	encodeAffix(token_3, affix);
	pushOperatorStack(&operatorStack, token_3);

	token_4 = getToken(tokenizer);
	pushOperandStack(&operandStack, token_4);

	operateIfBracket(&operatorStack, &operandStack, token_4);

	poppedStackItem = popStack(&operandStack);
	poppedToken = (Token*)(poppedStackItem->data);

  // 2 because the head of opeand is 2
	TEST_ASSERT_EQUAL(2, ((IntegerToken*)poppedToken)->value);
  TEST_ASSERT_EQUAL(token_3, operatorStack.head->data);
  TEST_ASSERT_EQUAL(token_1, operatorStack.tail->data);

}


///
 //    *************************************************************************
 //    | TESTS for OperatorPrecedenceAndAssociativity                          |
 //    |  *getTokenPrecedenceAndAssociativity(Token *token)                    |
 //    *************************************************************************
 //    | 1. This function will get the Associativity of currentToken           |                                                                                                                                                                       |
 //    *************************************************************************

void test_getTokenAssociativity_given_currentToken_PREFIX_expect_RIGHT_TO_LEFT(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *token;

  Associativity currTokenAssociativity;

  tokenizer = createTokenizer(" +  ");
  token = getToken(tokenizer);

  affix = PREFIX;
  encodeAffix(token, affix);

  currTokenAssociativity = getTokenAssociativity(token);
  TEST_ASSERT_EQUAL(RIGHT_TO_LEFT, currTokenAssociativity);


}

void test_getTokenAssociativity_given_currentToken_INFIX_expect_LEFT_TO_RIGHT(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *token;

  Associativity currTokenAssociativity;

  tokenizer = createTokenizer(" +  ");
  token = getToken(tokenizer);

  affix = INFIX;
  encodeAffix(token, affix);

  currTokenAssociativity = getTokenAssociativity(token);
  TEST_ASSERT_EQUAL(LEFT_TO_RIGHT, currTokenAssociativity);

}

void test_getTokenAssociativity_given_currentToken_SUFFIX_expect_LEFT_TO_RIGHT(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *token;

  Associativity currTokenAssociativity;

  tokenizer = createTokenizer(" +  ");
  token = getToken(tokenizer);

  affix = SUFFIX;
  encodeAffix(token, affix);

  currTokenAssociativity = getTokenAssociativity(token);
  TEST_ASSERT_EQUAL(LEFT_TO_RIGHT, currTokenAssociativity);

}

void test_getTokenAssociativity_given_currentToken_INVALID_AFFIX_expect_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *token;

  Associativity currTokenAssociativity;

  tokenizer = createTokenizer(" + ");
  token = getToken(tokenizer);

  Try{
  currTokenAssociativity = getTokenAssociativity(token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }

}


void test_getTokenAssociativity_given_currentToken_a_ERR_INVALID_AFFIX(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *token;

  Associativity currTokenAssociativity;

  tokenizer = createTokenizer(" a");
  token = getToken(tokenizer);

  Try{
  currTokenAssociativity = getTokenAssociativity(token);
  TEST_FAIL_MESSAGE("Expect ERR_INVALID_AFFIX. But no exception thrown.");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_AFFIX, e->errorCode);
  }

}

///
 //    ************************************************************************
 //    | TESTS for void pushOperatorStackIfHeadTokenOfStackIsSamePrecedence   |
 //    | (StackBlock *operatorStack, StackBlock *operandStack, Token *token)  |
 //    ************************************************************************
 //    | 1. This function will compare the precedence of HeadofOperatorStack  |
 //    |    and token, if both of them are same precedence then it will push  |
 //    | 2. else do nothing                                                   |
 //    ************************************************************************
 //

void test_pushOperatorStackIfHeadTokenOfStackIsSamePrecedence_given_headToken_is_prefix_nextToken_also_prefix_expect_pushed(void){
  Tokenizer *tokenizer  = NULL;
  Affix affix;
  Token *operatorToken_1;
  Token *operandToken_1;
  Token *operatorToken_2;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  affix = PREFIX;
  encodeAffix(operatorToken_1, affix);
  encodeAffix(operatorToken_2, affix);
  pushOperandStack(&operandStack,operandToken_1);
  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(&operatorStack, &operandStack, operatorToken_2);

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
  StackBlock operandStack = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 + - 2 ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  affix1 = PREFIX;
  affix2 = INFIX;
  encodeAffix(operatorToken_1, affix1);
  encodeAffix(operatorToken_2, affix2);
  pushOperandStack(&operandStack, operandToken_1);
  pushOperatorStack(&operatorStack, operatorToken_1);
  pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(&operatorStack, &operandStack, operatorToken_2);

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
  pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(&operatorStack, operatorToken_2);

  TEST_ASSERT_EQUAL(2, operatorStack.count);


}

///
 //    ************************************************************************
 //    | TESTS for void pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence  |
 //    | (StackBlock *operatorStack, Token *token)                            |
 //    ***********************************************************************
 //    | 1. This function will compare the precedence of HeadofOperatorStack  |
 //    |    and token, if head operator is lower precedence then it will push |
 //    | 2. else do nothing                                                   |
 //    ************************************************************************
 //

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
  pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(&operatorStack, operatorToken_2);

  TEST_ASSERT_EQUAL(1, operatorStack.count);
  TEST_ASSERT_EQUAL(temp, operatorToken_2);

}

///
 //    ************************************************************************
 //    | TESTS for void pushIfOperatorStackIsEmpty                            |
 //    | (StackBlock *operatorStack, Token *token)                            |
 //    ***********************************************************************|
 //    | 1. If the operatorStack is empty , it will just push                 |
 //    | 2. else do nothing                                                   |
 //    ************************************************************************
 //

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

  pushIfOperatorStackIsEmpty(&operatorStack, operatorToken_1);

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
  pushIfOperatorStackIsEmpty(&operatorStack, operatorToken_2);

  TEST_ASSERT_EQUAL(1, operatorStack.count);;
  TEST_ASSERT_EQUAL(temp, operatorToken_2);

}


///
 //    ************************************************************************
 //    | TESTS for void operateIfHeadTokenOfStackIsHigherPrecedence           |
 //    | (StackBlock *operatorStack, StackBlock *operandStack, Token *token)  |
 //    ************************************************************************
 //    | 1. If the headOfOperatorStack is higher precedence, it will compute  |
 //    |    the operands based on the affix of the headToken                  |
 //    | 2. else it will check for precedence check for precedence and        |
 //    |    determine push or compute                                         |
 //    ************************************************************************
 //

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
  TEST_ASSERT_EQUAL(1, operandStack.count);
  TEST_ASSERT_EQUAL(1, operatorStack.count);

}

void test_operateIfHeadTokenOfStackIsHigherPrecedence_given_4_divided_2_then_add_compare_expect_2_push_back(void){
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
  tokenizer = createTokenizer(" 4 / 2 +  ");
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
  TEST_ASSERT_EQUAL(2, ((IntegerToken*)calculatedToken)->value);
  TEST_ASSERT_EQUAL(1, operandStack.count);
  TEST_ASSERT_EQUAL(1, operatorStack.count);

}

///
 //    ************************************************************************
 //    | TESTS for void operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT  |
 //    | (StackBlock *operatorStack,StackBlock *operandStack, Token *token)   |
 //    ************************************************************************
 //    | 1. If headOfOperatorStack and token are same precedence then it will |
 //    |    check for associativity, if associativity i LEFT_TO_RIGHT then    |
 //    |    do the operation on the stack   first then push when token is     |
 //    |    higer precidence                                                  |
 //    | 2. else don't operate                                                |
 //    ************************************************************************
void test_operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT_given_3_plus_INFIX_2_minus_INFIX_expect_5_minus(void){
  Associativity prevTokenAssociativity;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operatorToken_2;
  Token *operandToken_1;
  Token *operandToken_2;
  Token *calculatedToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *calculatedItem;
  // fake '+' as prefix
  tokenizer = createTokenizer(" 3 + 2 - ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operandToken_2 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);

  encodeAffix(operatorToken_1,INFIX);
  encodeAffix(operatorToken_2,INFIX);
  prevTokenAssociativity = getTokenAssociativity(operatorToken_1);

  pushOperandStack(&operandStack,operandToken_1);
  pushOperandStack(&operandStack,operandToken_2);
  pushOperatorStack(&operatorStack, operatorToken_1);

  operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(&operatorStack, &operandStack, operatorToken_2);

  calculatedItem = popStack(&operandStack);
  calculatedToken = (Token*)(calculatedItem->data);

  TEST_ASSERT_EQUAL(5, ((IntegerToken*)calculatedToken)->value);
  TEST_ASSERT_EQUAL(0, operandStack.count);
  // In the function wont push so operatorStack still 0
  TEST_ASSERT_EQUAL(0, operatorStack.count);



}


void test_operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT_given_3_plus_INFIX_minus_PREFIX_2_expect_do_nothing(void){
  Associativity prevTokenAssociativity;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken_1;
  Token *operatorToken_2;
  Token *operandToken_1;
  Token *operandToken_2;
  Token *calculatedToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *calculatedItem;
  // fake '+' as prefix
  tokenizer = createTokenizer(" 3 + - 2  ");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operatorToken_2 = getToken(tokenizer);
  operandToken_2 = getToken(tokenizer);

  encodeAffix(operatorToken_1, INFIX);
  encodeAffix(operatorToken_2, PREFIX);
  prevTokenAssociativity = getTokenAssociativity(operatorToken_1);

  pushOperandStack(&operandStack,operandToken_1);
  pushOperatorStack(&operatorStack, operatorToken_1);

  operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(&operatorStack, &operandStack, operatorToken_2);

  calculatedItem = popStack(&operandStack);
  calculatedToken = (Token*)(calculatedItem->data);

  TEST_ASSERT_EQUAL(3, ((IntegerToken*)calculatedToken)->value);
  TEST_ASSERT_EQUAL(0, operandStack.count);
  // didn't do anything so remain the same
  TEST_ASSERT_EQUAL(1, operatorStack.count);

}


///
 //    ************************************************************************
 //    | TESTS for void ifNullTokenOperateUntilOperatorStackIsEmpty           |
 //    | (StackBlock *operatorStack, StackBlock *operandStack, Token *token)  |
 //    ************************************************************************
 //    | 1. If TokenType is TOKEN_NULL_TYPE, then do the operation until the  |
 //    |    operatorStack is empty                                            |
 //    | 2. else don't operate                                                |
 //    ************************************************************************
 //
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
  TEST_ASSERT_EQUAL(1, operandStack.count);
  TEST_ASSERT_EQUAL(0, operatorStack.count);

}


void test_ifNullTokenOperateUntilOperatorStackIsEmpty_given_3_minus_2_plus_expect_do_nothing(void){
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
  tokenizer = createTokenizer(" 3 - 2 +");
  operandToken_1 = getToken(tokenizer);
  operatorToken_1 = getToken(tokenizer);
  operandToken_2 = getToken(tokenizer);
  nullToken = getToken(tokenizer);

  encodeAffix(operatorToken_1,INFIX);
  pushOperandStack(&operandStack,operandToken_1);
  pushOperandStack(&operandStack,operandToken_2);
  pushOperatorStack(&operatorStack, operatorToken_1);

  ifNullTokenOperateUntilOperatorStackIsEmpty(&operatorStack, &operandStack, nullToken);

  TEST_ASSERT_EQUAL(2, operandStack.count);
  TEST_ASSERT_EQUAL(1, operatorStack.count);

}



///
 //    ************************************************************************
 //    | TESTS for Token *operationOnStacksIfOperatorIsInfix                  |
 //    | (StackBlock *operatorStack, StackBlock *operandStack)                |
 //    ************************************************************************
 //    | 1. This function will do the arithmetic for the headOperator and     |
 //    |    first two operand                                                 |
 //    | 2. else  do nothing                                                  |
 //    ************************************************************************
 //
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

///
 //    ************************************************************************
 //    | TESTS for Token *operationOnStacksIfOperatorIsPrefix                 |
 //    | (StackBlock *operatorStack, StackBlock *operandStack)                |
 //    ************************************************************************
 //    | 1. This function will combine the headOperatorToken [PREFIX] ('+' or |
 //    |    '-')  to the headOperandToken. eg  (-)(10) = (-10)                |
 //    | 2. else  do nothing                                                  |
 //    ************************************************************************
 //
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

///
 //    **************************************************************************
 //    | TESTS for void operateOnStacksDependOnAffix                            |
 //    | (StackBlock *operatorStack, StackBlock *operandStack, Affix affix)     |
 //    **************************************************************************
 //    | 1. This function will call function operationOnStacksIfOperatorIsPrefix|
 //    |    or  operationOnStacksIfOperatorIsInfix to do the operation          |
 //    | 2. else  do nothing                                                    |
 //    **************************************************************************
 //
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





///
 //    ************************************************************************
 //    | TESTS for void shuntingYard(Tokenizer *tokenizer,                    |
 //    | StackBlock *operatorStack, StackBlock *operandStack)                 |
 //    ************************************************************************
 //    | 1. Only accept '+', '-' , '*' , '/' operation operator               |
 //    | 2. (2)(2)  no operation operator between brackets are not allowed    |
 //    ************************************************************************
 //
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
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" -2 + 3 ");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);

    TEST_ASSERT_EQUAL(1, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

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


void test_shuntingYard_given_2_plus_a_3_expect_ERR_INVALID_OPERATOR(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2 +a 3 ");
  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);

    TEST_ASSERT_EQUAL(-1, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }

}

void test_shuntingYard_given_2_plus_minus_negtive778_expect_ans_780(void){
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


void test_shuntingYard_given_negative_one_plus_5_multiply_3_expect_ans_correct(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" -1 + 5 * 3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(-1 + 5 * 3 , ((IntegerToken*)answerToken)->value);
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


void test_shuntingYard_given_10_plus_seven_multiply_2_plus_3_multiply_minus_minus_plus_42_divided_5point1_expect_ans_correct(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" 10 + 7*2 + 3 * - - + 42 / 5.1 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL_FLOAT( 10 + 7*2 + 3 * - - +  42 / 5.1, ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}


void test_shuntingYard_given_integer_only_expression_expect_answer_correct(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" 10 + 7*2 + 3 --5 - 42 * 20 + 20 +100 *20 /10 + 10 + 7*2 + 3 - + 5 - 42 * 20 + 20 +100 *20 /10 / 10 * 10");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(10 + 7 * 2 + 3 - - 5 - 42 * 20 + 20 +100 *20 /10 + 10 + 7*2 + 3 - + 5  - 42 * 20 + 20 +100 *20 /10 /10 * 10, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_integer_and_float_long_expression_expect_answer_correct(void){
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" 1.5+ 2.37 - 3.0 * 4 /5 * - - - - -100 / - - - 1000 + + - + - + - + 10000 * 25000.25 + 1.5+ 2.37 - 3.0 * 4 /5 * - - - - -100 - 100 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedAns = popStack(&operandStack);
  answerToken = (Token*)(poppedAns->data);

  TEST_ASSERT_EQUAL(1.5+ 2.37 - 3.0 * 4 /5 * - - - - -100 / - - - 1000 + + - + - + - + 10000 * 25000.25 + 1.5+ 2.37 - 3.0 * 4 /5 * - - - - -100 - 100 , ((FloatToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);

}

void test_shuntingYard_given_10_plus_seven_multiply_2_plus_3_multiply_minus_5_multiasdasdply_42_minus20_plus_60_minus_60_multiply_2_plus_100_plus_63_divide_100_plus_100_multuply_2_divide_2_expect_ans_negative_143(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 10  + - -5 *42 / 100 *1000");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL( 10  + - -5 *42 /100 *1000 , ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

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
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR, e->errorCode);
  }
}

void test_shuntingYard_given_bracket_2_multiply_2_close_bracket_plus_2_expect_6(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;
 //tokenizer = createTokenizer(" 10 /10 *10");

  tokenizer = createTokenizer(" (2*2) +2");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL( (2*2) +2, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

}

void test_shuntingYard_given_open_bracket_2_multiply_2_without_close_bracket_plus_2_expect6(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" ((2*2) +2");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL( (2*2) +2, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_ASSERT_EQUAL(ERR_MISSING_BRACKET, e->errorCode);
  }

}

void test_shuntingYard_given_2_minus_open_bracket_2_multiply_2_without_close_bracket_plus_2_expect6(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer("2 - (2*2) ");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL(2 -  (2*2), ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

}

void test_shuntingYard_given_2_minus_plus_minus_plus_minus_open_bracket_2_multiply_2_without_close_bracket_plus_2_expect6(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer("2 - + - + - (2*2) ");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL(2 - + - + - (2*2), ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

}


void test_shuntingYard_given_brackets_without_operator_expect_ERR_MISSING_OPERATOR(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;


  tokenizer = createTokenizer(" (2*2)(2)");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL( (2*2) +2, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_ASSERT_EQUAL(ERR_MISSING_OPERATOR,e->errorCode);
  }

}
void test_shuntingYard_given_without_open_bracket_2_multiply_2_close_bracket_plus_2_expect6(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 2*2 +2)");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL( (2*2) +2, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }

}

void test_shuntingYard_given_multiple_bracket_expect_calculated_correctly(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *operatorToken;
  Token *operandToken;
  StackItem *poppedAns;

  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" ((2+--2) * 2 + - - 2) * (+ - 2 *2 /-2) * (100/--+10)");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedAns = popStack(&operandStack);
    answerToken = (Token*)(poppedAns->data);
    TEST_ASSERT_EQUAL(((2+ - -2) * 2 +  - - 2) * (+ -2 *2 /-2) * (100/- - +10), ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e,1);
  }
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

void test_shuntingYard_given_1_plus_2_expect_3(void){
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

void test_shuntingYard_given_5_plus_minus_minus_3_expect_8(void){
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 5 + --3 ");

  shuntingYard(tokenizer, &operatorStack, &operandStack);
  poppedStackItem = popStack(&operandStack);
  answerToken = (Token*)(poppedStackItem->data);

  TEST_ASSERT_EQUAL_FLOAT(8.0, ((IntegerToken*)answerToken)->value);
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);
}

void test_shuntingYard_given_2point5_multiply_2_expect_5point0(void){
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

void test_shuntingYard_given_20point5_minus_1point30_expect_19point20(void){
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

void test_shuntingYard_given_20000point5_divide_1point75_expect_11428point86(void){
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

void test_shuntingYard_given_3_plus_negative2_expect_1(void){
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
void test_shuntingYard_given_3_plus_minus_negative2_expect_1(void){
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
  TEST_ASSERT_EQUAL(NULL, operatorStack.head);
  TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
  TEST_ASSERT_EQUAL(NULL, operandStack.head);
  TEST_ASSERT_EQUAL(NULL, operandStack.tail);

}

void test_shuntingYard_given_3_plus_plus_2point12_expect_5point12(void){
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

void test_shuntingYard_given_3_divide_minus_1point5_expect_minus_2point0(void){
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


void test_shuntingYard_given_10_multiply_minus_1point5_expect_minus_15point0(void){
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


//**************************TESTS FOR BUGS REPORTED***********************

void test_shuntingYard_given_expression_with_closing_bracket_but_without_open_bracket_expect_ERR_MISSING_BRACKET(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer(" 34 *7) -56");


  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedStackItem = popStack(&operandStack);
    answerToken = (Token*)(poppedStackItem->data);

    // compiler complain about the closing bracket after 7,
    // but expecting an exception so it's not important
    // TEST_ASSERT_EQUAL_FLOAT(34 *7) -56, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
    TEST_ASSERT_EQUAL(NULL, operandStack.head);
    TEST_ASSERT_EQUAL(NULL, operandStack.tail);

  }Catch(e){
    dumpTokenErrorMessage(e,1);
  }

}

void test_shuntingYard_expression_w_multiple_bracket_expect_calculated_correctly(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer("(((6)* ((((3+5))))/5 ) - 5) * 7 + (5 - 6) * (((7)))");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedStackItem = popStack(&operandStack);
    answerToken = (Token*)(poppedStackItem->data);

    TEST_ASSERT_EQUAL_FLOAT((((6)* ((((3+5))))/5 ) - 5) * 7 + (5 - 6) * (((7))), ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
    TEST_ASSERT_EQUAL(NULL, operandStack.head);
    TEST_ASSERT_EQUAL(NULL, operandStack.tail);

  }Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_FAIL_MESSAGE("Do not expect an exception");
  }

}

void test_shuntingYard_expression_2_w_multiple_bracket_expect_calculated_correctly(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer("-((-+-(-5)* - -7) - +5)");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedStackItem = popStack(&operandStack);
    answerToken = (Token*)(poppedStackItem->data);

    TEST_ASSERT_EQUAL_FLOAT(-((-+-(-5)* - -7) - +5), ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
    TEST_ASSERT_EQUAL(NULL, operandStack.head);
    TEST_ASSERT_EQUAL(NULL, operandStack.tail);
  }Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_FAIL_MESSAGE("Do not expect an exception");
  }

}

void test_shuntingYard_expression_w_one_bracket_expect_calculated_correctly(void){
  CEXCEPTION_T e;
  Tokenizer *tokenizer  = NULL;
  Token *answerToken;

  StackBlock operatorStack = { NULL, NULL, 0};
  StackBlock operandStack  = { NULL, NULL, 0};
  StackItem *poppedStackItem;

  tokenizer = createTokenizer("+-4* (-7-6) *5 -6 +2");

  Try{
    shuntingYard(tokenizer, &operatorStack, &operandStack);
    poppedStackItem = popStack(&operandStack);
    answerToken = (Token*)(poppedStackItem->data);

    TEST_ASSERT_EQUAL_FLOAT(+-4* (-7-6) *5 -6 +2, ((IntegerToken*)answerToken)->value);
    TEST_ASSERT_EQUAL(NULL, operatorStack.head);
    TEST_ASSERT_EQUAL(NULL, operatorStack.tail);
    TEST_ASSERT_EQUAL(NULL, operandStack.head);
    TEST_ASSERT_EQUAL(NULL, operandStack.tail);
  }Catch(e){
    dumpTokenErrorMessage(e,1);
    TEST_FAIL_MESSAGE("Do not expect an exception");
  }

}
