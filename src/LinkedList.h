#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct ListItem ListItem;
struct ListItem{
  ListItem *next;
  void *data;
};

typedef struct LinkedList LinkedList;
struct LinkedList{
  ListItem *head;
  ListItem *tail;
  int count;
};

// Both addtoHead function have same code
// but int* func return the address  of newLinkedList
int *LinkedListAddToHead_wNewLinkedListAddress(LinkedList *List,void *data);
void LinkedListAddToHead(LinkedList *List,void *data);

void LinkedListAddToTail(LinkedList *List,void *data);
ListItem *LinkedListRemoveFromHead(LinkedList *List);
ListItem *LinkedListRemoveFromTail(LinkedList *List);


#endif // _LINKEDLIST_H
