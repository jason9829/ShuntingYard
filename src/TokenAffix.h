#ifndef _TOKENAFFIX_H
#define _TOKENAFFIX_H

#include "Token.h"

void encodeAffix(Token *token, Affix affix);
Affix getAffix(Token *token);
TokenType getTokenType(Token *token);

#endif // _TOKENAFFIX_H
