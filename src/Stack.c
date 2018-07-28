// INCOMPLETE

#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include <stdio.h>
#include <malloc.h>

int *pushStack_wNewStackAddress(StackBlock *List,void *data){
  if(*(int*)(data) == NULL){
    throwSimpleError(ERR_INVALID_DATA,"Data trying to add is NULL");
  }
  else{
    StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
    if(List->head == NULL){
      newStackItem->data = *(int*)(data);
      newStackItem->next = NULL;
      List->count++;
      List->head = newStackItem;
      List->tail = newStackItem;
    }
    else{
      newStackItem->data = *(int*)(data);
      newStackItem->next = List->head;     // Take previous node as next
      if(List->count == 1){     // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
        List->tail = newStackItem->next;              // previous node as tail
      }
      List->count++;
      List->head = newStackItem;
    }
    return newStackItem;
  }
}

void pushStack(StackBlock *List,void *data){
  if(*(int*)(data) == NULL){
    throwSimpleError(ERR_INVALID_DATA,"Data trying to add is NULL");
  }
  else{
    StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
    if(List->head == NULL){
      newStackItem->data = *(int*)(data);
      newStackItem->next = NULL;
      List->count++;
      List->head = newStackItem;
      List->tail = newStackItem;
    }
    else{
      newStackItem->data = *(int*)(data);
      newStackItem->next = List->head;     // Take previous node as next
      if(List->count == 1){     // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
        List->tail = newStackItem->next;              // previous node as tail
      }
      List->count++;
      List->head = newStackItem;
    }
  }
}
