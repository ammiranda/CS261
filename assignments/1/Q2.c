/* CS261- Assignment 1 - Q.2*/
/* Name: Alexander Miranda
 * Date: March 28, 2016
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a *= 2;
    /*Set b to half its original value*/
    *b /= 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    /*Print the values of x, y and z*/
    printf("x: %d y: %d z: %d\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int result = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("%d\n", result);
    /*Print the values of x, y and z again*/
    printf("x: %d y: %d z: %d\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}

/* The return value is different from the value of z because z was 
 * passed by value into the foo function so the changes to c within
 * the foo function did not point back to the same address of memory
 * that was allocated for z. Therefore z remained unchanged.
*/    
    
