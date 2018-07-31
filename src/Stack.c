#include "Stack.h"
#include "Exception.h"
#include "Error.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
#include <stdio.h>
#include <malloc.h>

int *pushStack_wNewStackAddress(StackBlock *List,void *data){
  Token *token = (struct Token*)malloc(sizeof(struct Token));
  token = ((Token*)(data));

  if(*(int*)(data) == NULL){
    throwSimpleError(ERR_INVALID_DATA,"Data trying to add is NULL");
  }
  else{
    StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
    if(List->head == NULL){
      if(token->type == TOKEN_INTEGER_TYPE){
        newStackItem->data = token;
      }
      else{
        newStackItem->data = *(int*)(data);
      }
      newStackItem->next = NULL;
      List->count++;
      List->head = newStackItem;
      List->tail = newStackItem;
    }
    else{
      if(token->type == TOKEN_INTEGER_TYPE){
        newStackItem->data = token;
      }
      else{
        newStackItem->data = *(int*)(data);
      }
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
  Token *token = (struct Token*)malloc(sizeof(struct Token));
  token = ((Token*)(data));

  if(token->type == TOKEN_NULL_TYPE){
      throwSimpleError(ERR_NULL_TOKEN,"Token is NULL");
  }
  else{
    if(*(int*)(data) == NULL){
    throwSimpleError(ERR_INVALID_DATA,"Data trying to add is NULL");
    }
    else{
      StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
      if(List->head == NULL){
          if(token->type == TOKEN_INTEGER_TYPE){
            newStackItem->data = token;
          }
          else{
            newStackItem->data = *(int*)(data);
          }
            newStackItem->next = NULL;
            List->count++;
            List->head = newStackItem;
            List->tail = newStackItem;
      }
      else{
        if(token->type == TOKEN_INTEGER_TYPE){
          newStackItem->data = token;
        }
        else{
          newStackItem->data = *(int*)(data);
        }
        newStackItem->next = List->head;     // Take previous node as next
        if(List->count == 1){     // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
          List->tail = newStackItem->next;              // previous node as tail
        }
        List->count++;
        List->head = newStackItem;
      }
    }
  }
}

StackItem *popStack(StackBlock *List){
  if(List->head == NULL){
    throwSimpleError(ERR_LINKEDLIST_NULL,"Empty linkedlist detected");
  }
  else{
    StackItem *poppedStack = (struct StackItem*)malloc (sizeof(struct StackItem));
    poppedStack = List->head;
    int *nextItemAddress;
    nextItemAddress = List->head->next;

    /*  List
     *             BEFORE
     *                    (remove this)          (nextItemAddress)
     *                       +-----+      next      +-----+   next
     *           head----->  |  1  |--------------> |  2  |---------> NULL
     *                       +-----+                +-----+
     *                          |
     *                      poppedStack
     *
     *             AFTER
     *                       +-----+      next
     *           head----->  |  2  |--------------> NULL
     *                       +-----+
     *
     */

    List->head->next = NULL;
    List->head = nextItemAddress;
    List->count--;
    return poppedStack;
  }
}
