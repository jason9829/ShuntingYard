#ifndef _SHUNTINGYARD_H
#define _SHUNTINGYARD_H

#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Arithmetic.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "OperatorPrecedence_wTable.h"




int isTokenValid(Token *token, TokenType lastTokenType);
int isOpenBracketToken(Token *token);
int isClosingBracketToken(Token *token);
int checkIfNextTokenIsValid(Token *token, Tokenizer *tokenizer);
int operatorStackHeadIsPrefix(StackBlock *operatorStack);
int operatorStackHeadIsInfix(StackBlock *operatorStack);
int areAssociativitiesSame(OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity, OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity);

void noOperatorBetweenBrackets(Token *token, Token *prevToken);
void bracketCounter(Token *token, int openBracketFound, int closeBracketFound);
void matchBracket(Token *token,int openBracketCounter, int closeBracketCounter);

void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack);
void operateOnStacksDependOnAffix(StackBlock *operatorStack, StackBlock *operandStack, Affix affix);

void operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(StackBlock *operatorStack,StackBlock *operandStack, Token *token);

void operateIfBracket(StackBlock *operatorStack, StackBlock *operandStack, Token *token);
void cancelBracket(StackBlock *operatorStack, Token *token);

void operateIfHeadTokenOfStackIsHigherPrecedence(StackBlock *operatorStack, StackBlock *operandStack, Token *token);
void ifNullTokenOperateUntilOperatorStackIsEmpty(StackBlock *operatorStack, StackBlock *operandStack, Token *token);

Associativity getTokenAssociativity(Token *currentToken);
Token *operationOnStacksIfOperatorIsInfix(StackBlock *operatorStack, StackBlock *operandStack);
Token *operationOnStacksIfOperatorIsPrefix(StackBlock *operatorStack, StackBlock *operandStack);

void pushOperator(StackBlock *operatorStack, StackBlock *operandStack, Token *token);
void pushOperandStack(StackBlock *operandStack, Token *token);
void pushOperatorStack(StackBlock *operatorStack, Token *token);
void pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(StackBlock *operatorStack, Token *token);
void pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(StackBlock *operatorStack, StackBlock *operandStack, Token *token);
void pushIfOperandStackIsEmpty(StackBlock *operandStack, Token *token);
void pushIfOperatorStackIsEmpty(StackBlock *operatorStack, Token *token);
void pushIfprevTokenIsOpenBracket(StackBlock *operatorStack, Token *token);
#endif // _SHUNTINGYARD_H
