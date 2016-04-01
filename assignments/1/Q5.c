/* CS261- Assignment 1 - Q.5*/
/* Name: Alexander Miranda
 * Date: March 29, 2016
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
     for (int i = 0; word[i] != '\0'; i++) {
        int isEven = i % 2 == 0 ? 1 : 0;
        if (!isEven && (word[i] >= 'A' && word[i] <= 'Z')) {
           word[i] += 32;
        } else if (isEven && (word[i] > 'a' && word[i] <= 'z')) {
           word[i] -= 32;
        }
     }
}

int main(){
    char word[30];
    printf("Enter word (30 chars or less):\n");
    /*Read word from the keyboard using scanf*/
    scanf("%30s", word);
    /*Call sticky*/
    sticky(word);
    /*Print the new word*/
    printf("%s\n", word);
    return 0;
}
