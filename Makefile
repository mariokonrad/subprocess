.PHONY: all clean

CXX=g++-5
CXXFLAGS=-Wall -Wextra -Werror -pedantic -O0 -ggdb -std=c++1y

all : test

test : test.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test.o : test.cpp subprocess.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o $@

clean :
	rm -f *.o
	rm -f test

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

