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

void pushTokensToRespectiveStack(Tokenizer *tokenizer, StackBlock *operatorStack, StackBlock *operandStack){
  Token *token ;
  Token *prevToken;
  TokenType operatorType;

  token = getToken(tokenizer);
  while(token-> type != TOKEN_NULL_TYPE){
    if(token->type == TOKEN_FLOAT_TYPE || token->type == TOKEN_INTEGER_TYPE){
      pushOperandStack(operandStack, token);
      prevToken = token;
      token = getToken(tokenizer);
    }
    else if(token->type == TOKEN_OPERATOR_TYPE){
      pushBackToken(tokenizer, token); // In the function need to get OperatorToken from tokenizer to compare
      checkTokenAffixAndEncodeAffix(tokenizer, prevToken);  // In the function pushBack so need to get again
      token = getToken(tokenizer);
      pushOperatorStack(operatorStack, token);
      prevToken = token;
      token = getToken(tokenizer);
    }
  }

}
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
      freeToken(token_1);
      freeToken(token_2);
      freeToken(token_operator);
      //pushStack(operandStack, ans);
      return ans;
    }
    //else{
    //  throwSimpleError(ERR_STACK_INSUFFICIENT, "Either count in operatorStack or operandStack is insufficient to operate");
    //}
}

void pushOperandStack(StackBlock *operandStack, Token *token){
  pushStack(operandStack, token);
}

void pushOperatorStack(StackBlock *operatorStack, Token *token){
  pushStack(operatorStack, token);
}


/*
OperatorType determineTokenOperatorType(Tokenizer *tokenizer, Token *prevToken){
  Affix tokenAffix;
  OperatorType tokenOperatorType;

  tokenAffix = checkTokenAffix(tokenizer, prevToken);
  tokenOperatorType = determineOperatorType(tokenAffix);
  return tokenOperatorType;
}
*/
