/*
 * This file uses the Acutest unit testing framework to test the functionality
 * you implemented in this assignment.  Each function you wrote will have one
 * or more unit tests associated with it.  You can find more about the
 * Acutest framework here: https://github.com/mity/acutest.
 */

#include <stdio.h>
#include <stdlib.h>

#include "acutest.h"

#include "bst.h"

/*
 * Below is defined testing data used in several of the unit tests in this
 * file.  There are specifically 5 BSTs defined with various characteristics.
 * Each tree is defined as an array of values in the order in which those
 * values are inserted into the tree.  The values are specifically in level
 * order, so that, starting with the root, each level of the tree is completely
 * listed from left to right before the values of the following level are
 * listed.  The sizes, heights, etc. for these trees are defined in subsequent
 * arrays.
 *
 * The first tree is visualized in a comment in test.c.  It is left as an
 * exercise for the programmer to visualize the remaining trees.
 */
#define NUM_TEST_TREES 9
#define MAX_TEST_TREE_SIZE 16
const int TEST_TREE_VALUES[NUM_TEST_TREES][MAX_TEST_TREE_SIZE] =  {
  { 64, 32, 96, 16, 48, 80, 112, 8, 24, 56, 88, 104, 120 },
  { 16, 8, 24, 32, 28 },
  { 13, 7, 20, 4, 14, 27, 1, 16, 33, 15, 18, 19 },
  { 10, 8, 11, 9 },
  { 100, 90, 80, 70, 60, 50, 40, 30, 20, 10 },
  { 32, 16 },
  { 32, 64 },
  { 32 },
  {}
};

const int TEST_TREE_SIZES[NUM_TEST_TREES] = { 13, 5, 12, 4, 10, 2, 2, 1, 0 };

const int TEST_TREE_HEIGHTS[NUM_TEST_TREES] = { 3, 3, 5, 2, 9, 1, 1, 0, -1 };

const int TEST_TREE_PATH_SUMS[NUM_TEST_TREES][MAX_TEST_TREE_SIZE] = {
  { 120, 136, 200, 328, 376, 392 },
  { 24, 100 },
  { 25, 78, 100, 93 },
  { 27, 21 },
  { 550 },
  { 48 },
  { 96 },
  { 32 },
  {}
};
const int TEST_TREE_NUM_PATH_SUMS[NUM_TEST_TREES] = { 6, 2, 4, 2, 1, 1, 1, 1, 0 };
#define MAX_TEST_TREE_PATH_SUM 550

/*
 * These are prototypes of auxilliary functions used in the tests.  Their
 * definitions are at the bottom of this file.
 */
struct bst* bst_from_array(const int* array, int n);
int contains(int val, const int* array, int n);
int ascending_int_cmp (const void * a, const void * b);


/****************************************************************************
 **
 ** bst_size() tests
 **
 ****************************************************************************/

/*
 * This function specifies a unit test for bst_size().  It specifically picks
 * a reasonably-large random size, creates a BST with that many values, and
 * then checks to make sure bst_size() returns the correct size.
 */
void test_bst_random_size() {
  int i, n, size;
  struct bst* bst = bst_create();

  /*
   * Pick a random size between 64 and 128 and insert that many values into the
   * BST.
   */
  n = rand() % 64 + 64;
  for (i = 0; i < n; i++) {
    bst_insert(rand(), bst);
  }

  /*
   * Make sure bst_size() returns the expected value, n.  If you see a test
   * failure from the call to TEST_CHECK_ below, it means your bst_size()
   * function didn't return the correct value.
   */
  size = bst_size(bst);
  TEST_CHECK_(size == n, "bst_size() returns the correct size (%d == %d)",
    size, n);

  bst_free(bst);
}


/*
 * This function specifies a unit test for bst_size().  It specifically creates
 * several relatively small BSTs of known size and ensures that bst_size()
 * returns the correct size for each one.
 */
void test_bst_known_sizes() {
  int i, n, size;
  struct bst* bst;

  /*
   * Iterate through all of the testing trees.
   */
  for (i = 0; i < NUM_TEST_TREES; i++) {
    /*
     * Create a new BST and fill it with the values for the i'th testing tree.
     */
    n = TEST_TREE_SIZES[i];
    bst = bst_from_array(TEST_TREE_VALUES[i], n);

    /*
     * Make sure bst_size() returns the expected value, n.  If you see a test
     * failure from the call to TEST_CHECK_ below, it means your bst_size()
     * function didn't return the correct value.
     */
    size = bst_size(bst);
    TEST_CHECK_(size == n,
      "bst_size() returns the correct size for tree %d (%d == %d)", i, size, n);

    bst_free(bst);
  }
}


/****************************************************************************
 **
 ** bst_height() tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for bst_height().  It specifically
 * creates several relatively small BSTs of known height and ensures that
 * bst_height() returns the correct height for each one.
 */
void test_bst_heights() {
  int i, h, height;
  struct bst* bst;

  /*
   * Iterate through all of the testing trees.
   */
  for (i = 0; i < NUM_TEST_TREES; i++) {
    /*
     * Create a new BST and fill it with the values for the i'th testing tree.
     */
    bst = bst_from_array(TEST_TREE_VALUES[i], TEST_TREE_SIZES[i]);

    /*
     * Make sure bst_height() returns the expected value, h.  If you see a test
     * failure from the call to TEST_CHECK_ below, it means your bst_height()
     * function didn't return the correct value.
     */
    h = TEST_TREE_HEIGHTS[i];
    height = bst_height(bst);
    TEST_CHECK_(height == h,
      "bst_height() returns the correct height for tree %d (%d == %d)", i,
      height, h);

    bst_free(bst);
  }
}


/****************************************************************************
 **
 ** bst_path_sum() tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for bst_path_sum().  It specifically
 * creates several relatively small BSTs with known path sums and ensures that
 * bst_path_sum() correctly identifies all good path sums.
 */
void test_bst_good_path_sums() {
  int i, j, sum;
  struct bst* bst;

  /*
   * Iterate through all of the testing trees.
   */
  for (i = 0; i < NUM_TEST_TREES; i++) {
    /*
     * Create a new BST and fill it with the values for the i'th testing tree.
     */
    bst = bst_from_array(TEST_TREE_VALUES[i], TEST_TREE_SIZES[i]);

    /*
     * Make sure bst_path_sum() correctly finds each good path sum in the tree.
     * If you see a test failure from the call to TEST_CHECK_ below, it means
     * your bst_path_sum() function returned "false" (0) for a given path sum
     * when it should have returned "true" (1).
     */
    for (j = 0; j < TEST_TREE_NUM_PATH_SUMS[i]; j++) {
      sum = TEST_TREE_PATH_SUMS[i][j];
      TEST_CHECK_(bst_path_sum(sum, bst),
        "bst_path_sum() correctly finds path sum %d in tree %d", sum, i);
    }
    bst_free(bst);
  }
}


/*
 * This function specifies a unit test for bst_path_sum().  It specifically
 * creates several relatively small BSTs with known path sums and ensures that
 * bst_path_sum() does not identify any bad path sums (i.e. ones that don't
 * exist in the tree).
 */
void test_bst_bad_path_sums() {
  int i, j, sum, finds_bad_sums, last_bad_sum;
  struct bst* bst;

  /*
   * Iterate through all of the testing trees.
   */
  for (i = 0; i < NUM_TEST_TREES; i++) {
    /*
     * Create a new BST and fill it with the values for the i'th testing tree.
     */
    bst = bst_from_array(TEST_TREE_VALUES[i], TEST_TREE_SIZES[i]);

    /*
     * Check to see whether bst_path_sum() finds any bad path sums by testing
     * all non-path-sum values up to the maximum possible path sum value.  If
     * bst_path_sum() finds any bad values, remember the last one it found.
     */
    finds_bad_sums = 0;
    for (j = 0; j < MAX_TEST_TREE_PATH_SUM; j++) {
      if (!contains(j, TEST_TREE_PATH_SUMS[i], TEST_TREE_NUM_PATH_SUMS[i])) {
        if (bst_path_sum(j, bst)) {
          finds_bad_sums = 1;
          last_bad_sum = j;
        }
      }
    }

    /*
     * Make sure bst_path_sum() didn't find any pad path sums.  If you see a
     * test failure from the line below, it means your bst_path_sum() function
     * found at least one bad path sum (i.e. a path sum that doesn't actually
     * exist in the tree) in the tree.  The last incorrect path sum is reported
     * here, but your function may have found more than one.
     */
    TEST_CHECK_(!finds_bad_sums,
      "bst_path_sum() incorrectly finds some path sum values in tree %d", i);
    TEST_MSG("The last incorrect path sum it found was: %d", last_bad_sum);

    bst_free(bst);
  }
}


/****************************************************************************
 **
 ** bst_iterator tests
 **
 ****************************************************************************/


/*
 * This function specifies a unit test for the bst_iterator.  It specifically
 * tests whether a bst_iterator can be successfully created from a tree
 * containing a non-zero number of elements.
 */
void test_bst_iterator_create() {
  struct bst* bst;
  struct bst_iterator* iter;

  /*
   * Create the iterator from a non-empty tree.
   */
  bst = bst_from_array(TEST_TREE_VALUES[0], TEST_TREE_SIZES[0]);
  iter = bst_iterator_create(bst);

  /*
   * Make sure the iterator is not NULL.  If you see a test failure coming
   * from the call to TEST_CHECK_() below, it means your bst_iterator_create()
   * function returned NULL when it shouldn't have.
   */
  TEST_CHECK_(iter != NULL, "iterator is not NULL");

  /*
   * Make sure the iterator that was just created has a next value.  If you
   * see a test failure coming from the call to TEST_CHECK_() below, it means
   * your bst_iterator_create() function created an iterator that started with
   * no next value, even though the tree over which the iterator was created
   * was not empty.
   */
  TEST_CHECK_(bst_iterator_has_next(iter), "iterator has a next value");

  bst_iterator_free(iter);
  bst_free(bst);
}


/*
 * This function specifies a unit test for the bst_iterator.  It specifically
 * tests whether a bst_iterator can be successfully created from an empty tree.
 */
void test_bst_iterator_create_empty() {
  struct bst* bst;
  struct bst_iterator* iter;

  /*
   * Create the iterator from an empty tree.
   */
  bst = bst_create();
  iter = bst_iterator_create(bst);

  /*
   * Make sure the iterator is not NULL.  If you see a test failure coming
   * from the call to TEST_CHECK_() below, it means your bst_iterator_create()
   * function returned NULL when it shouldn't have.
   */
  TEST_CHECK_(iter != NULL, "iterator is not NULL");

  /*
   * Make sure the iterator that was just created doesn't have a next value.
   * If you see a test failure coming from the call to TEST_CHECK_() below, it
   * means your bst_iterator_create() function created an iterator that started
   * out indicating there was a next value to which to iterate, even though the
   * tree over which the iterator was created was empty.
   */
  TEST_CHECK_(!bst_iterator_has_next(iter), "iterator has no next value");

  bst_iterator_free(iter);
  bst_free(bst);
}


/*
 * This function specifies a unit test for the bst_iterator.  It specifically
 * tests whether a bst_iterator correctly iterates through a non-empty tree.
 */
void test_bst_iterator_iteration() {
  int k, n, curr;
  const int* tree_values;
  int* in_order_values;
  struct bst* bst;
  struct bst_iterator* iter;

  /*
   * Create the iterator from a non-empty tree.
   */
  n = TEST_TREE_SIZES[0];
  tree_values = TEST_TREE_VALUES[0];
  bst = bst_from_array(tree_values, n);
  iter = bst_iterator_create(bst);

  /*
   * Make a sorted copy of the array of values used to build bst.  Since this
   * copy is sorted in ascending order, the ordering of the values in it will
   * match the order of an in-order traversal.
   */
  in_order_values = malloc(n * sizeof(int));
  memcpy(in_order_values, tree_values, n * sizeof(int));
  qsort(in_order_values, n, sizeof(int), ascending_int_cmp);

  /*
   * Iterate completely over the tree using the iterator and compare each
   * iterator value to the expected value, based on the in-order ordering of
   * values from in_order_values.  Make sure values are as expected.  If you
   * see a test failure coming from the call to TEST_CHECK_() in the loop
   * below, it means that your bst_iterator_next() function is returning
   * values in the wrong order.
   */
  k = 0;
  while (bst_iterator_has_next(iter) && k < n) {
    curr = bst_iterator_next(iter);
    TEST_CHECK_(curr == in_order_values[k],
      "%d'th iterator value equals expected value (%d == %d)", k, curr,
      in_order_values[k]);
    k++;
  }

  /*
   * Make sure the iterator iterated completely through the tree.  If you see
   * a failure from the call to TEST_CHECK_() below, it means your iterator
   * indicated that the iteration was complete before it should have been (i.e.
   * bst_iterator_has_next() returned "false" while there were still values
   * in the tree that weren't encountered).
   */
  TEST_CHECK_(k == n, "iterator visited %d elements (actually visited %d)",
    n, k);

  /*
   * Make sure the iterator was finished iterating.  If you see a test failure
   * from the call to TEST_CHECK_() below, it means your iterator indicated
   * that it still has elements to examine even after seeing all of the values
   * expected in the tree (i.e. bst_iterator_has_next() still returns "true"
   * after visiting all elements in the tree).
   */
  TEST_CHECK_(!bst_iterator_has_next(iter),
    "iterator has no more elements to visit");

  bst_iterator_free(iter);
  bst_free(bst);
}

/****************************************************************************
 **
 ** Test listing
 **
 ****************************************************************************/

TEST_LIST = {
  /* bst_size() tests */
  { "bst_random_size", test_bst_random_size },
  { "bst_known_sizes", test_bst_known_sizes },
  /* bst_height() tests */
  { "bst_heights", test_bst_heights },
  /* bst_path_sum() tests */
  { "bst_good_path_sums", test_bst_good_path_sums },
  { "bst_bad_path_sums", test_bst_bad_path_sums },
  /* bst_iterator tests */
  { "bst_iterator_create", test_bst_iterator_create },
  { "bst_iterator_create_empty", test_bst_iterator_create_empty },
  { "bst_iterator_iteration", test_bst_iterator_iteration },
  { NULL, NULL }
};


/****************************************************************************
 **
 ** Auxilliary functions
 **
 ****************************************************************************/


/*
 * This is an auxilliary function that creates a new BST and fills it with
 * values from an array.
 */
struct bst* bst_from_array(const int* array, int n) {
  int i;
  struct bst* bst = bst_create();
  for (i = 0; i < n; i++) {
    bst_insert(array[i], bst);
  }
  return bst;
}


/*
 * This is an auxilliary function that determines whether a given value is
 * contained in an array.  It returns 1 if the value is in the array or 0
 * otherwise.
 */
int contains(int val, const int* array, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (array[i] == val) {
      return 1;
    }
  }
  return 0;
}


/*
 * This is a comparison function to be used with qsort() to sort an array of
 * integers into ascending order.
 */
int ascending_int_cmp (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}
