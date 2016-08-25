##
# Makefile
#
# Simple Makefile to build photomosaic program
# and tests
#
CXX = clang++
CXXFLAGS = -Iinclude -std=c++14 -stdlib=libc++ -g -O0 -c -Wall -Wextra
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lpng

.PHONY: all clean tidy

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXENAME = photomosaic

OBJS = photomosaic.o mosaiccanvas.o sourceimage.o maptiles.o \
       rgba_pixel.o epng.o tileimage.o

KDTOBJS = testkdtree.o
KDTMOBJS = mosaiccanvas.o sourceimage.o maptiles.o rgba_pixel.o \
           epng.o tileimage.o

CXXFLAGS += -msse2

PROVIDED_OPTS = -O2 -O0

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXENAME)

photomosaic.o : src/photomosaic.cpp include/epng.h \
                $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/photomosaic.cpp

mosaiccanvas.o : include/mosaiccanvas.h src/mosaiccanvas.cpp include/epng.h
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/mosaiccanvas.cpp

sourceimage.o : include/sourceimage.h src/sourceimage.cpp include/epng.h
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/sourceimage.cpp

tileimage.o : include/tileimage.h src/tileimage.cpp include/epng.h
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/tileimage.cpp

maptiles.o : include/mosaiccanvas.h include/sourceimage.h \
             include/maptiles.h src/maptiles.cpp include/kdtree.h \
             include/kdtree.tcc include/point.h \
             include/point.tcc include/epng.h
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/maptiles.cpp

epng.o: include/epng.h src/epng.cpp
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/epng.cpp

rgba_pixel.o: include/rgba_pixel.h src/rgba_pixel.cpp
	$(CXX) $(CXXFLAGS) $(PROVIDED_OPTS) src/rgba_pixel.cpp

doc: $(wildcard src/*) $(wildcard include/*) mp_mosaic.doxygen
	doxygen mp_mosaic.doxygen

clean:
	rm -f $(EXENAME) $(KDTEXENAME) $(KDTMEXENAME) *.o 2>/dev/null

tidy:
	rm -rf doc