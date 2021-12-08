/*
 * This file contains executable code for testing your work in this assignment.
 */

#include <stdio.h>
#include <stdlib.h>

#include "students.h"
#include "dynarray.h"

/*
 * This is the total number of students in the testing data set.
 */
#define NUM_TESTING_STUDENTS 8


/*
 * These are the names of the students that'll be used for testing.
 */
char* TESTING_NAMES[] = {
  "Luke Skywalker",
  "Princes Leia",
  "Chewbacca",
  "Han Solo",
  "Lando Calrissian",
  "Darth Vader",
  "C-3PO",
  "R2-D2"
};


/*
 * These are the student IDs for the students in the array above that will be
 * used for testing.
 */
int TESTING_IDS[] = {
  933111111,
  933222222,
  933333333,
  933444444,
  933555555,
  933666666,
  933777777,
  933888888
};


/*
 * These are the GPAs of the students above that will be used for testing.
 */
float TESTING_GPAS[] = {
  3.75,
  4.0,
  3.0,
  2.5,
  3.67,
  1.33,
  3.25,
  3.9
};


int main(int argc, char** argv) {
  struct student* s = NULL;
  struct dynarray* students;
  int i;

  /*
   * Create a student using create_student() and print the results.
   */
  s = create_student(TESTING_NAMES[0], TESTING_IDS[0], TESTING_GPAS[0]);
  printf("\n== Here are the results of create_student():\n");
  if (s) {
    printf("  - name: %s\tid: %d\tgpa: %f\n", s->name, s->id, s->gpa);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Free the student created above.
   */
  free_student(s);

  /*
   * Create an array of students using create_student_array() and print the
   * results.
   */
  students = create_student_array(NUM_TESTING_STUDENTS, TESTING_NAMES,
    TESTING_IDS, TESTING_GPAS);
  printf("\n== Here are the results of create_student_array():\n");
  print_students(students);

  /*
   * Use find_max_gpa() to find the student with the highest GPA and print
   * the result.
   */
  s = find_max_gpa(students);
  printf("\n== Here's the student with the highest GPA:\n");
  if (s) {
    printf("  - name: %s\tid: %d\tgpa: %f\n", s->name, s->id, s->gpa);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Use find_min_gpa() to find the student with the lowest GPA and print
   * the result.
   */
  s = find_min_gpa(students);
  printf("\n== Here's the student with the lowest GPA:\n");
  if (s) {
    printf("  - name: %s\tid: %d\tgpa: %f\n", s->name, s->id, s->gpa);
  } else {
    printf("  - NULL\n");
  }

  /*
   * Use sort_by_gpa() to order the students by decreasing GPA and print the
   * results.
   */
  sort_by_gpa(students);
  printf("\n== Here are the students ordered by decreasing GPA:\n");
  print_students(students);

  /*
   * Free the memory we allocated to the array.  You should use valgrind to
   * verify that you don't have memory leaks.
   */
  free_student_array(students);

  return 0;
}
