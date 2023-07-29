SRCS1 = basicAccess.cxx
OBJS1 = $(SRCS1:.cxx=.o)
DEPS  = FlowUtils.h
TARGET1 = basicAccess

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
ROOTLIBS     += -lEG

INCFLAGS = -I$(ROOTSYS)/include -I./ -I./StRoot -I./StRoot/StEvent -I./StRoot/StPicoEvent
#LIBFLAGS = -L$(ROOTSYS)/lib -L./ -L./libs -Wl,-R./libs
LIBFLAGS = -L$(ROOTSYS)/lib -L./ -L./StRoot/StEpdUtil/ -Wl,-R./StRoot/StEpdUtil/ -L./StRoot/StPicoEvent/ -Wl,-R./StRoot/StPicoEvent
SOLIBS = -lStPicoDst -lStEpdUtil
#for each non-standard dynamic library location -L a corresponding -Wl,-R should be specified
#the -L's to StPicoEvent, StEpdUtil, and StBichsel are for locating libStPicoEvent.so, libStEpdUtil.so, and libStBichsel.so
#the -l's are to link these .so files

CC = g++ #-m32
FLAGS = -Wall -g -fPIC

COMPILE = $(CC) $(FLAGS)


all: $(TARGET1)

$(TARGET1): $(OBJS1)
	$(COMPILE) -o $@ $^ $(SOLIBS) $(ROOTCFLAGS) $(ROOTLIBS) $(INCFLAGS) $(LIBFLAGS)

basicAccess.o: basicAccess.cxx
	$(COMPILE) -o $@ -c basicAccess.cxx $(SOLIBS) $(ROOTCFLAGS) $(ROOTLIBS) $(INCFLAGS) $(LIBFLAGS)

.PHONY: clean

clean:
	rm -f *.so $(TARGET1) $(OBJS1)



# target : dependencies
#	action

# $@ = current target
# $^ = current dependencies
# $< = name of the related file that caused the action
