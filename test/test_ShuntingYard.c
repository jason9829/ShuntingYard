#include "unity.h"
#include "ShuntingYard.h"
#include "LinkedList.h"

void setUp(void){}
void tearDown(void){}

/*
 *  Starting from an empty linked-list, add item 1 into it
 *  BEFORE          AFTER
 *  head ------     head-----> item1
 *            |           next-----
 *  tail ------     tail----^     |
 *            |                   --
 *  count =0  --    count=1
 */
void test_LinkedListAddToHead_given_empty_linked_list_add_1_expect_item_inserted(void){
  LinkedList List = {.head= NULL, .tail= NULL , .count= 0};
  int value =1 ;
  ListItem *Item ={.next= NULL, .data= (void *) &value};

  LinkedListAddToHead(&List,Item);

  TEST_ASSERT_EQUAL(NULL,List.head);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(1,List.count);
}

/*
 *  Starting from an linked-list with item 1 ,add item 2 into it
 *  BEFORE                 AFTER
 *  head ------> item1
 *              next---             next-----> next----
 *  tail --------^    |    tail------------------^    |
 *  count=1          --     count=2                  --
 */
void test_LinkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_item_1(void){
  ListItem *Item1 ={.next= NULL, .data= (void *) &value1};
  ListItem *Item2 ={.next= NULL, .data= (void *) &value2};
  LinkedList List = {.head= NULL, .tail= NULL , .count= 1};

  int value =1, value2 =2;

  LinkedListAddToHead(&list,Item2);

  TEST_ASSERT_EQUAL(Item2,List.head);
  TEST_ASSERT_EQUAL(Item1,Item2->next);
  TEST_ASSERT_EQUAL(NULL,Item1->next);
  TEST_ASSERT_EQUAL(Item1,List.tail);
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
 */
void test_LinkedListRemoveFromHead_given_empty_linked_list_remove_expect_NULL(void){
  LinkedList List = {.head= NULL, .tail= NULL , .count= 0};
  ListItem *Item ={.next= NULL, .data= (void *) &NULL};

  LinkedListRemoveFromHead(&List,Item);

  TEST_ASSERT_EQUAL(Item,List.head);
  TEST_ASSERT_EQUAL(Item,List.tail);
  TEST_ASSERT_EQUAL(1,List.count);
}

/*
 *  Starting from an linked-list with item 1 ,add item 2 into it
 *  BEFORE                 AFTER
 *  head ------> item1     head-----> item2   item1
 *              next---             next-----> next----
 *  tail --------^    |    tail------------------^    |
 *  count=1          --     count=2                  --
 */
void test_LinkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_item_1(void){
  ListItem *Item1 ={.next= NULL, .data= (void *) &value1};
  LinkedList List = {.head= NULL, .tail= NULL , .count= 0};

  int value =1, value2 =2;

  LinkedListRemoveFromHead(&list,Item1);

  TEST_ASSERT_EQUAL(Item2,List.head);
  TEST_ASSERT_EQUAL(Item1,Item2->next);
  TEST_ASSERT_EQUAL(NULL,Item1->next);
  TEST_ASSERT_EQUAL(Item1,List.tail);
  TEST_ASSERT_EQUAL(2,List.count);
}
