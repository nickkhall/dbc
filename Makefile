# Compiler
CC = gcc
LDFLAGS = -o $(BIN) $(LIBPATH) $(LIBS)
CFDEBUG = $(CFLAGS) -g -DDEBUG $(LDFLAGS)
RM = /bin/rm -f

SRC = src/db.c
HDR = include/db.h

BIN = libdbc
BINS = libdbc.so
BUILD_DIR = bin
INCLUDES = -I/usr/include/postgresql -I/usr/include
LIBS = -lpq
LIB_DIR = lib
CFLAGS = -std=c18 -Wall -g

# All .c source files
SRC = src/db.c

all: $(BINS)

$(BINS): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -shared -o $(LIB_DIR)/$@ $(SRC) -lc

# prevent confusion with any files named "clean"
.PHONY: clean
clean:
	$(RM) $(LIB_DIR)/*.o $(LIB_DIR)/*.so

debug_code:
	$(RM) debug/debug
	$(CC) -g -o debug/debug $(SRC) $(CFLAGS) $(INCLUDES) $(LIBS)




