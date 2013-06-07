CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++0x

OBJS=common.o\
	 OutputBitmap.o\
	 PPMImage.o\
	 Primitive.o\
	 Sphere.o

.PHONY: all clean run

all: test

run: all
	./test
	eog result.ppm &

clean:
	$(RM) test *.o

test: test.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

common.o: common.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

OutputBitmap.o: OutputBitmap.cpp OutputBitmap.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

PPMImage.o: PPMImage.cpp PPMImage.h OutputBitmap.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Primitive.o: Primitive.cpp Primitive.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Sphere.o: Sphere.cpp Sphere.h Primitive.h common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
