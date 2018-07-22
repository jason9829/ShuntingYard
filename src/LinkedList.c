#include "LinkedList.h"
#include <stdio.h>
#include <malloc.h>


// ItemToAdd->next neccessary?
void LinkedListAddToHead(LinkedList *List, ListItem *ItemToAdd){
  ListItem *newData = (struct ListItem*)malloc (sizeof(struct ListItem));
 if(List->head == NULL && List->tail == NULL){
    newData->data = *(int*)(ItemToAdd->data);
    ItemToAdd->next = NULL;
    newData->next = NULL;
    List->count++;
    List->head = newData;
    List->tail = ItemToAdd->next;
  }
  else{
    newData->data = *(int*)(ItemToAdd->data);
    newData->next = List->head;     // Take previous node as next
    List->count++;
    List->head = newData;           // Point to the next node
    List->tail = ItemToAdd->next;
  }
}
