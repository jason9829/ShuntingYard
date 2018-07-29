#ifndef Token_H
#define Token_H

#include <stdint.h>
#include "Common.h"
#include "CException.h"
#include "Exception.h"

typedef enum {
  TOKEN_UNKNOWN_TYPE     = 0x00000000,
  TOKEN_NULL_TYPE        = 0x00000001,
  TOKEN_INVALID_TYPE     = 0x00000002,
  TOKEN_INTEGER_TYPE     = 0x00000003,
  TOKEN_OPERATOR_TYPE    = 0x00000004,
  TOKEN_FLOAT_TYPE       = 0x00000005,
  TOKEN_STRING_TYPE      = 0x00000006,
  TOKEN_IDENTIFIER_TYPE  = 0x00000007,
} TokenType;

typedef enum {
  NO_AFFIX = 0x00010000,
  PREFIX   = 0x00020000,
  INFIX    = 0x00030000,
  POSTFIX  = 0x00040000,
} Affix;

typedef enum {
  NO_ASSOCIATIVITY,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
} Associativity;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} Token;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  int value;
} IntegerToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  double value;
} FloatToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} IdentifierToken, StringToken, CharConstToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  Token *token[0];
} OperatorToken;

Token *createNullToken();
Token *createInvalidToken(char *originalString, int start, int len);
Token *createIntegerToken(int value, char *originalString);
Token *createFloatToken(double value, char *originalString);
Token *createIdentifierToken(char *str, char *originalString);
Token *createStringToken(char *str, char *originalString);
Token *createOperatorToken(char *str, char *originalString);
void freeToken(void *token);
void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo);

#endif // Token_H
