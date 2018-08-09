#include "Exception.h"
#include "CException.h"

#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>

/*
void throwSimpleError(int errorCode, char *errorMsg) {
  Exception *ex = (Exception *)malloc(sizeof(Exception));
	ex->errorCode = errorCode;
	ex->errorMsg = errorMsg;
	Throw(ex);
}

void freeError(Exception *ex){
  if(ex) {
    if(ex->errorMsg)
    free(ex);
  }
}
*/
