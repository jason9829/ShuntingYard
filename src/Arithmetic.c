#include "Arithmetic.h"
#include "TokenAffix.h"
#include "Stack.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"
#include <malloc.h>

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
    Ans = multiplicationOf2Tokens(token_1, token_2);
    return Ans;
    break;
    case '/':
    Ans = divisionOf2Tokens(token_1, token_2);
    return Ans;
    break;
    default: throwException(ERR_INVALID_OPERATOR, token_operator, "Operator '%c' is invalid" ,operation);
  }

}

Token *additionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;
  //Token *Answer;
  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (IntegerToken*)Answer;
    int answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 + v2;
    answer = ((IntegerToken*)Answer)->value ;
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
  throwException(ERR_INVALID_OPERAND, token_1 , " '%s' or '%s' is invalid for addition", token_1 ->str, token_2->str);
  }
}

Token *subtractionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    int Ans;
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 - v2;
    Ans = ((IntegerToken*)Answer)->value ;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 - v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 - v2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 - v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
  throwException(ERR_INVALID_OPERAND, token_1 , " '%s' or '%s' is invalid for subtraction", token_1 ->str, token_2->str);

  }

}

Token *multiplicationOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    int Ans;
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 * v2;
    Ans = ((IntegerToken*)Answer)->value ;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 * v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 * v2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 * v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
throwException(ERR_INVALID_OPERAND, token_1 , " '%s' or '%s' is invalid for multiplication", token_1 ->str, token_2->str);
  }

}


Token *divisionOf2Tokens(Token *token_1, Token *token_2){

  int v1 = 0, v2= 0;
  float v_1 = 0,v_2 = 0;

  Token *Answer = (struct Token*)malloc (sizeof(struct Token));

  if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    int Ans;
    (IntegerToken*)Answer;
    v1 = ((IntegerToken *)token_1)->value;
    v2 = ((IntegerToken *)token_2)->value;
    ((IntegerToken*)Answer)->value = v1 / v2;
    Ans = ((IntegerToken*)Answer)->value ;
    Answer->type = TOKEN_INTEGER_TYPE;    // type corrupted when check with codelite
    return Answer;
  }
  else if(token_1->type == TOKEN_INTEGER_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v1  = ((IntegerToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v1 / v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_INTEGER_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v2 = ((IntegerToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 / v2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else if(token_1->type == TOKEN_FLOAT_TYPE && token_2->type == TOKEN_FLOAT_TYPE){
    (FloatToken*)Answer;
    v_1 = ((FloatToken*)token_1)->value;
    v_2 = ((FloatToken*)token_2)->value;
    ((FloatToken*)Answer)->value = v_1 / v_2;
    float Ans;
    Ans = ((FloatToken*)Answer)->value ;
    Answer->type = TOKEN_FLOAT_TYPE;
    return Answer;
  }
  else{
    throwException(ERR_INVALID_OPERAND, token_1 , " %s' or '%s' is invalid for division", token_1 ->str, token_2->str);
  }
}
