# glui makefile

STD=-std=c99
WFLAGS=-Wall -Wextra
OPT=-O2
IDIR=-I. -Iinclude
CC=gcc
NAME=libglui
SRC=src/*.c
DLIB=glfw freetype z png jpeg
SLIB=glee gleex fract photon imgtool

LIBS=$(SLIB) $(DLIB)
LDIR=lib
LSTATIC=$(patsubst %,lib%.a,$(SLIB))
LPATHS=$(patsubst %,$(LDIR)/%,$(LSTATIC))
_LFLAGS= $(patsubst %,-L%,$(LDIR)/)
_LFLAGS += $(patsubst %,-l%,$(LIBS))

OS=$(shell uname -s)

ifeq ($(OS),Darwin)
	LFLAGS=$(_LFLAGS) -framework OpenGL -dynamiclib
	LIB=$(NAME).dylib
else
	LFLAGS=$(_LFLAGS) -lm -lGL -lGLEW -shared -fPIC
	LIB=$(NAME).so
endif

CFLAGS=$(STD) $(WFLAGS) $(OPT) $(IDIR)


$(NAME).a: $(SRC)
	$(CC) $(CFLAGS) -c $^ && ar -crv $@ *.o && rm *.o

$(LDIR):
	mkdir $@

$(LDIR)%.a: %
	cd $^ && make && mv $@ ../

$(LDIR)/$(LDIR)%.a: $(LDIR)%.a $(LDIR)
	mv $< $@

shared: $(SRC) $(LPATHS)
	$(CC) -o $(LIB) $(SRC) $(CFLAGS) $(LFLAGS)

clean:
	rm -r $(LDIR) && rm imgtool/imgtool
	
