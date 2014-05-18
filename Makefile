CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++11 -ffast-math -march=native
LDFLAGS=-ljpeg
RM=rm -rf
MKDIR=mkdir -p

VPATH = src/

OBJDIR=bin

_OBJS=common.o\
	 OutputBitmap.o\
	 PPMImage.o\
	 Primitive.o\
	 Sphere.o\
	 Raytracer.o\
	 Material.o\
	 Plane.o\
	 JPEGImage.o\
	 TraceProgram.o

OBJS=$(patsubst %, $(OBJDIR)/%, $(_OBJS))

DEPFILE=Makefile.depend

OBJ_SRC=$(patsubst %.o, %.cpp, $(_OBJS))
OBJ_HEAD=$(patsubst %.o, %.h, $(_OBJS))

.PHONY: all clean run config

all: test

$(OBJDIR):
	@$(MKDIR) $@

clean:
	$(RM) test
	$(RM) result.*
	$(RM) $(DEPFILE)
	$(RM) $(OBJDIR)

run: all
	./test
	eog result.ppm &

$(DEPFILE): $(OBJ_SRC) $(OBJ_HEAD)
	@gcc $(CXXFLAGS) -MM $^ > $@ 2> /dev/null

test: test.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@

include $(DEPFILE)
