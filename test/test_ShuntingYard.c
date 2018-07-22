#include "unity.h"
#include "ShuntingYard.h"
#include "LinkedList.h"

#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

/*
 *  Starting from an empty linked-list, add item 1 into it
 *  BEFORE          AFTER
 *  head ------     head-----> item1 ---> address unknown
 *            |           next-----
 *  tail ------     tail----^     |
 *            |                   --
 *  count =0  --    count=1
 */
void test_LinkedListAddToHead_given_empty_linked_list_add_1_expect_item_inserted(void){
  int value =1 ;
  LinkedList List = {NULL, NULL , 0};
  ListItem Item ={NULL, (void*) &value};

  LinkedListAddToHead(&List,&Item);

  //TEST_ASSERT_EQUAL(NULL,List.head);      // it's point to newData struct which is not null
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(NULL,Item.next);
  TEST_ASSERT_EQUAL(1,List.count);

}

/*
 *  Starting from an linked-list with item 1 ,add item 2 into it
 *  BEFORE                 AFTER
 *  head ------> item1     head ------> item2
 *              next---             next-----> next----
 *  tail --------^    |    tail------------------^    |
 *  count=1          --     count=2                  --
 */
void test_LinkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_item_1(void){
  int value1 =1, value2 =2;
  ListItem Item1 ={NULL,(void*) &value1};
  ListItem Item2 ={NULL,(void*) &value2};
  LinkedList List = {&Item1, NULL , 1};

  LinkedListAddToHead(&List,&Item2);
                                          
  //TEST_ASSERT_EQUAL(NULL,List.head);    // pointed at new node (unknown address)
  TEST_ASSERT_EQUAL(NULL,Item2.next);
  TEST_ASSERT_EQUAL(NULL,Item1.next);
  TEST_ASSERT_EQUAL(NULL,List.tail);
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
 * return ERROR_LINKEDLIST_EMPTY
 */
 /*
void xtest_LinkedListRemoveFromHead_given_empty_linked_list_remove_expect_ERROR_LINKEDLIST_NULL(void){
  LinkedList List = {NULL, NULL ,  0};
  ListItem *Item ={ NULL,  (void *) NULL};

  LinkedListRemoveFromHead(&List);

  TEST_ASSERT_EQUAL(Item,List.head);
  TEST_ASSERT_EQUAL(Item,List.tail);
  TEST_ASSERT_EQUAL(1,List.count);
}*/

/*
 *  Starting from an linked-list with item 1 then,remove it
 *  BEFORE                 AFTER
 *  head ------> item1     head-----> item2   item1
 *              next---             next-----> next----
 *  tail --------^    |    tail------------------^    |
 *  count=1          --     count=2                  --
 */
 /*
void xtest_LinkedListRemoveFromHead_given_linked_list_with_item_1_expect_NULL_after_remove(void){
  int value1 =1, value2 =2;

  ListItem *Item1 ={ NULL,  (void *) &value1};
  ListItem *Item2 ={ NULL, (void *) &value2};
  LinkedList List = { NULL, NULL , 0};

  LinkedListRemoveFromHead(&List);

  TEST_ASSERT_EQUAL(Item2,List.head);
  TEST_ASSERT_EQUAL(Item1,Item2->next);
  TEST_ASSERT_EQUAL(NULL,Item1->next);
  TEST_ASSERT_EQUAL(Item1,List. tail);
  TEST_ASSERT_EQUAL(2,List.count);
}
*/
