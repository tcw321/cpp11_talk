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

TESTSRC = test.cpp
TESTOBJ = $(TESTSRC:%.cpp=%.o)
TESTEXE = $(TESTSRC:%.cpp=%)

LIBSRC = 
LIBHEADER = 
LIBOBJ = $(LIBSRC:%.cpp=%.o)

SRC = $(LIBSRC) $(TESTSRC)
HEADER = $(LIBHEADER)
OBJ = $(LIBOBJ) $(TESTOBJ)
EXE = $(TESTEXE)

SUBMISSIONS = $(SRC) $(HEADER) Makefile README

all:	$(TESTEXE) run
 

clean:
	rm -f $(OBJ) $(EXE)

target:  $(TESTOBJ)
	$(CC) -o $(TESTEXE) $(TESTOBJ) $(LIBFLAGS)	

run:	$(TESTEXE)
	./test



# gmake depend tacks on a bunch of stuff after this...
