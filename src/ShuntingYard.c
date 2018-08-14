#include "ShuntingYard.h"
#include "Arithmetic.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include "Common.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "TokenAffix.h"
#include "OperatorPrecedence_wTable.h"

#include <stdio.h>
#include <stdlib.h>

#define START 1
#define STOP 0

void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Token *token;
  Token *nextToken;
  int answer;
  Affix prevOperatorAffix;
  TokenType prevTokenType;
  OperatorPrecedence *comparePrecedenceResults;
  Associativity prevTokenAssociativity;
  prevTokenType = TOKEN_NULL_TYPE;
  int condition = START;
  int bracketFound = 0 ;
  Token *ans;

  while(condition == START){
    token = getToken(tokenizer);

    if(!isTokenValid(token, prevTokenType) && token->type != TOKEN_NULL_TYPE){
      throwException(ERR_INVALID_TOKEN, token, "'%s' should not be here", token->str);
    }

    if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      pushOperandStack(operandStack, token);
      prevTokenType = getTokenType(token);
      continue;
    }
    else if (token->type == TOKEN_OPERATOR_TYPE){

		checkTokenAffixAndEncodeAffix(token, tokenizer, prevTokenType);

        //ifOpenBracketFoundKeepPushingUntilCloseBracket();
		pushOperatorBracket(operatorStack, operandStack, token);
        prevTokenType = getTokenType(token);
      }
    else{
      ifNullTokenOperateUntilOperatorStackIsEmpty(operatorStack, operandStack, token);
      condition = STOP;
    }
  }
}

// Assume open bracket is already found
void operateIfBracket(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  Token *headOperatorToken;
  Affix headOperatorAffix;
  if(isClosingBracketToken(token)){
    while(!isOpenBracketToken((Token*)(operatorStack->head->data))){
      headOperatorToken = (Token*)(operatorStack->head->data);
      headOperatorAffix = getAffix(headOperatorToken);
      operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
    }
    cancelBracket(operatorStack, token);
  }
}

void pushIfprevTokenIsOpenBracket(StackBlock *operatorStack, Token *token){
	if((Token*)(operatorStack->head->data) != token && isOpenBracketToken((Token*)(operatorStack->head->data))){
		pushOperatorStack(operatorStack, token);
	}
}

void cancelBracket(StackBlock *operatorStack, Token *token){
  if((Token*)(operatorStack->head->data) != token && isOpenBracketToken((Token*)(operatorStack->head->data)) && isClosingBracketToken(token)){
  popStack(operatorStack);
  freeToken(token);
  }
}

void pushOperatorBracket(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
    pushIfOperatorStackIsEmpty(operatorStack, token);
    pushIfprevTokenIsOpenBracket(operatorStack, token);
		pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(operatorStack, token);
    pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(operatorStack,operandStack, token);
    operateIfHeadTokenOfStackIsHigherPrecedence(operatorStack, operandStack, token);
}

void operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;
  Affix headOperatorAffix;
  Token *headOperatorToken;

  if(operatorStack->count !=0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(headOperatorToken);
    currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token);
    headOperatorAffix = getAffix(headOperatorToken);

  if(areAssociativitiesSame(headOperatorAndAssociativity, currentOperatorAndAssociativity)){
//if((headOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT && currentOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT)){
      if((headOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT && currentOperatorAndAssociativity-> associativity == LEFT_TO_RIGHT) && ((headOperatorAndAssociativity-> bindingPower == currentOperatorAndAssociativity-> bindingPower))){
          operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
      }
    }
  }

}


void ifNullTokenOperateUntilOperatorStackIsEmpty(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  Affix headOperatorAffix;
  Token *headOperatorToken;

  if(token->type == TOKEN_NULL_TYPE){
    while(operatorStack->count !=0){
      headOperatorToken = (Token*)operatorStack->head->data;
      headOperatorAffix = getAffix(headOperatorToken);
      operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
    }
  }

}

void operateIfHeadTokenOfStackIsHigherPrecedence(StackBlock *operatorStack, StackBlock *operandStack, Token *token){
  Token *headOperatorToken;
  Affix headOperatorAffix;
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;

  if(((Token*)(operatorStack->head->data) != token) && !isClosingBracketToken(token) && !isOpenBracketToken(token)){
      while(operatorStack->count !=0 && (comparePrevTokenAndNextTokenPrecedence(token, (Token*)(operatorStack->head->data)) == 1 ) ){
        headOperatorAffix = getAffix(headOperatorToken);
        if(operatorStack->count ==0){
          pushOperatorStack(operatorStack,token);
        }
        operateOnStacksDependOnAffix(operatorStack, operandStack, headOperatorAffix);
        if(operatorStack->count !=0){
          headOperatorToken = (Token*)operatorStack->head->data;
          headOperatorAffix = getAffix(headOperatorToken);

        }
      //  operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(operatorStack, operandStack, token);
      }
      pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(operatorStack, operandStack, token);
      pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(operatorStack, token);
      pushIfOperatorStackIsEmpty(operatorStack, token);
    }
  }


void pushIfOperatorStackIsEmpty(StackBlock *operatorStack, Token *token){
  if(operatorStack->count == 0){
    pushOperatorStack(operatorStack, token);
  }
}

void pushIfOperandStackIsEmpty(StackBlock *operandStack, Token *token){
  if(operandStack->count == 0){
    pushOperandStack(operandStack, token);
  }
}

int areAssociativitiesSame(OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity, OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity){
  if(headOperatorAndAssociativity->associativity == currentOperatorAndAssociativity->associativity){
    return 1;
  }
  else{
    return 0;
  }
}

void pushOperatorStackIfHeadTokenOfStackIsSamePrecedence(StackBlock *operatorStack,StackBlock *operandStack, Token *token){
  Affix affixOfHeadOperatorToken;
  OperatorPrecedenceAndAssociativity *headOperatorAndAssociativity;
  OperatorPrecedenceAndAssociativity *currentOperatorAndAssociativity;
  Token *headOperatorToken;
  TokenType prevTokenType;

  if(!isClosingBracketToken(token) && !isOpenBracketToken(token) && operatorStack->count != 0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    //prevTokenType = getTokenType(headOperatorToken);
    headOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(headOperatorToken);
    currentOperatorAndAssociativity = getTokenPrecedenceAndAssociativity(token);

    // HeadTokenIsInfix
      if(headOperatorToken != token){
        if (comparePrevTokenAndNextTokenPrecedence(token, headOperatorToken) == 2){
            operateStackIfOperatorsAssociativityAreLEFT_TO_RIGHT(operatorStack, operandStack, token);
            pushOperatorStack(operatorStack, token);
          }
      }
  }

  }

/*
 *  affixOfCurrentToken         Associativity
 *      PREFIX                  RIGHT-TO-LEFT
 *      INFIX                   LEFT-TO-RIGHT
 *      SUFFIX                  LEFT-TO-RIGHT
 */
Associativity getTokenAssociativity(Token *currentToken){
  Affix affixOfCurrentToken;

  affixOfCurrentToken = getAffix(currentToken);

  if(affixOfCurrentToken == PREFIX){
    return RIGHT_TO_LEFT;
  }
  else if(affixOfCurrentToken == INFIX){
    return LEFT_TO_RIGHT;
  }
  else if(affixOfCurrentToken == SUFFIX){
    return LEFT_TO_RIGHT;
  }
  else{
    throwException(ERR_INVALID_AFFIX, currentToken, "'%s' has an invalid affix, it should not be here", currentToken->str);
  }
}

void pushOperatorStackIfHeadTokenOfStackIsLowerPrecedence(StackBlock *operatorStack, Token *token){
  Affix affixOfHeadOperatorToken;
  Token *headOperatorToken;
  TokenType prevTokenType;

  if(operatorStack->count !=0){
    headOperatorToken = (Token*)(operatorStack->head->data);
    prevTokenType = getTokenType(headOperatorToken);
    affixOfHeadOperatorToken = getAffix(token);
    // HeadTokenIsInfix
      if(headOperatorToken != token){
        if(!operatorStackHeadIsPrefix(operatorStack)){
          if(!comparePrevTokenAndNextTokenPrecedence(token, headOperatorToken)){  // If 1 mean headOperator is higher precedence
             pushOperatorStack(operatorStack, token);
          }
        }
    }
  }

}

int operatorStackHeadIsPrefix(StackBlock *operatorStack){
  Affix affixOfHeadOperatorToken;
  affixOfHeadOperatorToken = getAffix((Token*)(operatorStack->head->data));

  if(affixOfHeadOperatorToken != PREFIX){
    return 0;
  }
  else{
    return 1;
  }
}

int operatorStackHeadIsInfix(StackBlock *operatorStack){
  Affix affixOfHeadOperatorToken;
  affixOfHeadOperatorToken = getAffix((Token*)(operatorStack->head->data));

  if(affixOfHeadOperatorToken != INFIX){
    return 0;
  }
  else{
    return 1;
  }
}

int isTokenValid(Token *token, TokenType lastTokenType){
  if(token->type == TOKEN_FLOAT_TYPE || token->type == TOKEN_INTEGER_TYPE){
    switch (lastTokenType) {
      case TOKEN_NULL_TYPE     : return 1;
      case TOKEN_OPERATOR_TYPE : return 1;
      default : return 0;
    }
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    switch (lastTokenType) {
      case TOKEN_NULL_TYPE      : return 1;
      case TOKEN_INTEGER_TYPE   : return 1;
      case TOKEN_FLOAT_TYPE     : return 1;
      case TOKEN_OPERATOR_TYPE  : return 1;
      default : return 0;
    }
  }
  else{
    return 0;
  }
}

int isOpenBracketToken(Token *token){
  char TokenSymbol;
  TokenSymbol = *((OperatorToken*)token)->str;

  if(TokenSymbol == '('){
    return 1;
  }
  else{
    return 0;
  }
}

int isClosingBracketToken(Token *token){
  char TokenSymbol;
  TokenSymbol = *((OperatorToken*)token)->str;

  if(TokenSymbol == ')'){
    return 1;
  }
  else{
    return 0;
  }
}

/*
void operateBasedOnPrecedence(StackBlock *operatorStack, StackBlock *operandStack, int comparePrecedenceResults){
  Affix currTokenAffix;
  currTokenAffix = getAffix((Token*)(operatorStack->head->data));
  Token *ans;

  switch (comparePrecedenceResults) {
    // precedence of head Operator larger than token
    case  0 : pushOperatorStack(operatorStack, token);
              break;
    case  1 : ans = operateOnStacksDependOnAffix(operatorStack, operandStack, currTokenAffix);
              pushOperandStack(operandStack, ans);
              break;
    case  2 : ans = operateOnStacksDependOnAffix(operatorStack, operandStack, currTokenAffix);
              pushOperandStack(operandStack, ans);
              break;
    default : throwException(ERR_INVALID_ANSWER, comparePrecedenceResults, "comparePrecedenceResults '%d' is invalid", comparePrecedenceResults);
  }
}*/
/*
void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Token *token;
  Token *nextToken;
  Affix prevOperatorAffix;
  TokenType prevTokenType;
  OperatorPrecedence *tokenPrecedence;
  prevTokenType = TOKEN_NULL_TYPE;
  int condition = START;

  while(condition == START){
    token = getToken(tokenizer);
    if(token->type == TOKEN_NULL_TYPE){
      while(operatorStack->count !=0){
        prevOperatorAffix = getAffix((Token*)(operatorStack->head->data));
        operateOnStacksDependOnAffix(operatorStack, operandStack, prevOperatorAffix);
      }
          condition = STOP;
    }
    else{
      if(isTokenValid(token, prevTokenType)){
        if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
          prevTokenType = getTokenType(token);
          pushOperandStack(operandStack, token);
          continue;
        }
        else{
          checkTokenAffixAndEncodeAffix(token, tokenizer, prevTokenType);
          tokenPrecedence = getTokenPrecedence(token);
          if(operatorStack->count == 0){
            prevTokenType = getTokenType(token);
            pushOperatorStack(operatorStack, token);
            prevOperatorAffix = getAffix((Token*)(operatorStack->head->data));
          }
          else{     // compare the precedence of operatorStack token and currentToken
            if(comparePrevTokenAndNextTokenPrecedence(token, (Token*)(operatorStack->head->data))){
              nextToken = getToken(tokenizer);
              if(nextToken->type == TOKEN_OPERATOR_TYPE){
                if(checkOperatorTokensAffixPossibilities(token, nextToken)){
                  pushBackToken(tokenizer, nextToken);
                  tokenPrecedence = getTokenPrecedence(token);
                  prevTokenType = getTokenType(token);
                  pushOperatorStack(operatorStack, token);
                  prevOperatorAffix = getAffix((Token*)(operatorStack->head->data));
                }
                else{
                  throwException(ERR_INVALID_TOKEN, token, "Affix of Token '%s' is invalid compare to '%s'", token->str, nextToken->str);
                }
              }
              prevOperatorAffix = getAffix((Token*)(operatorStack->head->data));
              operateOnStacksDependOnAffix(operatorStack, operandStack, prevOperatorAffix);
            }
            else{
              checkTokenAffixAndEncodeAffix(token, tokenizer, prevTokenType);
              tokenPrecedence = getTokenPrecedence(token);
              prevTokenType = getTokenType(token);
              pushOperatorStack(operatorStack, token);
            }
          }
        }
      }
      else{
        throwException(ERR_INVALID_TOKEN, token, "Token '%s' is invalid compare to '%s'", token->str, prevTokenType);
      }
    }
  }

}
*/

void operateOnStacksDependOnAffix(StackBlock *operatorStack, StackBlock *operandStack, Affix affix){
  Token *ans;
  switch (affix) {
    case INFIX  : ans = operationOnStacksIfOperatorIsInfix(operatorStack,  operandStack);
                  pushOperandStack(operandStack, ans);
                  break;
    case PREFIX : ans = operationOnStacksIfOperatorIsPrefix(operatorStack, operandStack);
                  pushOperandStack(operandStack, ans);
                  break;
  }
}

Token *operationOnStacksIfOperatorIsPrefix(StackBlock *operatorStack, StackBlock *operandStack){
  StackItem *poppedToken_1;
  StackItem *poppedToken_operator;

  Token *token_1;
  Token *token_operator;
  Token *ans;

  if(operatorStack->count >=1 && operandStack->count >=1){
    poppedToken_1 = popStack(operandStack);
    poppedToken_operator = popStack(operatorStack);
    token_1 = (Token*)(poppedToken_1->data);
    token_operator = (Token*)(poppedToken_operator->data);
    ans = combinePrefixWithOperandToken(token_operator, token_1);
    //freeToken(token_1);
    //freeToken(token_operator);
    return ans;
  }
  else{
    throwException(ERR_STACK_INSUFFICIENT, operandStack->head->data, "Only '%d' operator and '%d' operand", operatorStack->count, operandStack->count);
  }

}
Token *operationOnStacksIfOperatorIsInfix(StackBlock *operatorStack, StackBlock *operandStack){
    StackItem *poppedToken_1;
    StackItem *poppedToken_2;
    StackItem *poppedToken_operator;

    Token *token_1;
    Token *token_2;
    Token *token_operator;
    Token *ans;

    if(operatorStack->count >=1 && operandStack->count >=2){
      poppedToken_1 = popStack(operandStack);
      poppedToken_2 = popStack(operandStack);
      poppedToken_operator = popStack(operatorStack);
      token_1 = (Token*)(poppedToken_1->data);
      token_2 = (Token*)(poppedToken_2->data);
      token_operator = (Token*)(poppedToken_operator->data);
      ans = calculationOnTokens(token_2, token_1, token_operator);
      //freeToken(token_1);
      //freeToken(token_2);
      //freeToken(token_operator);
      //pushStack(operandStack, ans);
      return ans;
    }
    else{
      throwException(ERR_STACK_INSUFFICIENT, operandStack->head->data, "Only '%d' operator and '%d' operand", operatorStack->count, operandStack->count);
    }
}

void pushOperandStack(StackBlock *operandStack, Token *token){
  pushStack(operandStack, token);
}

void pushOperatorStack(StackBlock *operatorStack, Token *token){
  pushStack(operatorStack, token);
}

/*
void pushTokensToRespectiveStack(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Token *token ;
  Token *prevToken;
  Token *combinedWithPrefixToken;
  Token *ans;

  Affix prevTokenAffix;
  Affix currTokenAffix;

  TokenType prevTokenType;
  int comparePrecedenceResult;

  TokenType operatorType;

  token = getToken(tokenizer);

  while(token-> type != TOKEN_NULL_TYPE){
    if(token->type == TOKEN_FLOAT_TYPE || token->type == TOKEN_INTEGER_TYPE){
      if(operatorStack->count == 0){
        pushOperandStack(operandStack, token);
        prevToken = token;
        token = getToken(tokenizer);
      }
      else{
        pushOperandStack(operandStack, token);
        prevToken = token;
        token = getToken(tokenizer);
        ans = operationOnStacksIfOperatorIsInfix(operatorStack, operandStack);
        pushOperandStack(operandStack, ans);
      }

    }
    else if(token->type == TOKEN_OPERATOR_TYPE){
      prevTokenType = getTokenType(prevToken);
      if(prevTokenType == TOKEN_OPERATOR_TYPE){
        comparePrecedenceResult = comparePrevTokenAndNextTokenPrecedence(token, prevToken);
        switch (comparePrecedenceResult) {
          case 0 :   pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
                     checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
                     token = getToken(tokenizer);
                     pushOperatorStack(operatorStack, token);
                     prevToken = token;
                     token = getToken(tokenizer);
                     break;

          case 1 :   ans = operationOnStacksIfOperatorIsInfix(operatorStack, operandStack);
                     pushOperandStack(operandStack, ans);
                     pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
                     checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
                     token = getToken(tokenizer);
                     pushOperatorStack(operatorStack, token);
                     prevToken = token;
                     token = getToken(tokenizer);
                     break;

          case 2 :  pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
                    checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
                    token = getToken(tokenizer);
                    prevTokenAffix = getAffix(prevToken);
                    currTokenAffix = getAffix(token);
                      if(currTokenAffix == PREFIX){
                        if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
                          token = getToken(tokenizer);
                          combinedWithPrefixToken = combinePrefixWithOperandToken(prevToken,token);
                          pushOperandStack(operandStack, combinedWithPrefixToken);
                          freeToken(token);
                          prevToken = combinedWithPrefixToken;
                          token = getToken(tokenizer);
						  break;
                        } //
                        else{
                          pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
                          checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
                          token = getToken(tokenizer);
                          pushOperatorStack(operatorStack, token);
                          prevToken = token;
                          token = getToken(tokenizer);
						  break;
                        }
                      }

        }
      }
      else{
        pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
        checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
        token = getToken(tokenizer);
        pushOperatorStack(operatorStack, token);
        prevToken = token;
        token = getToken(tokenizer);
      }

    }
  }

}
*/
/*
void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Affix currOperatorAffix;
  Token *token;
  Token *prevToken;
  Token *ans;
  Token *combinedPrefixWithNumber;
  Token *token_operator;
  Token *prefixToken;
  TokenType tokenType;

  token = getToken(tokenizer);
  while(token-> type != TOKEN_NULL_TYPE){
    if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      if(operandStack->count == 0){
        pushOperandStack(operandStack, token);
        prevToken = token;
        token = getToken(tokenizer);
      }
      else if(currOperatorAffix == INFIX){
        pushOperandStack(operandStack, token);
        prevToken = token;
        ans = operationOnStacksIfOperatorIsInfix(operatorStack, operandStack);
        pushOperandStack(operandStack, ans);
        prevToken = token;
        token = getToken(tokenizer);

      }
    }
      else if(token->type == TOKEN_OPERATOR_TYPE){
        pushBackToken(tokenizer, token);
        checkTokenAffixAndEncodeAffix(tokenizer, prevToken);
        token = getToken(tokenizer);
        currOperatorAffix = getAffix(token);
        tokenType = getTokenType(token);
        token->type = tokenType;
        prevToken = token;
        pushOperatorStack(operatorStack, token);
        token = getToken(tokenizer);
      }
  }
}
*/
/*
void shuntingYard(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  StackItem *poppedToken_1;
  StackItem *poppedToken_2;
  StackItem *poppedToken_operator;

  OperatorType tokenOperatorType;
  Affix operatorAffix;
  Token *token;
  Token *prevToken;
  Token *ans;
  Token *combinedPrefixWithNumber;
  Token *token_operator;
  Token *prefixToken;
  TokenType operatorType;

  token = getToken(tokenizer);
  while(token-> type != TOKEN_NULL_TYPE){
    if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
      if(operandStack->head == NULL){
        pushOperandStack(operandStack, token);
        token = getToken(tokenizer);
      }
      else if(tokenOperatorType == BINARY){
        pushOperandStack(operandStack, token);
        ans = operationOnStacks(operatorStack, operandStack);
        pushOperandStack(operandStack, ans);
        //freeToken(prevToken);
        token = getToken(tokenizer);
      }
      else if (tokenOperatorType == UNARY){
        pushBackToken(tokenizer, token);
        combinedPrefixWithNumber = combinePrefixWithToken(tokenizer, prefixToken);
        pushBackToken(tokenizer, combinedPrefixWithNumber);
        popStack(operatorStack);
        token = getToken(tokenizer);
        tokenOperatorType = BINARY;
      }
    }
    else{
      if(operatorStack->head == NULL){
        prevToken = (Token*)(operandStack->head->data);
        pushBackToken(tokenizer, token);
        tokenOperatorType = determineTokenOperatorType(tokenizer, prevToken);
        token = getToken(tokenizer);

        // TokenType was encoded during determineTokenOperatorType
        // needed to set it back else pop operator Stack will cause invalid type
        operatorType = getTokenType(token);
        token->type = operatorType;
        pushOperatorStack(operatorStack, token);
        token = getToken(tokenizer);
      }
      else{
        prevToken = (Token*)(operatorStack->head->data);
        pushBackToken(tokenizer, token);
        tokenOperatorType = determineTokenOperatorType(tokenizer, prevToken);
        token = getToken(tokenizer);
        if(tokenOperatorType == UNARY){
          prefixToken = token;
        }
        // TokenType was encoded during determineTokenOperatorType
        // needed to set it back else pop operator Stack will cause invalid type
        operatorType = getTokenType(token);
        token->type = operatorType;
        pushOperatorStack(operatorStack, token);
        token = getToken(tokenizer);
      }
    }
  }
}
/*
 *    OperandStack
 *
 *                +-----+
 *      tail--->  +  2  + -----> Item1 (token_2)
 *                +-----+
 *                +  1  + -----> Item2 (token_1)
 *                +-----+
 *         head-----^
 *  First token that popped is Item2
 *  Only then Item1
 *  Thus, token_2 and token_1 position is in reverse
 *  calculationOnTokens(token_2, token_1, token_operator);
 */


/*
OperatorType determineTokenOperatorType(Tokenizer *tokenizer, Token *prevToken){
  Affix tokenAffix;
  OperatorType tokenOperatorType;

  tokenAffix = checkTokenAffix(tokenizer, prevToken);
  tokenOperatorType = determineOperatorType(tokenAffix);
  return tokenOperatorType;
}
*/
