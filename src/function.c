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

    int i = 0;
    char domain[MAX_DOMAIN];

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
    if(i < 0) return 0;
    domain[i] = '\0';

    i = domain_check(domain);

    if(check(string) == 0) fix_dir(null, symbol_one, symbol_two);
    return i;
}

int output(const char *string, int error, int code) 
{
    int i = 0;

    if(error == 0) {
        if(code == 2) {
            printf("Is URL: " GRN "yes" RESET "\n");
            printf("Domain name is correct: " GRN "yes" RESET "\n");
            printf("Updated path: %s\n", string);
            return 2;
        } else if(code == 1) {
            printf("Is URL: " GRN "yes" RESET "\n");
            printf("Domain name is correct: " RED "no" RESET "\n");
            return 1;
        } else {
            printf("Is URL:" RED " no\n" RESET);
            return 0;
        }
    } else if(error == -1) {
        printf(RED "Uncorrect length path!" RESET "\n");
        return -1;
    } else if(error > 0) {
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
        return -2;
    }

    return 0;
}


int fix_dir(char *string, char *symbol_one, char *symbol_two)
{
    int k = 0, i = 0;
    while(*(string + k) != '\0') {
        if(*(string + k) == '/') i++;
        k++;
    }
    k = 0;
    if(symbol_one != NULL && symbol_two != NULL) {
        while(*string != '\0') {
            if(*string == '/') k++;
            if(k == 3) {
                break;
            }
            string++;
        }
        while(*string  != '\0') {
            if(*string == '/') k++;
            if(k == i + 1) break; 
            if(*string == *symbol_one) *string = *symbol_two;
            string++;
        }
    }
    return 0;
}

int domain_check(char *str)
{
    int i = 0, ip = 0, status = 0, point = 0, ip_first = 0;
    if(slen(str) <= 3) {
        return 0;
    }
    while(1) {
        if(str[i] > 47 && str[i] < 58) {
            ip = (ip * 10) + str[i] - 48;
            i++;
        } else if(str[i] == '.' || str[i] == '/') {
            if(ip < 0 || ip > 255) break;
            if(point == 3 && ip_first > 0) return 2;
            if(point == 3 && ip_first == 0) return 1;
            if(point == 0) ip_first = ip;
            point++;
            i++;
            ip = 0;
        } else if(str[i] == '\0') {
            if(ip < 0 || ip > 255) break;
            if(point == 3 && ip_first > 0) return 2;
            if(point == 3 && ip_first == 0) return 1;
        } else break;
    }



    point = 0;
    i = 0;
    status = 2;
    while(str[i] != '\0') {
        if(str[i] == '.') {
            point++;
            i++;
        } else if((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123) ||
                  (str[0] > 47 && str[0] < 58)) {
            if(str[0] > 47 && str[0] < 58) {
                status =  1;
                break;
            }
            i++;
        } else return 0;
    }
    if(point > 4) status = 1;
    if(!scmp(str + slen(str) - 3, ".ru")) {
        if(!scmp(str + slen(str) - 4, ".com") || !scmp(str + slen(str) - 4, ".org")) {
            status = 1;
        }
    }
    return status;
}