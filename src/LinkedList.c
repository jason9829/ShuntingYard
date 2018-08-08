#include "LinkedList.h"
#include <stdio.h>
#include <malloc.h>
#include "Exception.h"
#include "Error.h"


int *LinkedListAddToHead_wNewLinkedListAddress(LinkedList *List, void *data){

  if(*(int*)(data) == NULL){
    throwException(ERR_INVALID_DATA,(int*)(data),"Data trying to add is '%d',(int*)(data)");
  }
  else{
    ListItem *newLinkedList = (struct ListItem*)malloc (sizeof(struct ListItem));
    if(List->head == NULL){
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = NULL;
      List->count++;
      List->head = newLinkedList;
      List->tail = newLinkedList;
    }
    else{
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = List->head;     // Take previous node as next
      if(List->count == 1){     // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
        List->tail = newLinkedList->next;              // previous node as tail
      }
      List->count++;
      List->head = newLinkedList;
    }
    return newLinkedList;
  }
}

void LinkedListAddToHead(LinkedList *List,void *data){
  if(*(int*)(data) == NULL){
    throwException(ERR_INVALID_DATA,(int*)(data),"Data trying to add is '%d',(int*)(data)");
  }
  else{
    ListItem *newLinkedList = (struct ListItem*)malloc (sizeof(struct ListItem));
    if(List->head == NULL){
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = NULL;
      List->count++;
      List->head = newLinkedList;
      List->tail = newLinkedList;
    }
    else{
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = List->head;     // Take previous node as next
      if(List->count == 1){     // if 2 block (head->newLinkedList) take previous as tail else tail remain the same
        List->tail = newLinkedList->next;              // previous node as tail
      }
      List->count++;
      List->head = newLinkedList;
    }
  }
}
ListItem *LinkedListRemoveFromHead(LinkedList *List){
  if(List->head == NULL){
    throwException(ERR_LINKEDLIST_NULL,NULL ,"The List is empty");
  }
  else{
    ListItem *removedLinkedList = (struct ListItem*)malloc (sizeof(struct ListItem));
    removedLinkedList = List->head;
    int *nextItemAddress;
    nextItemAddress = List->head->next;
    if(List->count == 1){
      List->tail = NULL;
    }
    /*  List
     *      BEFORE
     *                   (remove this)          (nextItemAddress)
     *                       +-----+      next      +-----+   next
     *           head----->  |  1  |--------------> |  2  |---------> NULL
     *                       +-----+                +-----+
     *                     removedLinkedList
     *       AFTER
     *                       +-----+      next
     *           head----->  |  2  |--------------> NULL
     *                       +-----+
     */

    List->head->next = NULL;
    List->head = nextItemAddress;

    List->count--;
    return removedLinkedList;
  }
}
