SRCS = VnFromInnerEPD-V3.cxx
OBJS = $(SRCS:.cxx=.o)
DEPS = FlowFunctions.h DeuteronsAndTritons.h TileVector.h
TARGET = VnFromInnerEPD-V3

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTLIBS     += -lEG

# Dynamic detection of STAR's CONS platform directory (sl73 vs al9)
# If CONS_PLATFORM isn't set in your environment, we default to whatever exists in StRoot
# CONS_PLATFORM ?= $(shell ls -d ../StRoot/.[a-z]*_x8664_gcc* 2>/dev/null | sed 's|../StRoot/\.||' | head -n 1)

# If the above dynamic check fails, you can manually replace it with your Alma9 folder name, e.g.:
# CONS_PLATFORM = al9_x8664_gcc11

CONS_LIB_DIR = ../StRoot/.al9_x8664_gcc11/lib
CONS_INC_DIR = ../StRoot/.al9_x8664_gcc11/include

INCFLAGS = -I$(ROOTSYS)/include -I../StRoot/StPicoEvent -I../StRoot/StEpdUtil -I../StRoot/StBichsel -I$(CONS_INC_DIR)
LIB_DIR  = ./libs
# Added -L$(CONS_LIB_DIR) and runtime path -Wl,-R$(CONS_LIB_DIR) so the linker can find STAR shared objects
LIBFLAGS = -L$(ROOTSYS)/lib -L$(LIB_DIR) -L$(CONS_LIB_DIR) -Wl,-R$(LIB_DIR) -Wl,-R$(CONS_LIB_DIR)
SOLIBS   = -lStPicoDst -lStEpdUtil -lStBichsel

CC = g++
# CHANGED: Replaced -std=c++0x (C++11 preview) with modern -std=c++17 or c++14 required by Alma9/ROOT6
FLAGS = -Wall -g -fPIC -std=c++11 -m64 -pthread

COMPILE = $(CC) $(FLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(COMPILE) -o $@ $(OBJS) $(LIBFLAGS) $(SOLIBS) $(ROOTLIBS)

VnFromInnerEPD-V3.o: VnFromInnerEPD-V3.cxx $(DEPS)
	$(COMPILE) $(ROOTCFLAGS) $(INCFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
