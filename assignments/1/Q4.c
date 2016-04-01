/* CS261- Assignment 1 - Q.4*/
/* Name: Alexander Miranda
 * Date: March 29, 2016
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
   struct student swap;

   for (int i = 0; i < (n - 1); i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (students[j].score > students[j+1].score) {
            swap = students[j];
            students[j] = students[j+1];
            students[j+1] = swap;
         }
      }
   }     
}

struct student* allocate(int n) {
   struct student* students = malloc(n * sizeof(struct student));
   return students;
}

void generate(struct student* students, int n){
   int ids[n];
   
   for (int i = 0; i < n; i++) {
      ids[i] = i + 1;
   }

   for (int i = 0; i < n; i++) {
      int index = rand() % n;
      while(ids[index] == 0) {
         index = rand() % n;
      }
      students[i].id = ids[index];
      students[i].score = rand() % 101;
      ids[index] = 0;
   }
}

void output(struct student* students, int n) {
   printf("Array Contents:\n");
   for (int i = 0; i < n; i++) {
      printf("%d %d\n", students[i].id, students[i].score);
   }
}

void deallocate(struct student* stud) {
   if (stud != 0){
      free(stud);
   }
}

int main(){
    struct student* stud = NULL;
    /*Declare an integer n and assign it a value.*/
    int n = 10;
    /*Allocate memory for n students using malloc.*/
    stud = allocate(n);
    /*Generate random IDs and scores for the n students, using rand().*/
    generate(stud, n);
    /*Print the contents of the array of n students.*/
    output(stud, n);
    /*Pass this array along with n to the sort() function*/
    sort(stud, n);
    /*Print the contents of the array of n students.*/
    output(stud, n);
    /*Deallocate the student array*/
    deallocate(stud);
    return 0;
}
