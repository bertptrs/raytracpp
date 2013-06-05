CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3

.PHONY: all clean

all: test

test: test.cc common.o
	$(CXX) $(CXXFLAGS) $^ -o $@

common.o: common.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
