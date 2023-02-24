CC = gcc
#--------------------------------------------------------------------------------------------
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror
#--------------------------------------------------------------------------------------------
TEST_FLAGS = -lcheck
TESTS = Tests/test
#--------------------------------------------------------------------------------------------
REPORT = gcov_report
GCOV_REPORT = gcov/$(REPORT)
GCOV_INFO = $(GCOV_REPORT).info
GCOV_FLAGS  = --coverage -lcheck
#--------------------------------------------------------------------------------------------
OS = $(shell uname)
SMARTCALC = smartcalc.app
#--------------------------------------------------------------------------------------------
ifeq ($(OS), Linux)
	TEST_FLAGS += -lm -lsubunit -D_GNU_SOURCE -lrt
	GCOV_FLAGS += -lrt -lsubunit -lpthread -lm
	SMARTCALC = smartcalc
endif
#--------------------------------------------------------------------------------------------

.PHONY: all install open dvi dist test gcov_report open uninstall clean rebuild

all: install open

test: clean
	$(CC) $(CFLAGS) $(TESTS).c smartcalc.c $(TEST_FLAGS) -o $(TESTS)
	./$(TESTS)

$(REPORT): clean
	mkdir -p gcov
	gcc $(CFLAGS) smartcalc.c $(TESTS).c $(GCOV_FLAGS) -o $(GCOV_REPORT) -DUNIT_TESTING -ggdb3 -fPIC -O0 --coverage
	./$(GCOV_REPORT)
ifeq ($(OS), Darwin)
	mv *.gcno *.gcda gcov
endif
	lcov -t "$(REPORT)" -o $(GCOV_INFO) -c -d gcov
	genhtml -o report $(GCOV_INFO) $(GCOV_INFO)
	open report/index.html

install: uninstall clean
	cd ../ && mkdir build
	cd cpp && qmake6 && make && make clean && rm Makefile && cd ../ && mv cpp/$(SMARTCALC) ../build/

check_leaks:
ifeq ($(OS) ,Darwin)
	$(CC) $(CFLAGS) smartcalc.c $(TESTS).c $(TEST_FLAGS) -o $(TESTS)
	leaks -atExit -- ./$(TESTS)
else
ifeq ($(OS) ,Linux)
	$(CC) $(CFLAGS) -g $(TESTS).c -o test smartcalc.c $(TEST_FLAGS)
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT.txt ./test
endif
endif

dvi:
	open dvi/index.html

dist:
	rm -rf ../Archive_smartcalc/
	mkdir ../Archive_smartcalc/
	cp -a **/ *.* Makefile ../build/$(SMARTCALC) ../Archive_smartcalc
	cd ../ && tar -cvzf Archive_smartcalc.tar.gz Archive_smartcalc

open:
	cd ../build && open $(SMARTCALC)

uninstall:
	@rm -rf ../build*

clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf .clang-format
	@rm -rf *.info
	@rm -rf Tests/test
	@rm -rf ../*.gz
	@rm -rf ../Archive_smartcalc
	@rm -rf gcov
	@rm -rf test
	@rm -rf RESULT.txt


style:
	@cp ../materials/linters/.clang-format .
	@echo "======= CHECK GOOGLE CODE STYLE ======="
	@sleep 1
	clang-format -n $(TESTS).c $(FUNCS) *.h *.c */*.cpp */*.h


rebuild: uninstall install open
