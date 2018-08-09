#include "OperatorPrecedence_wTable.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define STRONGEST 2
#define WEAKEST   1

OperatorPrecedence bindingPower[50] = {
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
    throwException(ERR_INVALID_OPERATOR, token, "Do not accept '%c' operator", operatorSymbol);
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
int comparePrevTokenAndNextTokenPrecedence(Token *currToken, Token *prevToken){

  OperatorPrecedence *precedenceOfprevToken;
  OperatorPrecedence *precedenceOfcurrToken;


  precedenceOfprevToken = getTokenPrecedence(prevToken);
  precedenceOfcurrToken = getTokenPrecedence(currToken);


  if((precedenceOfprevToken->bindingPower) > (precedenceOfcurrToken)->bindingPower){
    return 1;
  }
  else if ((precedenceOfprevToken->bindingPower) < (precedenceOfcurrToken)->bindingPower){
    return 0;
  }
  else{
    return 2;
  }
}
