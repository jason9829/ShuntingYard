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
  token = (Token*)(data);

  if(token->type == TOKEN_NULL_TYPE){
      throwException(ERR_NULL_TOKEN, List ,"Token is NULL", token->str);
  }
    else{
      StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
      if(List->head == NULL){
          if(token->type == TOKEN_INTEGER_TYPE){
            newStackItem->data = (IntegerToken*)(data);
          }
          else if(token->type == TOKEN_FLOAT_TYPE){
            newStackItem->data = (FloatToken*)(data);
          }
          else if(token->type == TOKEN_OPERATOR_TYPE){
            newStackItem->data = (OperatorToken*)(data);
          }
          else if(token->type == TOKEN_IDENTIFIER_TYPE){
            newStackItem->data = (IdentifierToken*)(data);
          }
          else if (token->type == TOKEN_STRING_TYPE){
            newStackItem->data = (StringToken*)(data);
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
        else if(token->type == TOKEN_FLOAT_TYPE){
          newStackItem->data = (FloatToken*)(data);
        }
        else if(token->type == TOKEN_OPERATOR_TYPE){
          newStackItem->data = (OperatorToken*)(data);
        }
        else if(token->type == TOKEN_IDENTIFIER_TYPE){
          newStackItem->data = (IdentifierToken*)(data);
        }
        else if (token->type == TOKEN_STRING_TYPE){
          newStackItem->data = (StringToken*)(data);
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
      throwException(ERR_NULL_TOKEN, List ,"Token is NULL ");
  }
  StackItem *newStackItem = (struct StackItem*)malloc (sizeof(struct StackItem));
  if(List->head == NULL){
      if(token->type == TOKEN_INTEGER_TYPE){
        newStackItem->data = (IntegerToken*)(data);
      }
      else if(token->type == TOKEN_FLOAT_TYPE){
        newStackItem->data = (FloatToken*)(data);
      }
      else if(token->type == TOKEN_OPERATOR_TYPE){
        newStackItem->data = (OperatorToken*)(data);
      }
      else if(token->type == TOKEN_IDENTIFIER_TYPE){
        newStackItem->data = (IdentifierToken*)(data);
      }
      else if (token->type == TOKEN_STRING_TYPE){
        newStackItem->data = (StringToken*)(data);
      }
      else{ // encodedToken
        //newStackItem->data = *(int*)(data);
        newStackItem->data = (Token*)(data);
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
    else if(token->type == TOKEN_FLOAT_TYPE){
      newStackItem->data = (FloatToken*)(data);
    }
    else if(token->type == TOKEN_OPERATOR_TYPE){
      newStackItem->data = (OperatorToken*)(data);
    }
    else if(token->type == TOKEN_IDENTIFIER_TYPE){
      newStackItem->data = (IdentifierToken*)(data);
    }
    else if (token->type == TOKEN_STRING_TYPE){
      newStackItem->data = (StringToken*)(data);
    }
    else{ // encodedToken
      //newStackItem->data = *(int*)(data);
      newStackItem->data = (Token*)(data);
    }
    newStackItem->next = List->head;     // Take previous node as next
    if(List->count == 1){                // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
      List->tail = newStackItem->next;   // previous node as tail
    }
    List->count++;
    List->head = newStackItem;
  }
}

StackItem *popStack(StackBlock *List){
  if(List->head == NULL){
    throwException(ERR_LINKEDLIST_NULL,List ,"The Stack is empty");
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
    if(List->count == 1){
      List->tail = NULL;
    }
    List->count--;
    return poppedStack;
  }
}
