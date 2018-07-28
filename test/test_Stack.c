// IINCOMPLETE
#include "unity.h"
#include "Stack.h"
#include "Error.h"
#include "CException.h"
#include "Exception.h"
#include <stdarg.h>
#include <stdio.h>


void setUp(void){}
void tearDown(void){}

//    ******************************************************************
//    |  TEST UNNECESSARY                                               |
//    |  Same with LinkedList TEST                                      |
//    ******************************************************************
//    |   TEST FOR Push & Pop (WITHOUT TOKEN)                          |
//    |   FUNCTIONS TESTED                                             |
//    |   ****************                                             |
//    |  int *pushStack_wNewStackAddress(StackBlock *List,void *data); |
//    *****************************************************************

/* Starting from empty (NULL) stack then push 10 into the stack
*
*   BEFORE             AFTER
*   +------+           +------+  next
*   + NULL +           +  20  + ------> NULL
*   +------+           +------+
*             head---------^
*             tail---------^
*/

void test_pushStack_push_20_expect_20_pushed(void){
 int pushValue = 20;
 int *newStackAddress;
 StackBlock Stack = {NULL, NULL, 0};
 newStackAddress = pushStack_wNewStackAddress(&Stack,&pushValue);

 StackItem * newStackVerify;
 newStackVerify = &newStackAddress;

 TEST_ASSERT_EQUAL(newStackAddress,Stack.head);
 TEST_ASSERT_EQUAL(newStackAddress,Stack.tail);
 TEST_ASSERT_EQUAL(NULL,newStackVerify-> next-> next);
 TEST_ASSERT_EQUAL(20,newStackVerify->next->data);
 TEST_ASSERT_EQUAL(1, Stack.count);

}
/* Starting from item1(20) stack then push 21 into the stack
*
*   BEFORE             AFTER
*   +------+           +------+  next
*   +  20  +     ----->+  20  + ------> NULL
*   +------+     |     +------+
*                |     +  21  +
*              tail    +------+
*              head--------^
*/

void test_pushStack_with_value_of_20_then_push_21_expect_21_pushed(void){
int value = 20;
int pushValue = 21;
int *newStackAddress;

StackItem Item1 = {NULL,(void*) &value};
StackBlock Stack = {&Item1, &Item1, 1};

newStackAddress = pushStack_wNewStackAddress(&Stack,&pushValue);

StackItem * newStackVerify;
newStackVerify = &newStackAddress;

TEST_ASSERT_EQUAL(&Item1,newStackVerify-> next-> next);
TEST_ASSERT_EQUAL(&Item1, Stack.tail);
TEST_ASSERT_EQUAL(newStackAddress,Stack.head);
TEST_ASSERT_EQUAL(21,newStackVerify->next->data);
TEST_ASSERT_EQUAL(2, Stack.count);

}
