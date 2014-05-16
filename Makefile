CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++11 -ffast-math -march=native
LDFLAGS=-ljpeg

OBJS=common.o\
	 OutputBitmap.o\
	 PPMImage.o\
	 Primitive.o\
	 Sphere.o\
	 Raytracer.o\
	 Material.o\
	 Plane.o\
	 JPEGImage.o

DEPFILE = .depends

OBJ_SRC=$(patsubst %.o, %.cpp, $(OBJS))
OBJ_HEAD=$(patsubst %.o, %.h, $(OBJS))

.PHONY: all clean run config

all: $(DEPFILE) test

clean:
	$(RM) test *.o .depends*

run: all
	./test
	eog result.ppm &

$(DEPFILE): $(OBJ_SRC) $(OBJ_HEAD)
	gcc $(CXXFLAGS) -MM $(OBJ_SRC) > $@

test: test.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(LDFLAGS)

include $(DEPFILE)
