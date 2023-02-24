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
#--------------------------------------------------------------------------------------------
ifeq ($(OS), Linux)
	TEST_FLAGS += -lm -lsubunit -D_GNU_SOURCE -lrt
	GCOV_FLAGS += -lrt -lsubunit -lpthread -lm
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
	cd cpp && qmake6 && make && make clean && rm Makefile && cd ../ && mv cpp/smartcalc ../build/

dvi:
	open dvi/index.html

dist:
	rm -rf ../Archive_smartcalc/
	mkdir ../Archive_smartcalc/
	cp -a -r **/ *.* Makefile ../build/smartcalc ../Archive_smartcalc
	cd ../ && tar -cvzf Archive_smartcalc.tar.gz Archive_smartcalc

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
	@rm -rf ../*.gz
	@rm -rf ../Archive_smartcalc
	@rm -rf gcov



rebuild: uninstall install open
