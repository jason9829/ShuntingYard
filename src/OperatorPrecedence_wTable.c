#include "OperatorPrecedence_wTable.h"
#include "TokenInfo_AffixTable_wEvaluation.h"
#include "Token.h"
#include "Tokenizer.h"
#include "TokenAffix.h"
#include "Stack.h"
#include "Exception.h"
#include "Error.h"

#define STRONG 3
#define MEDIUM 2
#define WEAK   1

OperatorPrecedence bindingPower[50] = {
  [INFIX_PLUS] = {.bindingPower = WEAK},
  [INFIX_MINUS] = {.bindingPower = WEAK},
  [INFIX_MULTIPLY] = {.bindingPower = MEDIUM},
  [INFIX_DIVIDE] = {.bindingPower = MEDIUM},
  [PREFIX_PLUS] = {.bindingPower = STRONG},
  [PREFIX_MINUS] = {.bindingPower = STRONG},
  [OPEN_BRACKET] = {.bindingPower = 0},
  [CLOSE_BRACKET] = {.bindingPower = 0},
};

OperatorPrecedenceAndAssociativity bindingPowerAndAssociativity[50] = {
  [INFIX_PLUS] = {.bindingPower = WEAK, .associativity = LEFT_TO_RIGHT},
  [INFIX_MINUS] = {.bindingPower = WEAK,.associativity = LEFT_TO_RIGHT},
  [INFIX_MULTIPLY] = {.bindingPower = MEDIUM, .associativity = LEFT_TO_RIGHT},
  [INFIX_DIVIDE] = {.bindingPower = MEDIUM, .associativity = LEFT_TO_RIGHT},
  [PREFIX_PLUS] = {.bindingPower = STRONG, .associativity = RIGHT_TO_LEFT},
  [PREFIX_MINUS] = {.bindingPower = STRONG, .associativity = RIGHT_TO_LEFT},
  [OPEN_BRACKET] = {.bindingPower = 0, .associativity = LEFT_TO_RIGHT},
  [CLOSE_BRACKET] = {.bindingPower = 0, .associativity = LEFT_TO_RIGHT},
  [INVALID_OPERATOR] = {.bindingPower = 0, .associativity = 0},
};

OperatorPrecedenceAndAssociativity *getTokenPrecedenceAndAssociativity(Token *token){
  Affix tokenAffix;
  tokenAffix = getAffix(token);
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  switch(tokenAffix){
    case PREFIX :    if(operatorSymbol == '+'){
                      return &bindingPowerAndAssociativity[PREFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPowerAndAssociativity[PREFIX_MINUS];
                     }
                     else if (operatorSymbol == '('){
                      return &bindingPowerAndAssociativity[OPEN_BRACKET];
                     }
                     else{
                       return &bindingPowerAndAssociativity[INVALID_OPERATOR];
                     }

    case SUFFIX :    if(operatorSymbol == ')'){
                      return &bindingPowerAndAssociativity[CLOSE_BRACKET];
                      }
                      else{
                        return &bindingPowerAndAssociativity[INVALID_OPERATOR];
                      }

    case INFIX  :    if(operatorSymbol == '+'){
                      return &bindingPowerAndAssociativity[INFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPowerAndAssociativity[INFIX_MINUS];
                     }
                     else if(operatorSymbol == '*'){
                      return &bindingPowerAndAssociativity[INFIX_MULTIPLY];
                     }
                     else if(operatorSymbol == '/'){
                      return &bindingPowerAndAssociativity[INFIX_DIVIDE];
                     }
                     else{
                       return &bindingPowerAndAssociativity[INVALID_OPERATOR];
                     }

      default:  throwException(ERR_INVALID_AFFIX, token, "'%c' is an invalid operator", operatorSymbol);

  }
}

OperatorPrecedence *getTokenPrecedence(Token *token){
  Affix tokenAffix;
  tokenAffix = getAffix(token);
  char operatorSymbol;
  operatorSymbol = *((OperatorToken*)token)->str;

  switch(tokenAffix){
    case PREFIX :    if(operatorSymbol == '+'){
                      return &bindingPower[PREFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPower[PREFIX_MINUS];
                     }
                     else if (operatorSymbol == '('){
                       return &bindingPower[OPEN_BRACKET];
                     }

    case SUFFIX :
    case INFIX  :    if(operatorSymbol == '+'){
                      return &bindingPower[INFIX_PLUS];
                     }
                     else if(operatorSymbol == '-'){
                      return &bindingPower[INFIX_MINUS];
                     }
                     else if(operatorSymbol == '*'){
                      return &bindingPower[INFIX_MULTIPLY];
                     }
                     else if(operatorSymbol == '/'){
                      return &bindingPower[INFIX_DIVIDE];
                     }

      default:  throwException(ERR_INVALID_AFFIX, token, "'%c' is an invalid operator", operatorSymbol);

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

    // operator->addtoHead > token
    if((precedenceOfprevToken->bindingPower) > (precedenceOfcurrToken)->bindingPower){
      return 1;
    } // operator->addtoHead < token
    else if ((precedenceOfprevToken->bindingPower) < (precedenceOfcurrToken)->bindingPower){
      return 0;
    }
    else{
      return 2;
    }
  }
