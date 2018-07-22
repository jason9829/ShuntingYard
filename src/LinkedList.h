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


void LinkedListAddToHead(LinkedList *List, ListItem *ItemToAdd);
void LinkedListAddToTail(LinkedList *List, ListItem *ItemToAdd);
ListItem *LinkedListRemoveFromHead(LinkedList *List);
ListItem *LinkedListRemoveFromTail(LinkedList *List);



#endif // _LINKEDLIST_H
