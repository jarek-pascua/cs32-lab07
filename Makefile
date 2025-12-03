#Makefile

CXX=clang++

CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field 

BINARIES=lab07Test

all: ${BINARIES}

lab07Test : lab07Test.o WordCount.o tddFuncs.o
	${CXX} $^ -o $@

tests: ${BINARIES}
	./lab07Test

clean:
	/bin/rm -f ${BINARIES} *.o
