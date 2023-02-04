CC = gcc
#--------------------------------------------------------------------------------------------
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror
#--------------------------------------------------------------------------------------------
TEST_FLAGS = -lcheck
TESTS = Tests/test

all: clean test

test: clean
	$(CC) $(CFLAGS) $(TESTS).c stack.c $(TEST_FLAGS) -o $(TESTS)
	./$(TESTS)


clean:
	rm -rf test *.o