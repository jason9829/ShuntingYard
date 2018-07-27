#include "Stack.h"
#include "LinkedList.h"
#include "Exception.h"
#include "Error.h"
#include <stdio.h>
#include <malloc.h>


void pushStack(LinkedList *Stack,void *data){
  int *newItemAddress;
  newItemAddress = LinkedListAddToHead(Stack, data);
}
