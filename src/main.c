#include <stdio.h>
#include "strings.h"
#include "function.h"
#define MAX_PATH 260

int main()
{
    char string[MAX_PATH];
    char symbol_one, symbol_two;
    int k = 0;

    if(input(string, &symbol_one, &symbol_two)) {
        printf("path: %s\n", string);
        k = check(string);
        if(k == 2) {
            printf("Is URL: yes\n");
            printf("Domain name is correct: yes\n");
        } else if(k == 1) {
            printf("Is URL: yes\n");
            printf("Domain name is correct: no\n");
        } else {
            printf("Is URL: no\n");
        }

    } else {
        printf("Uncorrect input.\n");
    }
    return 0;
}
