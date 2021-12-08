/*
 * This file uses the Acutest unit testing framework to test the functionality
 * you implemented in this assignment.  Each function you wrote will have one
 * or more unit tests associated with it.  You can find more about the
 * Acutest framework here: https://github.com/mity/acutest.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acutest.h"

#include "pq.h"

/*
 * This is a comparison function to be used with qsort() to sort an array of
 * integers into ascending order.
 */
int ascending_int_cmp(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

/****************************************************************************
 **
 ** Tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for the priority queue.  It specifically
 * tests the creation of a PQ, making sure pq_create() returns a non-NULL and
 * empty PQ.
 */
void test_pq_create() {
  struct pq* pq;

  /*
   * Create the priority queue.
   */
  pq = pq_create();

  /*
   * Make sure the PQ is not NULL.  If you see a test failure coming from the
   * call to TEST_CHECK_() below, it means your pq_create() function returned
   * NULL when it shouldn't have.
   */
  TEST_CHECK_(pq != NULL, "pq is not NULL");

  /*
   * Make sure the PQ that was just created is empty.  If you see a test
   * failure coming from the call to TEST_CHECK_() below, it means your
   * pq_create() function created a non-empty PQ.
   */
  TEST_CHECK_(pq_isempty(pq), "pq is empty");

  pq_free(pq);
}


/*
 * This function specifies a unit test for the priority queue.  It specifically
 * tests to make sure a single value can be successfully inserted, queried,
 * and removed from a new PQ.
 */
void test_pq_insert_single() {
  struct pq* pq = pq_create();
  int* first, * removed;
  int p, v = 32;

  /*
   * Insert a single pointer to an integer value into the priority queue with
   * the same priority as the value.
   */
  pq_insert(pq, &v, v);

  /*
   * Make sure the PQ is not empty after inserting a value.  If you see a test
   * failure coming from the call to TEST_CHECK_() below, it means your PQ
   * was empty even after inserting a value.
   */
  TEST_CHECK_(!pq_isempty(pq), "pq is not empty");

  /*
   * Make sure the priority value tied to the first/only element in the PQ is
   * equal to the priority with which it was inserted.  If you see a test
   * failure coming from the call to TEST_CHECK_() below, it means your PQ
   * didn't return the correct priority for the first element after inserting
   * only a single element.
   */
  p = pq_first_priority(pq);
  TEST_CHECK_(p == v, "pq first priority is correct (%d == %d)", p, v);

  /*
   * Make sure the first element in the PQ is equal to the only inserted value.
   * If you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your PQ didn't return the correct value for the first element after
   * inserting only a single element.
   */
  first = pq_first(pq);
  TEST_CHECK_(*first == v, "pq first value is correct (%d == %d)", *first, v);

  /*
   * Make sure the first element removed in the PQ is equal to the only
   * inserted value.  If you see a test failure coming from the call to
   * TEST_CHECK_() below, it means your PQ didn't return the correct value
   * when removing the first element after inserting only a single element.
   */
  removed = pq_remove_first(pq);
  TEST_CHECK_(*removed == v, "pq removed value is correct (%d == %d)",
    *removed, v);

  /*
   * Make sure the PQ is empty after removing the only value.  If you see a
   * test failure coming from the call to TEST_CHECK_() below, it means your
   * PQ was not empty even after removing what should have been the only value.
   */
  TEST_CHECK_(pq_isempty(pq), "pq is empty");

  pq_free(pq);
}


/*
 * This function specifies a unit test for the priority queue.  It specifically
 * tests to make sure a single value can be successfully inserted, queried,
 * and removed from a new PQ.
 */
void test_pq_insert_multiple() {
  struct pq* pq = pq_create();
  int* first, * removed;
  int i, k, p;
  const int n = 16, m = 16;
  int vals[n + m], ordered[n + m];

  /*
   * Seed the random number generator with a constant value, so it produces the
   * same sequence of pseudo-random values every time this program is run.
   */
  srand(0);

  /*
   * Fill an array with pseudo-random integer values and insert pointers to
   * those values into the priority queue with the same priority as the value.
   */
  for (i = 0; i < n; i++) {
    vals[i] = rand() % 64;
    pq_insert(pq, &vals[i], vals[i]);
  }

  /*
   * Make a copy of the random value array and sort it by ascending value.  We
   * make a copy here so we can maintain the original array in the same order,
   * thereby ensuring that pointer values stored in the priority queue always
   * point to the same integer values.
   */
  memcpy(ordered, vals, n * sizeof(int));
  qsort(ordered, n, sizeof(int), ascending_int_cmp);

  /*
   * Examine and remove half of the values currently in the PQ.
   */
  k = 0;
  while (k < n / 2) {
    /*
     * Make sure the priority value tied to the first element in the PQ is
     * the expected value.  If you see a test failure coming from the call to
     * TEST_CHECK_() below, it means that the priority value returned by
     * pq_first_priority() wasn't the expected value (i.e. the k'th value in
     * the ordered array).
     */
    p = pq_first_priority(pq);
    TEST_CHECK_(p == ordered[k],
      "pq %d'th first priority is correct (%d == %d)", k, p, ordered[k]);

    /*
     * Make sure the value of the first element in the PQ is the expected
     * value.  If you see a test failure coming from the call to TEST_CHECK_()
     * below, it means that the value returned by pq_first() wasn't the
     * expected value (i.e. the k'th value in the ordered array).
     */
    first = pq_first(pq);
    TEST_CHECK_(*first == ordered[k],
      "pq %d'th first value is correct (%d == %d)", k, *first, ordered[k]);

    /*
     * Make sure the value removed from the PQ is the expected value.  If you
     * see a test failure coming from the call to TEST_CHECK_() below, it means
     * that the value returned by pq_remove_first() wasn't the expected value
     * (i.e. the k'th value in the ordered array).
     */
    removed = pq_remove_first(pq);
    TEST_CHECK_(*removed == ordered[k],
      "pq %d'th removed value is correct (%d == %d)", k, *removed, ordered[k]);
    k++;
  }

  /*
   * Add a second set of pseudo-random integer values to the end of the array,
   * and add pointers to those values into the priority queue with the same
   * priority as the value.
   */
  for (i = n; i < n + m; i++) {
    vals[i] = rand() % 64;
    pq_insert(pq, &vals[i], vals[i]);
  }

  /*
   * Copy the second array of random values to the end of the ordered array and
   * re-sort all of the the ordered array except the k values that were already
   * examined above (since they were already removed from the PQ, and we won't
   * see them again).  Again, we make a copy here so we can maintain the
   * original array in the same order, thereby ensuring that pointer values
   * stored in the priority queue always point to the same integer values.
   */
  memcpy(ordered + n, vals + n, m * sizeof(int));
  qsort(ordered + k, n - k + m, sizeof(int), ascending_int_cmp);

  /*
   * Examine and remove the remaining values in the PQ.
   */
  while (k < n + m) {
    /*
     * Make sure the priority value tied to the first element in the PQ is
     * the expected value.  If you see a test failure coming from the call to
     * TEST_CHECK_() below, it means that the priority value returned by
     * pq_first_priority() wasn't the expected value (i.e. the k'th value in
     * the ordered array).
     */
    p = pq_first_priority(pq);
    TEST_CHECK_(p == ordered[k],
      "pq %d'th first priority is correct (%d == %d)", k, p, ordered[k]);

    /*
     * Make sure the value of the first element in the PQ is the expected
     * value.  If you see a test failure coming from the call to TEST_CHECK_()
     * below, it means that the value returned by pq_first() wasn't the
     * expected value (i.e. the k'th value in the ordered array).
     */
    first = pq_first(pq);
    TEST_CHECK_(*first == ordered[k],
      "pq %d'th first value is correct (%d == %d)", k, *first, ordered[k]);

    /*
     * Make sure the value removed from the PQ is the expected value.  If you
     * see a test failure coming from the call to TEST_CHECK_() below, it means
     * that the value returned by pq_remove_first() wasn't the expected value
     * (i.e. the k'th value in the ordered array).
     */
    removed = pq_remove_first(pq);
    TEST_CHECK_(*removed == ordered[k],
      "pq %d'th removed value is correct (%d == %d)", k, *removed, ordered[k]);
    k++;
  }

  /*
   * Make sure the PQ is empty when we expect it to be.  If you see a test
   * failure coming from the call to TEST_CHECK_() below, it means your PQ was
   * not empty after removing what should have been the last value.
   */
  TEST_CHECK_(pq_isempty(pq), "pq is empty");

  pq_free(pq);
}


/****************************************************************************
 **
 ** Test listing
 **
 ****************************************************************************/

TEST_LIST = {
  { "pq_create", test_pq_create },
  { "pq_insert_single", test_pq_insert_single },
  { "pq_insert_multiple", test_pq_insert_multiple },
  { NULL, NULL }
};
