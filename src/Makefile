CC = gcc
#--------------------------------------------------------------------------------------------
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror
#--------------------------------------------------------------------------------------------
TEST_FLAGS = -lcheck
TESTS = Tests/test

all: install open

test: clean
	$(CC) $(CFLAGS) $(TESTS).c smartcalc.c $(TEST_FLAGS) -o $(TESTS)
	./$(TESTS)

#install:
#	cmake --build ../cmake-build-debug
#
#open:
#	./../cmake-build-debug/untitled.app/Contents/MacOS/untitled
#
#unistall:
#	rm -rf ../cmake-build-debug/untitled.app

install: clean
	cd ../ && mkdir build
	cd cpp && qmake6 && make && make clean && rm Makefile && cd ../ && mv cpp/smartcalc ../build/

open:
	cd ../build && open smartcalc

uninstall:
	@rm -rf ../build*

clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf Tests/test

rebuild: uninstall install open