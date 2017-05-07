#include <stdio.h>
#include "strings.h"
#include "function.h"


int input(char *string, char *symbol_one, char *symbol_two) 
{
    int i = 0;
    printf("Input string: ");
    while(scanf("%c", &string[i]) == 1 && i < MAX_PATH - 1) {
        if(string[i] == '\n') {
            string[i] = '\0';
            break;
        } else {
            i++;
        }
    }
    if(i < 1) {
        return 0;
    } else if(i >= MAX_PATH - 1) {
        string[MAX_PATH - 1] = '\0';
    }
    printf("Symbol 1: ");
    if(scanf("%c", symbol_one) != 1) {
        return 0;
    }

    if(!((*symbol_one > 64 && *symbol_one < 91) ||
         (*symbol_one > 96 && *symbol_one < 123) ||
         (*symbol_one > 47 && *symbol_one < 58))) {
        if(*symbol_one == '/' || 
           *symbol_one == ':' ||
           *symbol_one == '.' || 
           *symbol_one == '-' || 
           *symbol_one == '_') {}
            else return -1;
        
    }

    printf("Symbol 2: ");
    if(scanf(" %c", symbol_two) != 1) {
        return 0;
    }

    if(!((*symbol_two > 64 && *symbol_two < 91) ||
         (*symbol_two > 96 && *symbol_two < 123) ||
         (*symbol_two > 47 && *symbol_two < 58))) {
        if(*symbol_two == '/' || 
           *symbol_two == ':' ||
           *symbol_two == '.' || 
           *symbol_two == '-' || 
           *symbol_two == '_') {} 
            else return -1;
    }
    return 1;  
}

int check(char *string)
{   
    if (slen(string) > MAX_PATH) {
        return -1;
    } else if (sspn(string) > 0) {
        return sspn(string);
    }
    return 0; 
}
int process(char *string, char *symbol_one, char *symbol_two)
{   
    char *null; 
    null = string;
    char pattern_https[] = {'h', 't', 't', 'p', ':', '/', '/', '\0'};
    char pattern_ru[] = {'r', 'u', '\0'};
    char pattern_com[] = {'c', 'o', 'm', '\0'};
    char pattern_org[] = {'o', 'r', 'g', '\0'};
    int i = 0, k = 0, error = 0, delta = 0;
    char domain[MAX_DOMAIN];
    char domain_head[MAX_DOMAIN];
    while(pattern_https[i] != '\0') {
        if(pattern_https[i] == *string) {
            i++;
            string++;
           continue;
       } else return 0;
    }
    i = 0;
    while(*string != '/' && *string != '\0') {
        domain[i] = *string;
        string++;
        i++;
    }
    domain[i] = '\0';
    i = 0;
    while(domain[i] != '\0') {
        if(domain[i] == '.') {
            error++;
            k = 0;
            i++;
        } else if(  (domain[0] > 64 && domain[0] < 91) || 
                    (domain[0] > 96 && domain[0] < 123) ||
                    (domain[0] > 47 && domain[0] < 58)) {
            if(domain[0] > 47 && domain[0] < 58) delta = 1;
            domain_head[k] = domain[i];
            k++;
            i++;
        } else delta = 1;
    }
    domain_head[k] = '\0';

    if(error > 3) return 0;
    
    if( scmp(domain_head, pattern_ru) || scmp(domain_head, pattern_org) || scmp(domain_head, pattern_com)) {
        i = 0;
        if(delta == 1) return 1;
        if(check(string) == 0 && symbol_one != NULL && symbol_two != NULL) {
            while(*(null + i) != '\0') {
            if(*(null + i) == *symbol_one) *(null + i) = *symbol_two;
                i++;
            }
        }
        return 2;
    }
    return 0;
}

int output(const char *string, int error, int code) 
{
    int i = 0;
    if(error == 0) {
        if(code == 2) {
            printf("Is URL: " GRN "yes" RESET "\n");
            printf("Domain name is correct: " GRN "yes" RESET "\n");
            printf("Updated path: %s\n", string);
        } else if(code == 1) {
            printf("Is URL: " GRN "yes" RESET "\n");
            printf("Domain name is correct: " RED "no" RESET "\n");
        } else {
            printf("Is URL:" RED " no\n" RESET);
        }
    } else if(error == -1) {
        printf(RED "Uncorrect length path!" RESET "\n");
    } else if(error == 1) {
        printf(RED "Uncorrect symbol!" RESET "\n");
        while(*string != '\0') {
            if(i == error) {
                printf(RED "%c" RESET, *string);
            }
            i++;
            printf("%c", *string);
            string++;
        }
        printf("\n");
    }
    return 0;
}