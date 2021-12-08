/*
 * This file uses the Acutest unit testing framework to test the functionality
 * you implemented in this assignment.  Each function you wrote will have one
 * or more unit tests associated with it.  You can find more about the
 * Acutest framework here: https://github.com/mity/acutest.
 */

#include <stdio.h>
#include <stdlib.h>

#include "acutest.h"

#include "link.h"
#include "stack.h"
#include "queue.h"
#include "list_reverse.h"
#include "queue_from_stacks.h"
#include "stack_from_queues.h"

/*
 * These are prototypes for auxilliary functions used in some of the tests.
 * The function definitions are at the bottom of this file.
 */
struct link* list_from_array(int* array, int n);
void list_print(struct link* head);
void list_free(struct link* head);


/****************************************************************************
 **
 ** list_reverse() tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for list_reverse().  It specifically
 * tests reversing a list containing 16 elements.  The original ordering of
 * the list (before calling list_reverse()) is stored in an array.  This
 * function then performs three specific kinds of tests:
 *
 *   * It tests to make sure the reversed list is not NULL.
 *   * It tests to make sure that the i'th element in the reversed list is
 *     equal to the correct value from the original list by comparing to
 *     the (n - 1 - i)'th in the array that holds the original ordering of
 *     the list.
 *   * It tests to make sure the reversed list has the same length as the
 *     original list.  It does this by verifying that the loop that compares
 *     the elements of the reversed list to the elements of the array doesn't
 *     exit before all of the elements in both the list and the array are
 *     examined.
 */
void test_regular_list_reverse() {
  int i, n = 16;
  int* array = malloc(n * sizeof(int));
  struct link* list, * curr;

  /*
   * Initialize an array containing the squares from 0 to 15, then build a
   * linked list from that array, and call list_reverse() to reverse the list.
   */
  for (i = 0; i < n; i++) {
    array[i] = i * i;
  }
  list = list_from_array(array, n);
  list = list_reverse(list);

  /*
   * Make sure the reversed list is not NULL.  If you see a test failure from
   * the call to TEST_CHECK_() below, it means your list_reverse() function
   * returned NULL when it shouldn't have.
   */
  TEST_CHECK_(list != NULL, "reversed list is not NULL");

  /*
   * Loop through the list and the array, starting at the front of the list
   * and at the back of the array, and test to make sure corresponding elements
   * are equal to each other.  If some corresponding two elements are not
   * equal, a test failure will be reported.  Specifically, if you see a test
   * failure stemming from the call below to TEST_CHECK_(), it means the list
   * was not correctly reversed, so the i'th element in the reversed list is
   * not equal to the (n - 1 - i)'th element in the original list.
   */
  curr = list;
  i = 0;
  while (curr != NULL && i < n) {
    int j = n - i - 1;
    TEST_CHECK_(curr->value == array[j],
      "list[%d] equal to array[%d] (%d == %d)", i, j, curr->value, array[j]);
    curr = curr->next;
    i++;
  }

  /*
   * Make sure the loop above finished examining all of the elements in both
   * the reversed list and the array.  If you see a test failure coming from
   * the call below to TEST_CHECK(), it means that the reversed list has a
   * different number of elements than the original list.
   */
  if (!TEST_CHECK(curr == NULL && i == n)) {
    TEST_MSG("List unexpectedly ended before the array (or vice versa).");
  }

  list_free(list);
  free(array);
}


/*
 * This function specifies a unit test for list_reverse().  It specifically
 * tests reversing a list containing only one element.  It performs three
 * specific checks:
 *
 *   * It tests to make sure the reversed list is not NULL.
 *   * It tests to make sure the values stored in the first link in the
 *     reversed list is the same as the only value in the original list.
 *   * It tests to make sure the reversed list doesn't have any additional
 *     elements beyond the first.
 */
void test_singleton_list_reverse() {
  int v = 16;
  struct link* list;

  /*
   * Initialize a list with a single element (using a pointer trick), and then
   * reverse the list.
   */
  list = list_from_array(&v, 1);
  list = list_reverse(list);

  /*
   * Make sure the reversed list is not NULL.  If you see a test failure from
   * the call to TEST_CHECK_() below, it means your list_reverse() function
   * returned NULL when it shouldn't have.
   */
  TEST_CHECK_(list != NULL, "reversed list is not NULL");

  /*
   * Make sure the value stored in the reversed list is equal to the one from
   * the original list.  If you see a test failure coming from the call to
   * TEST_CHECK_() below, it means the reversed list contains a different
   * value than the original singleton list.
   */
  TEST_CHECK_(list->value == v, "list contains the expected value (%d == %d)",
    list->value, v);

  /*
   * Make sure the reversed list contains only one element, i.e. that
   * list->next is NULL.  If you see a test failure coming from the call to
   * TEST_CHECK_() below, it means there are potentially additional elements
   * in your reversed list, even though it was created from a list containing
   * just a single element.
   */
  TEST_CHECK_(list->next == NULL,
    "reversed list has one element (list->next is NULL)");

  list_free(list);
}


/*
 * This function specifies a unit test for list_reverse().  It specifically
 * tests reversing a NULL list.  It performs one specific check to make sure
 * the reversed list also NULL.
 */
void test_null_list_reverse() {
  struct link* list;

  /*
   * Try to reverse a NULL list.
   */
  list = list_reverse(NULL);

  /*
   * Make sure the reversed list is NULL.  If you see a test failure from
   * the call to TEST_CHECK_() below, it means your list_reverse() function
   * returned a non-NULL value when it shouldn't have.
   */
  TEST_CHECK_(list == NULL, "reversed list is NULL");
}


/****************************************************************************
 **
 ** Queue-from-stacks tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for the queue-from-stacks.  It
 * specifically tests the creation of a queue-from-stacks.  It makes two
 * specific checks:
 *
 *   * It tests to make sure queue_from_stacks_create() returns a non-NULL
 *     value.
 *   * It tests to make sure queue_from_stacks_isempty() returns "true" for
 *     a queue-from-stacks immediately after its creation.
 */
void test_queue_from_stacks_create() {
  struct queue_from_stacks* qfs;

  /*
   * Create the queue-from-stacks.
   */
  qfs = queue_from_stacks_create();

  /*
   * Make sure the queue-from-stacks is not NULL.  If you see a test failure
   * coming from the call to TEST_CHECK_() below, it means your
   * queue_from_stacks_create() function returned NULL when it shouldn't have.
   */
  TEST_CHECK_(qfs != NULL, "qfs is not NULL");

  /*
   * Make sure the queue-from-stacks that was just created is empty.  If you
   * see a test failure coming from the call to TEST_CHECK_() below, it means
   * your queue_from_stacks_create() function created a non-empty queue.
   */
  TEST_CHECK_(queue_from_stacks_isempty(qfs), "qfs is empty");

  queue_from_stacks_free(qfs);
}


/*
 * This function specifies a unit test for the queue-from-stacks.  It
 * specifically tests whether enqueueing a value, checking the front value,
 * and dequeueing work correctly.  It enqueues a single value into a new
 * queue-from-stacks and then performs four specific checks:
 *
 *   * It tests to make sure queue_from_stacks_isempty() returns "false""
 *     after the value was enqueued.
 *   * It tests to make sure queue_from_stacks_front() returns the same value
 *     that was enqueued.
 *   * It tests to make sure queue_from_stacks_dequeue() returns the same
 *     value that was enqueued.
 *   * It tests to make sure queue_from_stacks_isempty() returns "true""
 *     after the value was dequeued.
 */
void test_queue_from_stacks_enqueue_single() {
  struct queue_from_stacks* qfs = queue_from_stacks_create();
  int dequeued, front, v = 32;

  /*
   * Enqueue a single value into the queue-from-stacks.
   */
  queue_from_stacks_enqueue(qfs, v);

  /*
   * Make sure the queue-from-stacks is not empty after enqueuing a value.  If
   * you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your queue-from-stacks was empty even after enqueueing a value.
   */
  TEST_CHECK_(!queue_from_stacks_isempty(qfs), "qfs is not empty");

  /*
   * Make sure the front value in the queue-from-stacks is equal to the value
   * that was just enqueued.  If you see a test failure coming from the call
   * to TEST_CHECK_() below, it means your queue-from-stacks didn't contain
   * the proper value at the front after enqueueing a single value.
   */
  front = queue_from_stacks_front(qfs);
  TEST_CHECK_(front == v, "qfs front value is correct (%d == %d)", front, v);

  /*
   * Dequeue a value from the queue-from-stacks and make sure that value is
   * equal to the value that was just enqueued.  If you see a test failure
   * coming from the call to TEST_CHECK_() below, it means your
   * queue-from-stacks didn't return the proper value when dequeuing after a
   * single value was enqueued.
   */
  dequeued = queue_from_stacks_dequeue(qfs);
  TEST_CHECK_(dequeued == v, "qfs dequeued value is correct (%d == %d)",
    dequeued, v);

  /*
   * Make sure the queue-from-stacks is empty after dequeuing a value.  If
   * you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your queue-from-stacks was not empty even after dequeueing what
   * should have been the only value in the queue.
   */
  TEST_CHECK_(queue_from_stacks_isempty(qfs), "qfs is empty after dequeuing");

  queue_from_stacks_free(qfs);
}


/*
 * This function specifies a unit test for the queue-from-stacks.  It
 * specifically tests whether the queue-from-stacks correctly supports
 * multiple enqueues, followed by several dequeues, several more enqueues,
 * and then several more dequeues.  It performs several specific checks,
 * each of which involves making sure the proper value is contained at the
 * front of the queue-from-stacks and is dequeued from the queue-from-stacks,
 * where the "proper" value for each check is determined based on a regular
 * queue implementation that is known to work.
 */
void test_queue_from_stacks_enqueue_multiple() {
  struct queue_from_stacks* qfs = queue_from_stacks_create();
  struct queue* q = queue_create();
  int dequeued, front, v, i, n = 16, m = 8;

  /*
   * Enqueue multiple values into the queue-from-stacks.  Enqueue the same
   * values into a regular queue, so we can compare the ordering of the queue
   * and the queue-from-stacks.
   */
  for (i = 0; i < n; i++) {
    v = 2 * i + 1;
    queue_from_stacks_enqueue(qfs, v);
    queue_enqueue(q, v);
  }

  /*
   * For m iterations, make sure the front value and the dequeued value from
   * the queue-from-stacks matches the correct value from the regular queue.
   */
  for (i = 0; i < m; i++) {
    v = queue_dequeue(q);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your queue-from-stacks didn't contain the proper value at the
     * front (where the proper value, v, comes from the normal queue, q).
     */
    front = queue_from_stacks_front(qfs);
    TEST_CHECK_(front == v, "qfs front value is correct (%d == %d)", front, v);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your queue-from-stacks didn't dequeue the proper value (where
     * the proper value, v, comes from the normal queue, q).
     */
    dequeued = queue_from_stacks_dequeue(qfs);
    TEST_CHECK_(dequeued == v, "qfs dequeued value is correct (%d == %d)",
      dequeued, v);
  }

  /*
   * Enqueue multiple additional values into the queue-from-stacks and the
   * regular queue.
   */
  for (i = n; i < n + m; i++) {
    v = 2 * i + 1;
    queue_from_stacks_enqueue(qfs, v);
    queue_enqueue(q, v);
  }

  /*
   * For the remaining values in the queue, make sure the front value and the
   * dequeued value from the queue-from-stacks matches the correct value from
   * the regular queue.
   */
  while (!queue_isempty(q)) {
    v = queue_dequeue(q);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your queue-from-stacks didn't contain the proper value at the
     * front (where the proper value, v, comes from the normal queue, q).
     */
    front = queue_from_stacks_front(qfs);
    TEST_CHECK_(front == v, "qfs front value is correct (%d == %d)", front, v);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your queue-from-stacks didn't dequeue the proper value (where
     * the proper value, v, comes from the normal queue, q).
     */
    dequeued = queue_from_stacks_dequeue(qfs);
    TEST_CHECK_(dequeued == v, "qfs dequeued value is correct (%d == %d)",
      dequeued, v);
  }

  /*
   * Make sure the queue-from-stacks is empty at the same time as the regular
   * queue.  If you see a test failure coming from the call to TEST_CHECK_()
   * below, it means your queue-from-stacks was not empty even after dequeueing
   * what should have been the last value in the queue.
   */
  TEST_CHECK_(queue_from_stacks_isempty(qfs), "qfs is empty after dequeuing");

  queue_from_stacks_free(qfs);
  queue_free(q);
}


/****************************************************************************
 **
 ** Stack-from-queues tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for the stack-from-queues.  It
 * specifically tests the creation of a stack-from-queues.  It makes two
 * specific checks:
 *
 *   * It tests to make sure stack_from_queues_create() returns a non-NULL
 *     value.
 *   * It tests to make sure queue_from_stacks_isempty() returns "true" for
 *     a stack-from-queues immediately after its creation.
 */
void test_stack_from_queues_create() {
  struct stack_from_queues* sfq;

  /*
   * Create the stack-from-queues.
   */
  sfq = stack_from_queues_create();

  /*
   * Make sure the stack-from-queues is not NULL.  If you see a test failure
   * coming from the call to TEST_CHECK_() below, it means your
   * stack_from_queues_create() function returned NULL when it shouldn't have.
   */
  TEST_CHECK_(sfq != NULL, "sfq is not NULL");

  /*
   * Make sure the stack-from-queues that was just created is empty.  If you
   * see a test failure coming from the call to TEST_CHECK_() below, it means
   * your stack_from_queues_create() function created a non-empty stack.
   */
  TEST_CHECK_(stack_from_queues_isempty(sfq), "sfq is empty");

  stack_from_queues_free(sfq);
}


/*
 * This function specifies a unit test for the stack-from-queues.  It
 * specifically tests whether pushing a value, checking the top value,
 * and popping work correctly.  It pushes a single value into a new
 * stack-from-queues and then performs four specific checks:
 *
 *   * It tests to make sure stack_from_queues_isempty() returns "false""
 *     after the value was pushed.
 *   * It tests to make sure stack_from_queues_top() returns the same value
 *     that was pushed.
 *   * It tests to make sure stack_from_queues_pop() returns the same
 *     value that was pushed.
 *   * It tests to make sure stack_from_queues_isempty() returns "true""
 *     after the value was popped.
 */
void test_stack_from_queues_push_single() {
  struct stack_from_queues* sfq = stack_from_queues_create();
  int popped, top, v = 32;

  /*
   * Enqueue a single value into the stack-from-queues.
   */
  stack_from_queues_push(sfq, v);

  /*
   * Make sure the stack-from-queues is not empty after pushing a value.  If
   * you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your stack-from-queues was empty even after pushing a value.
   */
  TEST_CHECK_(!stack_from_queues_isempty(sfq), "sfq is not empty");

  /*
   * Make sure the top value in the stack-from-queues is equal to the value
   * that was just pushed.  If you see a test failure coming from the call
   * to TEST_CHECK_() below, it means your stack-from-queues didn't contain
   * the proper value at the top after pushing a single value.
   */
  top = stack_from_queues_top(sfq);
  TEST_CHECK_(top == v, "sfq top value is correct (%d == %d)", top, v);

  /*
   * Dequeue a value from the stack-from-queues and make sure that value is
   * equal to the value that was just pushed.  If you see a test failure
   * coming from the call to TEST_CHECK_() below, it means your
   * stack-from-queues didn't return the proper value when popping after a
   * single value was pushed.
   */
  popped = stack_from_queues_pop(sfq);
  TEST_CHECK_(popped == v, "sfq popped value is correct (%d == %d)",
    popped, v);

  /*
   * Make sure the stack-from-queues is empty after popping a value.  If
   * you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your stack-from-queues was not empty even after popping what
   * should have been the only value in the queue.
   */
  TEST_CHECK_(stack_from_queues_isempty(sfq), "sfq is empty after popping");

  stack_from_queues_free(sfq);
}


/*
 * This function specifies a unit test for the stack-from-queues.  It
 * specifically tests whether the stack-from-queues correctly supports
 * multiple pushes, followed by several pops, several more pushes,
 * and then several more pops.  It performs several specific checks,
 * each of which involves making sure the proper value is contained at the
 * top of the stack-from-queues and is popped from the stack-from-queues,
 * where the "proper" value for each check is determined based on a regular
 * stack implementation that is known to work.
 */
void test_stack_from_queues_push_multiple() {
  struct stack_from_queues* sfq = stack_from_queues_create();
  struct stack* s = stack_create();
  int popped, top, v, i, n = 16, m = 8;

  /*
   * Push multiple values into the stack-from-queues.  Push the same
   * values into a regular stack, so we can compare the ordering of the stack
   * and the stack-from-queues.
   */
  for (i = 0; i < n; i++) {
    v = 2 * i;
    stack_from_queues_push(sfq, v);
    stack_push(s, v);
  }

  /*
   * For m iterations, make sure the top value and the popped value from
   * the stack-from-queues matches the correct value from the regular stack.
   */
  for (i = 0; i < m; i++) {
    v = stack_pop(s);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your stack-from-queues didn't contain the proper value at the
     * top (where the proper value, v, comes from the normal stack, s).
     */
    top = stack_from_queues_top(sfq);
    TEST_CHECK_(top == v, "sfq top value is correct (%d == %d)", top, v);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your stack-from-queues didn't dequeue the proper value (where
     * the proper value, v, comes from the normal stack, s).
     */
    popped = stack_from_queues_pop(sfq);
    TEST_CHECK_(popped == v, "sfq popped value is correct (%d == %d)",
      popped, v);
  }

  /*
   * Enqueue multiple additional values into the stack-from-queues and the
   * regular stack.
   */
  for (i = n; i < n + m; i++) {
    v = 2 * i;
    stack_from_queues_push(sfq, v);
    stack_push(s, v);
  }

  /*
   * For the remaining values in the queue, make sure the top value and the
   * popped value from the stack-from-queues matches the correct value from
   * the regular stack.
   */
  while (!stack_isempty(s)) {
    v = stack_pop(s);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your stack-from-queues didn't contain the proper value at the
     * top (where the proper value, v, comes from the normal stack, s).
     */
    top = stack_from_queues_top(sfq);
    TEST_CHECK_(top == v, "sfq top value is correct (%d == %d)", top, v);

    /*
     * If you see a test failure coming from the call to TEST_CHECK_() below,
     * it means your stack-from-queues didn't dequeue the proper value (where
     * the proper value, v, comes from the normal stack, s).
     */
    popped = stack_from_queues_pop(sfq);
    TEST_CHECK_(popped == v, "sfq popped value is correct (%d == %d)",
      popped, v);
  }

  /*
   * Make sure the stack-from-queues is empty at the same time as the regular
   * stack.  If you see a test failure coming from the call to TEST_CHECK_()
   * below, it means your stack-from-queues was not empty even after popping
   * what should have been the last value in the stack.
   */
  TEST_CHECK_(stack_from_queues_isempty(sfq), "sfq is empty after popping");

  stack_from_queues_free(sfq);
  stack_free(s);
}


TEST_LIST = {
  /* list_reverse() tests */
  { "regular_list_reverse", test_regular_list_reverse },
  { "singleton_list_reverse", test_singleton_list_reverse },
  { "null_list_reverse", test_null_list_reverse },
  /* queue-from-stacks tests */
  { "queue_from_stacks_create", test_queue_from_stacks_create },
  { "queue_from_stacks_enqueue_single", test_queue_from_stacks_enqueue_single },
  { "queue_from_stacks_enqueue_multiple", test_queue_from_stacks_enqueue_multiple },
  /* stack-from-queues tests */
  { "stack_from_queues_create", test_stack_from_queues_create },
  { "stack_from_queues_push_single", test_stack_from_queues_push_single },
  { "stack_from_queues_push_multiple", test_stack_from_queues_push_multiple },
  { NULL, NULL }
};



/*
 * A function to convert an array of integers into a linked list.
 */
struct link* list_from_array(int* array, int n) {
  struct link* link, * head = NULL, * tail = NULL;

  for (int i = 0; i < n; i++) {
    /*
     * Allocate a new link and store the current value there.
     */
    link = malloc(sizeof(struct link));
    link->value = array[i];
    link->next = NULL;

    /*
     * If the list was empty, put the new link at the head.
     */
    if (!head) {
      head = link;
    }

    /*
     * Put the new link at the tail of the list.
     */
    if (tail) {
      tail->next = link;
    }
    tail = link;
  }

  return head;
}


/*
 * A function to free all of the memory allocated to a list, given its head.
 */
void list_free(struct link* head) {
  struct link* next, * curr = head;
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}
