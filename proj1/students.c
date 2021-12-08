/*
* This is the file in which you will implement the functionality required by
* the assignment.  Make sure to add your name and @oregonstate.edu email
* address below:
*
* Name: David Kwak
* Email: kwakd@oregonstate.edu
*/

#include <stdio.h>
#include <stdlib.h>

#include "students.h"
#include "dynarray.h"
//#include "dynarray.c"

/*
* This function should allocate and initialize a single student struct with
* name, ID, and GPA data.
*
* Params:
*   name - a string containing the student's name.  Note that you'll have to
*     make a copy of this string to store in the student struct instead of
*     storing this string directly.
*   id - an integer ID for the student
*   gpa - the student's GPA
*
* Return:
*   Should return a newly-allocated student structure whose fields are
*   initialized with the values provided.
*/
struct student* create_student(char* name, int id, float gpa) {
	struct student *stud = malloc(sizeof(*stud));
	stud->name = name;
	stud->id = id;
	stud->gpa = gpa;
	return stud;
}


/*
* This function should free all memory allocated by create_student() for a
* single student.  This function must free all relevant memory and cannot
* result in a memory leak.
*
* Params:
*   student - a pointer to the student whose memory should be freed.  This
*     function must free any memory allocated to the fields of this struct
*     as well as memory allocated for the struct itself.
*/
void free_student(struct student* student) {
	free(student);
}


/*
* This function should create a struct student for each student represented
* in the information provided in the function arguments, and it should store
* those students in a dynamic array (i.e. struct dynarray) allocated by this
* function.  In particular, you should create a dynamic array and insert new
* student structs into it, such that the i'th student in the array has the
* i'th name, the i'th ID, and the i'th GPA from the arrays provided as
* arguments.  You should use your create_student() function to allocate and
* initialize each student struct stored in the array, and you should use the
* provided dynamic array functions to allocate and work with the dynamic
* array.  At the end of the function, you should return the dynamic array
* with student structures stored in it.
*
* Params:
*   num_students - the number of students to be stored in the newly allocated
*     dynamic array
*   names - an array of the names of the students to be stored in the dynamic
*     array of student structs.  This array will have length num_students.
*   ids - an array of the IDs of the students to be stored in the dynamic
*     array of student structs.  This array will have length num_students.
*   gpas - an array of the GPAs of the students to be stored in the dynamic
*     array of student structs.  This array will have length num_students.
*
* Return:
*   Should return a pointer to the newly allocated dynamic array containing
*   newly-created student structs.  The i'th student in this array should have
*   the i'th name, the i'th ID, and the i'th GPA from the arrays provided as
*   arguments.
*/
struct dynarray* create_student_array(int num_students, char** names, int* ids,
	float* gpas) {

	struct dynarray *sarray = dynarray_create();
	for (int i = 0; i < num_students; i++) {
		struct student *stud = create_student(names[i], ids[i], gpas[i]);
		dynarray_insert(sarray, i, stud);
	}
	//int i = dynarray_size(sarray);
	//printf("%d\n", i);
	return sarray;
}


/*
* This function should free all of the memory allocated to a dynamic array of
* student structs, including the memory allocated to the array itself as
* well as any memory allocated to the individual student structs.  You
* should use free_student() to free the memory for each individual student,
* and you should use provided dynamic array functions to free the memory
* associated with the dynamic array itself.  This function must free *all*
* memory associated with a dynamic array of students and must not result in
* any memory leaks.
*
* Params:
*   students - a pointer to the dynamic array of student structs whose memory
*     is to be freed
*/
void free_student_array(struct dynarray* students) {
	dynarray_free(students);
}


/*
* This function should print the name, ID, and GPA of each student in an
* array, one student per line.  You must use provided dynamic array functions
* to access the student data stored in the array.
*
* Params:
*   students - the dynamic array of students to be printed
*/
void print_students(struct dynarray* students) {
	int x = dynarray_size(students);
	for (int i = 0; i < x; i++) {
	printf("  - name: %s\tid: %d\tgpa: %f\n", ((struct student *)dynarray_get(students, i))->name, ((struct student *)dynarray_get(students, i))->id, ((struct student *)dynarray_get(students, i))->gpa);
	}
}


/*
* This function should return a pointer to the student in a given array with
* the highest GPA.  You should not make a copy of the student being returned,
* i.e. this function should not allocate any memory.  Instead, you should
* simply return the pointer to the student struct that's already stored in
* the array.  You must use the provided dynamic array functions to access
* the data stored in the array.
*
* Params:
*   students - the array from which to find the student with the highest GPA
*
* Return:
*   Should return a pointer to the student in the array with the highest GPA.
*   You should not make a copy of the student being returned but should
*   instead return the pointer to the student struct that's already stored in
*   the array.
*/
struct student* find_max_gpa(struct dynarray* students) {
	int x = dynarray_size(students);
	float temp = ((struct student *)dynarray_get(students, 0))->gpa;
	int idx = 0;
	for (int i = 1; i < x; i++){
		if (((struct student *)dynarray_get(students, i))->gpa > temp) {
			temp = ((struct student *)dynarray_get(students, i))->gpa;
			idx = i;
		}


	}
	return ((struct student *)dynarray_get(students, idx));
}


/*
* This function should return a pointer to the student in a given array with
* the lowest GPA.  You should not make a copy of the student being returned,
* i.e. this function should not allocate any memory.  Instead, you should
* simply return the pointer to the student struct that's already stored in
* the array.  You must use the provided dynamic array functions to access
* the data stored in the array.
*
* Params:
*   students - the array from which to find the student with the lowest GPA
*
* Return:
*   Should return a pointer to the student in the array with the lowest GPA.
*   You should not make a copy of the student being returned but should
*   instead return the pointer to the student struct that's already stored in
*   the array.
*/
struct student* find_min_gpa(struct dynarray* students) {
	int x = dynarray_size(students);
	float temp = ((struct student *)dynarray_get(students, 0))->gpa;
	int idx = 0;
	for (int i = 1; i < x; i++) {
		if (((struct student *)dynarray_get(students, i))->gpa < temp) {
			temp = ((struct student *)dynarray_get(students, i))->gpa;
			idx = i;
		}


	}
	return ((struct student *)dynarray_get(students, idx));
}


/*
* This function should sort the students stored in a dynamic array by
* descending GPA (i.e. highest GPAs at the beginning of the array).  You may
* implement any sorting algorithm you want, with the following constraints:
*   - You must sort in place, i.e. you can't allocate additional memory.
*   - You may not use built-in sorting functions like qsort(), i.e. you must
*     implement the sort yourself.  You may implement any in-place sorting
*     algorithm you like.  Some possibilities are selection sort, insertion
*     sort, bubble sort, and quicksort.
*   - You must use provided dynamic array functions (e.g. dynarray_get(),
*     dynarray_set(), etc.) to access and modify the contents of the dynamic
*     array.
*
* Params:
*   students - the dynamic array of students to be sorted.  When the function
*     returns, this array should be sorted by descending GPA.
*/
void sort_by_gpa(struct dynarray* students) {
	int x = dynarray_size(students);


	int idx = 0;
	for (int i = 0; i < x-1; i++) {
		for (int j = 0; j < x-1; j++) {
			if (((struct student *)dynarray_get(students, j))->gpa < ((struct student *)dynarray_get(students, j + 1))->gpa) {

				char *tempname = ((struct student *)dynarray_get(students, j+1))->name;
				int tempid = ((struct student *)dynarray_get(students, j+1))->id;
				float tempgpa = ((struct student *)dynarray_get(students, j+1))->gpa;

				((struct student *)dynarray_get(students, j + 1))->name = ((struct student *)dynarray_get(students, j))->name;
				((struct student *)dynarray_get(students, j + 1))->id = ((struct student *)dynarray_get(students, j))->id;
				((struct student *)dynarray_get(students, j + 1))->gpa = ((struct student *)dynarray_get(students, j))->gpa;
				
				((struct student *)dynarray_get(students, j))->name = tempname;
				((struct student *)dynarray_get(students, j))->id = tempid;
				((struct student *)dynarray_get(students, j))->gpa = tempgpa;

			}
		}

	}

}
