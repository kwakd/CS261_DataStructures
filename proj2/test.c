/*
 * This file contains executable code for testing your work in this assignment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "link.h"
#include "stack.h"
#include "queue.h"
#include "list_reverse.h"
#include "queue_from_stacks.h"
#include "stack_from_queues.h"

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
 * A simple function to print the contents of a linked list, given its head.
 */
void list_print(struct link* head) {
  struct link* curr = head;

  if (!curr) {
    printf(" (null)");
  }

  while (curr) {
    printf(" %4d", curr->value);
    curr = curr->next;
  }
  printf("\n");
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


int main(int argc, char** argv) {
  int n = 16, m = 8;
  int* array = malloc(n * sizeof(int));
  struct link* list;
  struct queue_from_stacks* qfs;
  struct queue* q;
  struct stack_from_queues* sfq;
  struct stack* s;

  printf("\n===========================\n");
  printf("== Testing list_reverse()\n");
  printf("===========================\n\n");

  for (int i = 0; i < n; i++) {
    array[i] = i * i;
  }

  /*
   * Test list reversal using a list created from array.
   */
  list = list_from_array(array, n);
  printf("== Original list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed list contents:");
  list_print(list);
  printf("\n");

  /*
   * Test list reversal on a list of length 1 (using a pointer trick to create
   * the list).
   */
  list_free(list);
  list = list_from_array(&n, 1);
  printf("== Original length=1 list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed length=1 list contents:");
  list_print(list);
  printf("\n");

  /*
   * Test list reversal on a null list.
   */
  list_free(list);
  list = NULL;
  printf("== Original null list contents:");
  list_print(list);
  list = list_reverse(list);
  printf("== Reversed null list contents:");
  list_print(list);
  printf("\n");

  free(array);

  /*
   * Test queue-from-stacks implementation by enqueueing, checking the front,
   * and dequeueing and comparing against a known-correct regular queue.
   */
  printf("\n=============================================\n");
  printf("== Testing queue-from-stacks implementation\n");
  printf("=============================================\n\n");
  qfs = queue_from_stacks_create();
  q = queue_create();
  for (int i = 0; i < n; i++) {
    int val = 2 * i + 1;
    queue_from_stacks_enqueue(qfs, val);
    queue_enqueue(q, val);

  }

  printf("== Dequeueing some from queue-from-stacks: front / dequeued (expected)\n");
  for (int i = 0; i < m; i++) {
    int expected = queue_dequeue(q);
	//printf("before front\n");
    int front = queue_from_stacks_front(qfs);
	//printf("before deque\n");
    int dequeued = queue_from_stacks_dequeue(qfs);
	//printf("before print\n");
    printf("  - %4d / %4d (%4d)\n", front, dequeued, expected);
  }

  printf("== Enqueueing more into queue-from-stacks.\n");
  for (int i = n; i < n + m; i++) {
    int val = 2 * i + 1;
    queue_from_stacks_enqueue(qfs, val);
    queue_enqueue(q, val);
  }

  printf("== Dequeueing rest from queue-from-stacks: front / dequeued (expected)\n");
  while (!queue_isempty(q)) {
    int expected = queue_dequeue(q);
    int front = queue_from_stacks_front(qfs);
    int dequeued = queue_from_stacks_dequeue(qfs);
    printf("  - %4d / %4d (%4d)\n", front, dequeued, expected);
  }

  printf("== Is queue-from-stacks empty (expect 1)? %d\n",
    queue_from_stacks_isempty(qfs));

  queue_from_stacks_free(qfs);
  queue_free(q);

  /*
   * Test stack-from-queues implementation by pushing, checking the top, and
   * popping and comparing against a known-correct regular stack.
   */
  printf("\n=============================================\n");
  printf("== Testing stack-from-queues implementation\n");
  printf("=============================================\n\n");
  sfq = stack_from_queues_create();
  s = stack_create();
  printf("== Pushing onto stack-from-queues.\n");
  for (int i = 0; i < n; i++) {
    int val = 2 * i;
	//printf("before stack_from_queues\n");
    stack_from_queues_push(sfq, val);
	//printf("before stack push.\n");
    stack_push(s, val);
	//printf("after stack push.\n");

  }

  printf("== Popping some from stack-from-queues: top / popped (expected)\n");
  for (int i = 0; i < m; i++) {
	 //printf("before stack pop.\n");
    int expected = stack_pop(s);
	//printf("before stack top.\n");
    int top = stack_from_queues_top(sfq);
	//printf("before stackpop.\n");
    int popped = stack_from_queues_pop(sfq);
    printf("  - %4d / %4d (%4d)\n", top, popped, expected);
  }

  printf("== Pushing more onto stack-from-queues.\n");
  for (int i = n; i < n + m; i++) {
    int val = 2 * i;
    stack_from_queues_push(sfq, val);
    stack_push(s, val);
  }

  printf("== Popping rest from stack-from-queues: top / popped (expected)\n");
  while (!stack_isempty(s)) {
    int expected = stack_pop(s);
    int top = stack_from_queues_top(sfq);
    int popped = stack_from_queues_pop(sfq);
    printf("  - %4d / %4d (%4d)\n", top, popped, expected);
  }

  printf("== Is stack-from-queues empty (expect 1)? %d\n",
    stack_from_queues_isempty(sfq));

  stack_from_queues_free(sfq);
  stack_free(s);
}
