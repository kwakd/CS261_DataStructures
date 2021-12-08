/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct node {
    int priority;
    void* value;
};

struct node* node_create(int priority, void* value) {
    struct node* node = malloc(sizeof(struct node));
    assert(node);
    node->priority = priority;
    node->value = value;
    return node;
}

void node_free(struct node* node) {
    assert(node);
    free(node);
}

/* ----------------------------------------------------------- */
struct pq {
    struct dynarray *heap;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
    struct pq* pq = malloc(sizeof(struct pq));
    assert(pq);
    pq->heap = dynarray_create();
    return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
    assert(pq);
    dynarray_free(pq->heap);
    free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
    assert(pq);
    if (dynarray_size(pq->heap)) return 0;
    return 1;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {

    /* check if pq is empty */
    if (dynarray_size(pq->heap)==0) {
        struct node* node = node_create(priority, value);
        dynarray_insert(pq->heap, 0, node);
        return;
    }

    // first, insert the new node at the end 
    struct node* node = node_create(priority, value);
    int node_idx = dynarray_size(pq->heap); // node_idx is dynarray index
    dynarray_insert(pq->heap, node_idx, node);

    // fix the min heap property if it is violated 
    int parent_node_idx = (node_idx-1) / 2;
    struct node* parent_node = dynarray_get(pq->heap, parent_node_idx);
    while (node_idx > 0 && parent_node->priority > node->priority) {
        // swap two nodes
        dynarray_set(pq->heap, node_idx, parent_node);
        dynarray_set(pq->heap, parent_node_idx, node);

        node_idx = parent_node_idx;
        parent_node_idx = (parent_node_idx-1) / 2;
        node = dynarray_get(pq->heap, node_idx);
        parent_node = dynarray_get(pq->heap, parent_node_idx);
    }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
    return dynarray_get(pq->heap, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
    struct node* node = pq_first(pq);
    return node->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
    assert(pq);

    // get root node and save it to local variable 'first_node'
    struct node* first_node = dynarray_get(pq->heap, 0);

    // copy the last node to the root
    int last_node_idx = dynarray_size(pq->heap)-1; // last_node_idx is dynarray index
    struct node* last_node = dynarray_get(pq->heap, last_node_idx);
    dynarray_set(pq->heap, 0, last_node);   // now, last node becomes root

    // remove last node
    dynarray_remove(pq->heap, last_node_idx);
    last_node_idx = dynarray_size(pq->heap)-1; // update last_node_idx

    // bubble element down 
    // always with smaller child (between left and right child), 
    // until heap invariant is true again

    int node_idx = 0;   // start from root, and bubble down
    while (node_idx < last_node_idx) {
        
        struct node* node = dynarray_get(pq->heap, node_idx);

        // get children
        int left_child_idx = 2 * node_idx + 1;
        int right_child_idx = 2 * node_idx + 2;
        
        struct node* left_child_node;
        struct node* right_child_node;

        // get out of while loop if current node is leaf node
        if (left_child_idx > last_node_idx && right_child_idx > last_node_idx) {
            break;        
        }

        // if left child does not exist, pick right child
        if (left_child_idx > last_node_idx) {
            right_child_node = dynarray_get(pq->heap, right_child_idx);
            if (right_child_node->priority < node->priority) {
                // swap two nodes
                dynarray_set(pq->heap, node_idx, right_child_node);
                dynarray_set(pq->heap, right_child_idx, node);
                node_idx = right_child_idx;
                continue;
            }
            else {
                break;
            }
        }

        // if right child does not exist, pick left child
        if (right_child_idx > last_node_idx) {
            left_child_node = dynarray_get(pq->heap, left_child_idx);
            if (left_child_node->priority < node->priority) {
                // swap two nodes
                dynarray_set(pq->heap, node_idx, left_child_node);
                dynarray_set(pq->heap, left_child_idx, node);
                node_idx = left_child_idx;
                continue;
            }
            else {
                break;
            }
        }

        // both childeren exist. pick one smaller
        left_child_node = dynarray_get(pq->heap, left_child_idx);
        right_child_node = dynarray_get(pq->heap, right_child_idx);
        if (left_child_node->priority <= right_child_node->priority) {  // pick left
            if (left_child_node->priority < node->priority) {
                // swap two nodes
                dynarray_set(pq->heap, node_idx, left_child_node);
                dynarray_set(pq->heap, left_child_idx, node);
                node_idx = left_child_idx;
            }
            else {
                break;
            }
        }
        else {  // pick right child
            if (right_child_node->priority < node->priority) {
                // swap two nodes
                dynarray_set(pq->heap, node_idx, right_child_node);
                dynarray_set(pq->heap, right_child_idx, node);
                node_idx = right_child_idx;
            }
            else {
                break;
            }
        }
    }

    return first_node->value;
}
