/*
 * This file contains the definitions of structures you'll use for this
 * assignment along with prototypes of functions you'll have to write.  You
 * should not modify anything in this file.
 */

#include "dynarray.h"

/*
 * This structure represents information about a single university student.
 */
struct student {
  char* name;
  int id;
  float gpa;
};


/*
 * These are the prototypes of the functions you will write in students.c.
 * See the documentation in students.c for more information about each
 * function.
 */
struct student* create_student(char* name, int id, float gpa);
void free_student(struct student* student);
struct dynarray* create_student_array(int num_students, char** names, int* ids,
    float* gpas);
void free_student_array(struct dynarray* students);
void print_students(struct dynarray* students);
struct student* find_max_gpa(struct dynarray* students);
struct student* find_min_gpa(struct dynarray* students);
void sort_by_gpa(struct dynarray* students);
