#include "ShuntingYard.h"
#include "TokenAffix.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"


/*Token operateOnTokens(StackBlock *operatorStack, StackBlock *operandStack){
  if(operatorStack->head == NULL || operandStack->head == NULL){
    throwSimpleError(ERR_STACK_NULL, "Empty Stack detected");
  }
  else{
    Token *token_1;
    Token *token_2;
    Token *token_operator;
    if(operatorStack->count >=1 && operandStack->count >=2){
      popStack()
    }
  }
}
*/
Token *calculationOnTokens(Token *token_1, Token *token_2, Token *token_operator){
  Token *Ans;
  char operation;
  operation = *((OperatorToken*)token_operator)->str;

  int v1,v2;
  v1 = ((IntegerToken *)token_1)->value;
  v2 = ((IntegerToken *)token_2)->value;

  switch (operation) {
    case '+':
    ((IntegerToken *)Ans)->value = v1 + v2;
    break;
    case '-':
    ((IntegerToken *)Ans)->value = v1 - v2;
    break;
    case '*':
    ((IntegerToken *)Ans)->value = v1 * v2;
    break;
    case '/':
    ((IntegerToken *)Ans)->value = v1 / v2;
    break;
    default: throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator detected");
  }

  return Ans;

}

TokenType typecastTokenType(Token *token){

}
