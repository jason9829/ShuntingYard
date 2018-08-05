#include "OperatorPrecedence_wTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define STRONGEST 2
#define WEAKEST   1

OperatorPrecedence bindingPower[100] = {
  ['+'] = {.bindingPower = WEAKEST},
  ['-'] = {.bindingPower = WEAKEST},
  ['*'] = {.bindingPower = STRONGEST},
  ['/'] = {.bindingPower = STRONGEST}
};

OperatorPrecedence *getTokenPrecedence(Token *token){
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  if(operatorSymbol == '+'){
    return &bindingPower['+'];
  }
  else if(operatorSymbol == '-'){
    return &bindingPower['-'];
  }
  else if(operatorSymbol == '*'){
    return &bindingPower['*'];
  }
  else if(operatorSymbol == '/'){
    return &bindingPower['/'];
  }
  else{
    throwSimpleError(ERR_INVALID_OPERATOR, "Invalid operator detected");
  }
}

// Example
//
//     operatorStack
//            +-----+
//  tail-->   +  *  + <---
//            +-----+    | next
//            +  -  +  __|
//            +-----+
//      head----^
//   *For this example expect return '0'
//   i) next(tail) operator precedence is higher return 0
//  ii) current(head) operator precedence is higer return 1
// iii) both operator precedence are same return 2
int compareCurrTokenAndNextTokenPrecedence(Tokenizer *tokenizer){
  Token *token_1;
  Token *token_2;

  OperatorPrecedence *precedenceOftoken_1;
  OperatorPrecedence *precedenceOftoken_2;

  token_1 = getToken(tokenizer);
  token_2 = getToken(tokenizer);

  precedenceOftoken_1 = getTokenPrecedence(token_1);
  precedenceOftoken_2 = getTokenPrecedence(token_2);

  pushBackToken(tokenizer, token_2);
  pushBackToken(tokenizer, token_1);
  if((precedenceOftoken_1->bindingPower) > (precedenceOftoken_2)->bindingPower){
    return 1;
  }
  else if ((precedenceOftoken_1->bindingPower) < (precedenceOftoken_2)->bindingPower){
    return 0;
  }
  else{
    return 2;
  }
}
