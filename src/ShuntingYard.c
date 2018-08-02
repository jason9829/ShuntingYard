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
  //Token *Ans;
  Token *Ans = (struct Token*)malloc (sizeof(struct Token));
  char operation;
  operation = *((OperatorToken*)token_operator)->str;

  switch (operation) {
    case '+':
    Ans = additionOf2Tokens(token_1, token_2);
    return Ans;
    break;
    case '-':
    Ans = subtractionOf2Tokens(token_1, token_2);
    return Ans;
    break;
    case '*':
    //((IntegerToken *)Ans)->value = v1 * v2;
    break;
    case '/':
    //((IntegerToken *)Ans)->value = v1 / v2;
    break;
    default: throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator detected");
  }

}

Token *additionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;
  //Token *Answer;
  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 + v2;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 + v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 + v2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 + v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
  throwSimpleError(ERR_INVALID_OPERAND,"Operand type is invalid");
  }
}

Token *subtractionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 - v2;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 - v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 - v2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 - v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
  throwSimpleError(ERR_INVALID_OPERAND,"Operand type is invalid");
  }

}


Token *multiplicationOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 * v2;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 * v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 * v2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 * v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
  throwSimpleError(ERR_INVALID_OPERAND,"Operand type is invalid");
  }

}


Token *divisionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 / v2;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 / v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 / v2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 / v_2;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
  throwSimpleError(ERR_INVALID_OPERAND,"Operand type is invalid");
  }

}
