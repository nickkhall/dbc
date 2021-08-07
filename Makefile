# Compiler
CC = gcc
LDFLAGS = -o $(BIN) $(LIBPATH) $(LIBS)
CFDEBUG = $(CFLAGS) -g -DDEBUG $(LDFLAGS)
RM = /bin/rm -f

SRC = src/dbsqlc.c
HDR = include/dbsqlc.h

BIN = libdbsqlc
BINS = dbsqlc.so
BUILD_DIR = bin
LIB_DIR = lib
CFLAGS = -std=c18 -Wall -fPIC -shared

all: $(BINS)

$(BINS): $(SRC) $(HDR)
	$(CC) -g -DDEBUG $(CFLAGS) -o $(LIB_DIR)/$@ $(SRC) -lc

# prevent confusion with any files named "clean"
.PHONY: clean
clean:
	$(RM) $(LIB_DIR)/*.o $(LIB_DIR)/*.so

debug_code:
	$(CC) -g -o debug/debug $(SRC) $(CFLAGS) $(INCLUDES) $(LIBS)

