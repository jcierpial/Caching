COMPILER = gcc
CCFLAGS  = -Wall
all: cachesize cacheblock

debug:
	make DEBUG=TRUE

cachesize.o: cachesize.c cachesize.h
	$(COMPILER) $(CCFLAGS) -c cachesize.c cachesize.h
cachesize: cachesize.o
	$(COMPILER) $(CCFLAGS) -o cachesize cachesize.o
	
cacheblock: cacheblock.o
	$(COMPILER) $(CCFLAGS) -o cacheblock cacheblock.o
cacheblock.o: cacheblock.c cacheblock.h
	$(COMPILER) $(CCFLAGS) -c cacheblock.c cacheblock.h

ifeq ($(DEBUG), TRUE)
 CCFLAGS += -g
endif

clean:
	rm -f cachesize
	rm -f cacheblock
	rm -f *.o