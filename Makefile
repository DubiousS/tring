all: src/strings.c src/strings.h src/function.c src/function.h src/main.c
	gcc -Wall -o string src/strings.c src/function.c src/main.c