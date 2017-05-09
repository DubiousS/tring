FOLDER := src/
FOLDER_TWO := build/src/
FOLDER_TEST := build/test/
TARGET := bin/string
CC := gcc
CFLAGS :=  -Wall -Werror -c
EXE_TEST := bin/string-test
LFLAGS := -I thirdparty -I src -c

 
all: $(EXE_TEST) $(TARGET)

$(TARGET): build/src/main.o build/src/function.o build/src/strings.o
		$(CC) build/src/main.o build/src/function.o build/src/strings.o -o $@

build/src/main.o: src/main.c
		$(CC) $(CFLAGS) src/main.c -o $@   

build/src/function.o: src/function.c
		$(CC) $(CFLAGS) src/function.c -o $@ 

build/src/strings.o: src/strings.c
		$(CC) $(CFLAGS) src/strings.c -o $@

$(EXE_TEST): build/test/function_test.o build/test/main.o build/src/function.o build/src/strings.o
		$(CC) build/test/function_test.o build/test/main.o build/src/function.o build/src/strings.o -o $@

build/test/function_test.o: test/function_test.c       
		$(CC) $(LFLAGS) test/function_test.c -o $@   

build/test/main.o: test/main.c 
		$(CC) -I thirdparty -c test/main.c -o $@

.PHONY: all clean
clean:
	rm -f build/src/*.o
	rm -f build/test/*.o
	rm -f bin/*