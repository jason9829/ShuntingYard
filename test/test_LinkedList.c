#include "unity.h"
#include "LinkedList.h"
#include "Error.h"
#include "Common.h"
#include "CException.h"
#include "Exception.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

void setUp(void){}
void tearDown(void){}

//    *************************************************************
//    |   TEST FOR LINKEDLIST (WITHOUT TOKEN)                     |
//    |   FUNCTIONS TESTED                                        |
//    |   ****************                                        |
//    |   int *LinkedListAddToHead(LinkedList *List,void *data)   |
//    |   ListItem *LinkedListRemoveFromHead(LinkedList *List)    |
//    *************************************************************
// If any Data trying to add is NULL, throw exception
void test_LinkedListAddToHead_given_empty_linked_list_add_NULL_expect_ERR_DATA_NULL(void){
  CEXCEPTION_T e;
  int value = NULL ;

  LinkedList List = {NULL, NULL , 0};
  ListItem Item = {NULL, (void*) &value};

  Try{
    LinkedListAddToHead(&List,&value);
    TEST_FAIL_MESSAGE("Expect ERR_DATA_NULL. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_INVALID_DATA, e->errorCode);
    freeError(e);
  }
}

// add char into the linked list, typecast int* so cant test the data
void test_LinkedListAddToHead_given_empty_linked_list_add_char_a_expect_item_inserted(void){
  char value = 'a';
  int *newLinkedList_ptr;

  LinkedList List = {NULL, NULL , 0};

  newLinkedList_ptr = LinkedListAddToHead_wNewLinkedListAddress(&List,&value);
  ListItem *newLinkedList_verify;             // just to check the next and data of newLinkedList (can't access to newLinkedList at here)
  newLinkedList_verify = &newLinkedList_ptr;  // point to the newLinkedList

  TEST_ASSERT_EQUAL(newLinkedList_ptr,List.tail);
  TEST_ASSERT_EQUAL(newLinkedList_ptr,List.head);
  TEST_ASSERT_EQUAL(NULL,newLinkedList_verify->next->next); // newLinkedList_verify->next->next same as newLinkedList->next
  TEST_ASSERT_EQUAL(1,List.count);
}

/*
 *  Starting from an empty linked-list, add item 1 into it
 *  BEFORE          AFTER
 *  head ------     head------------------> item1 ---> address unknown
 *            |           next-----> NULL    ^
 *  tail ------     tail---------------------|
 *            |
 *  count =0  --    count =1
 */
void test_LinkedListAddToHead_given_empty_linked_list_add_1_expect_item_inserted(void){
  int value =1 ;
  int *newLinkedList_ptr;

  LinkedList List = {NULL, NULL , 0};

  newLinkedList_ptr = LinkedListAddToHead_wNewLinkedListAddress(&List,&value);
  ListItem *newLinkedList_verify;             // just to check the next and data of newLinkedList (can't access to newLinkedList at here)
  newLinkedList_verify = &newLinkedList_ptr;  // point to the newLinkedList

  TEST_ASSERT_EQUAL(newLinkedList_ptr, List.tail);
  TEST_ASSERT_EQUAL(newLinkedList_ptr, List.head);
  TEST_ASSERT_EQUAL(NULL, newLinkedList_verify->next->next);
  TEST_ASSERT_EQUAL(1, newLinkedList_verify->next->data);
  TEST_ASSERT_EQUAL(1, List.count);

}

/*
 *  Starting from an linked-list with item 1 ,add item 2 into it
 *  BEFORE                 AFTER
 *  head ------> item1     head ------> newLinkedList
 *              next---                  next.item1-----
 *  tail --------^    |    tail------------>item1      |
 *  count=1          --    next. newLinkedList-^      --
 *                         count=2
 */

void test_LinkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_item_1(void){
  int value1 =1, new_value =20;
  int *newLinkedList_ptr;

  ListItem Item1 = {NULL,(void*) &value1};
  LinkedList List = {&Item1, NULL , 1};

  newLinkedList_ptr = LinkedListAddToHead_wNewLinkedListAddress(&List,&new_value);
  ListItem *newLinkedList_verify;             // just to check the next and data of newLinkedList (can't access to newLinkedList at here)
  newLinkedList_verify = &newLinkedList_ptr;  // point to the newLinkedList

  TEST_ASSERT_EQUAL(&Item1,List.tail);
  TEST_ASSERT_EQUAL(newLinkedList_ptr,List.head);
  TEST_ASSERT_EQUAL(&Item1,newLinkedList_verify->next->next);
  TEST_ASSERT_EQUAL(20,newLinkedList_verify->next->data);
  TEST_ASSERT_EQUAL(2,List.count);

}

/*
 *  Starting from an empty linked-list, try to remove item but nothing to remove so should be NULL
 *  BEFORE          AFTER
 *  head ------     head----------|
 *            |           next-----
 *  tail ------     tail          |
 *            |       |------->  --
 *  count =0  --    count=1
 * return ERR_LINKEDLIST_EMPTY
 */

void test_LinkedListRemoveFromHead_given_empty_linked_list_remove_expect_ERR_LINKEDLIST_NULL(void){
  CEXCEPTION_T e;
  LinkedList List = {NULL, NULL ,  0};
  ListItem Item = {NULL,  (void *) NULL};

  Try{
    LinkedListRemoveFromHead(&List);
    TEST_FAIL_MESSAGE("Expect ERR_LINKEDLIST_NULL. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_LINKEDLIST_NULL, e->errorCode);
    freeError(e);
  }

  TEST_ASSERT_EQUAL(NULL,List.head);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(0,List.count);
}

/*
 *  Starting from an linked-list with item 1 then,remove it
 *  BEFORE                 AFTER
 *  head ------> item1     head------------->NULL
 *              next---    next------------->NULL
 *  tail --------^    |    tail------------->NULL
 *  count=1          --     count=0
 */

void test_LinkedListRemoveFromHead_given_linked_list_with_item_1_expect_NULL_after_remove(void){
  int value1 = 1;

  ListItem *removedLinkedList;
  ListItem Item1 = {NULL,  (void *) &value1};
  LinkedList List = {&Item1, NULL , 1};

  removedLinkedList = LinkedListRemoveFromHead(&List);

  TEST_ASSERT_EQUAL(NULL,List.head);
  TEST_ASSERT_EQUAL(NULL,Item1.next);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(0,List.count);
  TEST_ASSERT_EQUAL(&Item1,removedLinkedList);
}

/*
 *  Starting from an linked-list with item 1 ,remove item 1 from it
 *  BEFORE                                      AFTER
 *  head ------> item1                        head-----> item2
 *              next-----> item2                           ^   next----->NULL
 *  tail --------^    next.item2----->NULL    tail---------|
 *  count=2           tail----> item2          count=1
 */

 void test_LinkedListRemoveFromHead_given_linked_list_with_item_2_expect_item1_remove(void){
   int value1 =1, value2 =2;

   ListItem *removedLinkedList;
   ListItem Item2 = {NULL,(void*) &value2};
   ListItem Item1 ={&Item2,(void*) &value1};
   LinkedList List = {&Item1, &Item2 , 2};

   removedLinkedList = LinkedListRemoveFromHead(&List);

   TEST_ASSERT_EQUAL(NULL, Item1.next);
   TEST_ASSERT_EQUAL(&Item2, List.head);
   TEST_ASSERT_EQUAL(&Item2, List.tail);
   TEST_ASSERT_EQUAL(NULL, Item2.next);
   TEST_ASSERT_EQUAL(1, List.count);
   TEST_ASSERT_EQUAL(&Item1,removedLinkedList);
 }

/*  Starting from LinkedList with Item1, Item2 and Item3, then remove Item1
 *      BEFORE
 *      head-----------> item1     _---> item2       ---> item3
 *                next.item1_______| next.item2------|       ^   next.item3-----
 *                                                           |                 |
 *      tail--------------------------------------------------                NULL
 *
 *      AFTER
 *      head-----------> item2   -----> item3
 *              next.item2_______|      ^     next.item3-------
 *                 tail-----------------|                      |
 *                                                            NULL
 *      next.item1----> NULL
 *
 */
 void test_LinkedListRemoveFromHead_given_linked_list_with_item_1_item_2_item_3_expect_item1_remove(void){
   int value1 =1, value2 =2, value3 = 3;

   ListItem *removedLinkedList;
   ListItem Item3 = {NULL,(void*) &value3};
   ListItem Item2 = {&Item3,(void*) &value2};
   ListItem Item1 ={&Item2,(void*) &value1};
   LinkedList List = {&Item1, &Item3 , 3};

   removedLinkedList = LinkedListRemoveFromHead(&List);

   TEST_ASSERT_EQUAL(NULL, Item1.next);
   TEST_ASSERT_EQUAL(&Item2, List.head);
   TEST_ASSERT_EQUAL(&Item3,Item2.next);
   TEST_ASSERT_EQUAL(&Item3, List.tail);
   TEST_ASSERT_EQUAL(NULL, Item3.next);
   TEST_ASSERT_EQUAL(2, List.count);
   TEST_ASSERT_EQUAL(&Item1,removedLinkedList);
 }
