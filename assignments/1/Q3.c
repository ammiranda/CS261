/* CS261- Assignment 1 - Q.3*/
/* Name: Alexander Miranda
 * Date: March 28, 2016
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
   /*Sort the given array number , of length n*/
   int swap;   

   for (int i = 0; i < (n - 1); i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (number[j] > number[j+1]) {
            swap = number[j];
            number[j] = number[j+1];
            number[j+1] = swap; 
         }
      }
   } 
}

void printArray(int* arr, int length) {
   printf("Array Contents:\n");
   for (int i = 0; i < length; i++) {
      printf("%d\n", arr[i]);
   }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int * arr = (int *)malloc(sizeof(int)*n);
    /*Fill this array with random numbers, using rand().*/
    for (int i = 0; i < n; i++) {
       arr[i] = rand() % 100;
    }
    /*Print the contents of the array.*/
    printArray(arr, n);
    /*Pass this array along with n to the sort() function of part a.*/
    sort(arr, n);    
    /*Print the contents of the array.*/    
    printArray(arr, n);   
    
    if (arr != 0) {
       free(arr); 
    }

    return 0;
}
