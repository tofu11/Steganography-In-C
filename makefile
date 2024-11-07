OS := $(shell uname -s)

<<<<<<< HEAD
ifeq ($(OS), Darwin)
  INCLUDE_PATH := /opt/homebrew/include
  LIB_PATH := /opt/homebrew/lib
endif

ifeq ($(OS), Linux)
  INCLUDE_PATH := /util/criterion/include
  LIB_PATH := /util/criterion/lib/x86_64-linux-gnu
endif

=======

ifeq ($(OS), Darwin)
 INCLUDE_PATH := /opt/homebrew/include
 LIB_PATH := /opt/homebrew/lib
endif


ifeq ($(OS), Linux)
 INCLUDE_PATH := /util/criterion/include
 LIB_PATH := /util/criterion/lib/x86_64-linux-gnu
endif


>>>>>>> 3078d70aa3cb08d2a27f4171a65d1b0c7edaafb5
CC = gcc
CFLAGS = -ggdb -O0 -c -Wall -fprofile-arcs -ftest-coverage
DEBUG = -coverage
OBJECTS = Encode.o Decode.o Steganography.o tests.o

<<<<<<< HEAD
<<<<<<< HEAD


=======
>>>>>>> e5b3177030fee8961457e7789a8cd45d158c1032
Encode.o: Encode.c Stegano_header.h
	$(CC) $(CFLAGS) Encode.c

Decode.o: Decode.c Stegano_header.h
	$(CC) $(CFLAGS) Decode.c

Steganography.o: Steganography.c Stegano_header.h
	$(CC) $(CFLAGS) Steganography.c

<<<<<<< HEAD
Stegano: Encode.o Decode.o Steganography.o tests.o
	$(CC) $(OBJECTS) -o Stegano -lgcov -lcriterion
=======
runner: Encode.o Decode.o Steganography.o
	$(CC) $(CFLAGS) -o runner Encode.o Decode.o Steganography.o
>>>>>>> e5b3177030fee8961457e7789a8cd45d158c1032

tests.o: tests.c Stegano_header.h
	$(CC) -c $(CFLAGS) -I $(INCLUDE_PATH) tests.c

tests: Encode.o Decode.o Steganography.o tests.o
	$(CC) -L $(LIB_PATH) -I $(INCLUDE_PATH) -o tests $(OBJECTS) -lcriterion -lgcov

.PHONY: clean
clean:
<<<<<<< HEAD
	rm -rf *~ *.o code tests Stegano *.dSYM *.gc??
=======
	rm -rf *~ *.o code tests runner *.dSYM *.gc??
>>>>>>> e5b3177030fee8961457e7789a8cd45d158c1032
=======


Encode.o: Encode.c Stegano_header.h
   $(CC) $(CFLAGS) Encode.c


Decode.o: Decode.c Stegano_header.h
   $(CC) $(CFLAGS) Decode.c


Steganography.o: Steganography.c Stegano_header.h
   $(CC) $(CFLAGS) Steganography.c


Stegano: Encode.o Decode.o Steganography.o tests.o
   $(CC) $(OBJECTS) -o Stegano -lgcov -lcriterion


tests.o: tests.c Stegano_header.h
   $(CC) -c $(CFLAGS) -I $(INCLUDE_PATH) tests.c


tests: Encode.o Decode.o Steganography.o tests.o
   $(CC) -L $(LIB_PATH) -I $(INCLUDE_PATH) -o tests $(OBJECTS) -lcriterion -lgcov


.PHONY: clean
clean:
   rm -rf *~ *.o code tests Stegano *.dSYM *.gc??
>>>>>>> 3078d70aa3cb08d2a27f4171a65d1b0c7edaafb5
