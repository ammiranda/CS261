/* CS261- Assignment 1 - Q.1*/
/* Name: Alexander Miranda
 * Date: March 28, 2016
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* students = malloc(10 * sizeof(struct student));
     /*return the pointer*/
     return students;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     int ids[10];

     for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;
     }     

     for (int i = 0; i < 10; i++) {
        int index = rand() % 10;
        while(ids[index] == 0) {
           index = rand() % 10;
        } 
        students[i].id = ids[index]; 
        students[i].score = rand() % 101;
        ids[index] = 0;
     }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    for (int i = 0; i < 10; i++) {
       printf("%d %d\n", students[i].id, students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 100;
    int max = 0;
    float sum = 0;

    for (int i = 0; i < 10; i++) {
       if (students[i].score < min) {
          min = students[i].score;
       }
       if (students[i].score > max) {
          max = students[i].score;
       }
       sum += students[i].score;
    }
    printf("Minimum Score: %d\n", min);
    printf("Maximum Score: %d\n", max);
    printf("Average Score: %f\n", sum / 10); 
}

void deallocate(struct student* stud){
     if (stud != 0) {
        free(stud);
     }
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
