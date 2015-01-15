CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++11
LDFLAGS=-ljpeg
RM=rm -rf
MKDIR=mkdir -p

VPATH = src/

OBJDIR=bin
DEPDIR=.deps

DIRS=$(OBJDIR)\
	 $(DEPDIR)

_OBJS=$(patsubst %.cpp, %.o, $(notdir $(wildcard src/*.cpp)))
DEPS=$(patsubst %.o, $(DEPDIR)/%.depend, $(_OBJS))
OBJS=$(patsubst %, $(OBJDIR)/%, $(_OBJS))

DEPFILE=Makefile.depend

CPPFILES=$(wildcard src/*.cpp)

.PHONY: all clean run config

all: test

$(DIRS):
	$(MKDIR) $@

clean:
	$(RM) test
	$(RM) $(DEPFILE)
	$(RM) $(DIRS)

$(DEPFILE): $(CPPFILES)
	gcc $(CXXFLAGS) -MM $^ > $@ 2> /dev/null

test: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(DEPDIR)/%.depend: %.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) -MM -MG -MT $(OBJDIR)/$(basename $(notdir $<)).o -MF $@ $<

include $(DEPS)
