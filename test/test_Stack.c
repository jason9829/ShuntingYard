#include "unity.h"
#include "Stack.h"
#include "Error.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Common.h"
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
*   BEFORE                        AFTER
*   +------+  next                  +------+  next
*   +  20  +-------> NULL     ----->+  20  + ------> NULL
*   +------+                  |     +------+
*                             |     +  21  +
*                           tail    +------+
*                           head--------^
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

/*  Starting from item1(21) and item2(20) then pop the item1(21)
 *
 *    BEFORE                                AFTER
 *          +------+  next                  +------+  next
 *    ----->+  20  + ------> NULL           +  20  + -------> NULL
 *    |     +------+                        +------+
 *    |     +  21  +                 head-------^
 *  tail    +------+                 tail-------^
 *  head--------^
 */

void test_popStack_with_item1_and_item2_expect_item1_popped(void){
  int value1 = 21, value2 = 20;

  StackItem *poppedStack;
  StackItem Item2 = {NULL,(void*) &value2};
  StackItem Item1 = {&Item2,(void*) &value2};

  StackBlock Stack = {&Item1, &Item2, 2};

  poppedStack = popStack(&Stack);

  TEST_ASSERT_EQUAL(&Item2, Stack.head);
  TEST_ASSERT_EQUAL(&Item2, Stack.tail);
  TEST_ASSERT_EQUAL(NULL, Item2.next);
  TEST_ASSERT_EQUAL(&Item1, poppedStack);
  TEST_ASSERT_EQUAL(1, Stack.count);
}

//    *************************************************************
//    |   TEST FOR LINKEDLIST (TOKEN)                             |
//    |   FUNCTIONS TESTED                                        |
//    |   ****************                                        |
//    |   int *LinkedListAddToHead(LinkedList *List,void *data)   |
//    |   ListItem *LinkedListRemoveFromHead(LinkedList *List)    |
//    *************************************************************

void test_LinkedListAddToHead_given_nullToken_expect_ERR_NULL_TOKEN(void){
   CEXCEPTION_T e;

   StackBlock Stack = {NULL,NULL,0};

   Token *token = NULL;
   Tokenizer *tokenizer = NULL;

   tokenizer = createTokenizer("  ");
   token = getToken(tokenizer);
   Try{
     pushStack(&Stack,token);
   }
   Catch(e){
     printf(e->errorMsg);
     TEST_ASSERT_EQUAL(ERR_NULL_TOKEN, e->errorCode);
     freeError(e);
   }
     TEST_ASSERT_NOT_NULL(token);
}
