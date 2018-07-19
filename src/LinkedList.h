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

void LinkedListAddToHead(LinkedList *list, ListItem *itemToAdd);
void LinkedListAddToTail(LinkedList *list, ListItem *itemToAdd);
ListItem *LinkedListRemoveFromHead(LinkedList *list);
ListItem *LinkedListRemoveFromTail(LinkedList *list);

#endif // _LINKEDLIST_H
