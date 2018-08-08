#ifndef _STACK_H
#define _STACK_H

typedef struct StackItem StackItem;
struct StackItem{
  StackItem *next;
  void *data;
};

typedef struct StackBlock StackBlock;
struct StackBlock{
  StackItem *head;
  StackItem *tail;
  int count;
};


// Both addtoHead function have same code
// but int* func return the address  of newStackAddress
int *pushStack_wNewStackAddress(StackBlock *List,void *data);
void pushStack(StackBlock *List,void *data);

StackItem *popStack(StackBlock *List);



#endif // _STACK_H
