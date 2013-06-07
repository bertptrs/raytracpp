CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++0x

.PHONY: all clean

all: test

clean:
	$(RM) test *.o

test: test.cc common.o PPMImage.o OutputBitmap.o
	$(CXX) $(CXXFLAGS) $^ -o $@

common.o: common.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

OutputBitmap.o: OutputBitmap.cpp OutputBitmap.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

PPMImage.o: PPMImage.cpp PPMImage.h OutputBitmap.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
