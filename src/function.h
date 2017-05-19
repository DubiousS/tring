#ifndef FUNCTION_H
#define FUNCTION_H
enum {
    MAX_PATH = 260,
    MAX_DOMAIN = 255 
};
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


int input(char *string, char *symbol_one, char *symbol_two);
int check(char *string);
int process(char *string, char *symbol_one, char *symbol_two);
int output(const char *string, int error, int code);
int fix_dir(char *string, char *symbol_one, char *symbol_two);
int domain_check(char *str);


#endif
