#include <stdio.h>
#include "strings.h"
#include "function.h"

int main()
{
    char string[MAX_PATH];
    char symbol_one, symbol_two;
    int inp = input(string, &symbol_one, &symbol_two);

    printf("path: " YEL "%s" RESET "\n", string);
    
    if(inp == 1) {
        output(string, check(string), process(string, &symbol_one, &symbol_two));
    } else if(inp == 0) {
        printf("\x1B[31mUncorrect input path.\n\x1B[0m");
    } else if(inp == -1) {
        printf("\x1B[31mUncorrect input symbol.\n\x1B[0m");
        output(string, check(string), process(string, NULL, NULL));
    }
    
    return 0;
}
