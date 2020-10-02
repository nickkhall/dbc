# Compiler
CC = gcc
LDFLAGS = -o $(BIN) $(LIBPATH) $(LIBS)
CFDEBUG = $(CFLAGS) -g -DDEBUG $(LDFLAGS)
RM = /bin/rm -f

SRC = src/db.c
HDR = include/db.h

BIN = libdbc
BINS = libdbc.so
BUILD_DIR = $(LIB_DIR)
INCLUDES = -I/usr/include/postgresql -I/usr/include
LIBS = -lpq
LIB_DIR = lib
CFLAGS = -std=c11 -Wall -g -c -fPIC

# All .c source files
SRC = src/db.c
OBJ = lib/db.o

link: 
	$(CC) $(OBJ) -shared -o $(BUILD_DIR)/$(BINS) 

compile:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(OBJ) 

# prevent confusion with any files named "clean"
.PHONY: clean
clean:
	$(RM) $(LIB_DIR)/*.o $(LIB_DIR)/*.so

debug_code:
	$(RM) debug/debug
	$(CC) -g -o debug/debug $(SRC) $(CFLAGS) $(INCLUDES) $(LIBS)




