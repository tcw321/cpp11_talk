VERSION = RELEASE

DEBUG_CFLAGS = -g -DUSE_HEAP_STATS
PROFILE_CFLAGS = -pg
RELEASE_CFLAGS = -O2

ifeq "$(VERSION)" "PROFILE"
CFLAGS = $(PROFILE_CFLAGS)
else
ifeq "$(VERSION)" "DEBUG"
CFLAGS = $(DEBUG_CFLAGS) -std=c++11
else
ifeq "$(VERSION)" "RELEASE"
CFLAGS = $(RELEASE_CFLAGS) -std=c++11
LIBFLAGS = -std=c++11
endif
endif
endif

CXX2 = clang++-mp-3.1
CXX = g++-mp-4.7 
CC = $(CXX)
CXXFLAGS = $(CFLAGS)

TESTSRC = test.cpp ramp.cpp simulation.cpp
TESTOBJ = $(TESTSRC:%.cpp=%.o)
TESTEXE = test

LIBSRC = 
LIBHEADER = collector.hpp simulation.hpp icollector.hpp ramp.hpp
LIBOBJ = $(LIBSRC:%.cpp=%.o)

SRC = $(LIBSRC) $(TESTSRC)
HEADER = $(LIBHEADER)
OBJ = $(LIBOBJ) $(TESTOBJ)
EXE = $(TESTEXE)

SUBMISSIONS = $(SRC) $(HEADER) Makefile README

all:	depend run


clean:
	rm -f $(OBJ) $(EXE)

exe:	$(TESTOBJ) 
	$(CC) -o $(TESTEXE) $(TESTOBJ) $(LIBFLAGS)	

run:	exe
	./test

depend: .depend

.depend: $(TESTSRC)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

# gmake depend tacks on a bunch of stuff after this...
