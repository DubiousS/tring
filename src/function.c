#include <stdio.h>
#include "strings.h"
#include "function.h"


int input(char string[MAX_PATH], char *symbol_one, char *symbol_two) 
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
    printf("\nSymbol 2: ");
    if(scanf("%c", symbol_two) != 1) {
        return 0;
    }
    return 1;
}

int check(char *string)
{   
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
    
    if( scmp(domain_head, pattern_ru) || 
        scmp(domain_head, pattern_org) || 
        scmp(domain_head, pattern_com)) return 2 - delta;
    else return 0;
}