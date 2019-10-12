name =  program
src = $(wildcard src/*.cpp)
incl = include
obj = $(src:.c=.o)

Leda = '/usr/local/LEDA/incl'
LedaLibs = '/usr/local/LEDA'

BOOSTDIR = '/home/theologos/Desktop/boost'


CC = g++
CFLAGS = -std=c++0x -O3
LIBFLAGS = -lleda -lm

DFLAGS = -DEXAMPLE2

all: $(name)

$(name): $(obj)
	$(CC) $(CFLAGS) -o $@ $^  -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)  $(DFLAGS)

run:
	./$(name)

clean:
	rm -f $(name)
