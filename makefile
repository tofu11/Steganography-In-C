OS := $(shell uname -s)

ifeq ($(OS), Darwin)
  INCLUDE_PATH := /opt/homebrew/include
  LIB_PATH := /opt/homebrew/lib
endif

ifeq ($(OS), Linux)
  INCLUDE_PATH := /util/criterion/include
  LIB_PATH := /util/criterion/lib/x86_64-linux-gnu
endif

CC = gcc
CFLAGS = -ggdb -O0 -c -Wall -fprofile-arcs -ftest-coverage
DEBUG = -coverage
OBJECTS = Encode.o Decode.o Steganography.o tests.o

# Separate compilation and linking steps
Stegano: Encode.o Decode.o Steganography.o
	$(CC) $(OBJECTS) -o Stegano

Encode.o: Encode.c Stegano_header.h
	$(CC) $(CFLAGS) Encode.c

Decode.o: Decode.c Stegano_header.h
	$(CC) $(CFLAGS) Decode.c

Steganography.o: Steganography.c Stegano_header.h
	$(CC) $(CFLAGS) Steganography.c

tests.o: tests.c Stegano_header.h
	$(CC) -c $(CFLAGS) -I $(INCLUDE_PATH) tests.c

tests: Encode.o Decode.o Steganography.o tests.o
	$(CC) -L $(LIB_PATH) -I $(INCLUDE_PATH) -o tests $(OBJECTS) -lcriterion -lgcov

.PHONY: clean
clean:
	rm -rf *~ *.o code tests Stegano *.dSYM *.gc??
