#------------------------------------------------------------------------------
#  Nadia Shabbar
#  nshabbar
#  pa4
#  Makefile for CSE 101 Programming Assignment 3
#
#  make                     makes Sparse
#  make MatrixClient         makes MatrixClient
#  make clean               removes binaries
#  make checkFind           tests Sparse for memory leaks on in3
#  make checkClient         tests MatrixClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c -g
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

MatrixClient : MatrixClient.o $(BASE_OBJECTS)
	$(LINK) MatrixClient MatrixClient.o $(BASE_OBJECTS)
	
MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixClient.o : MatrixClient.c $(HEADERS)
	$(COMPILE) MatrixClient.c
	
MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) *.o Sparse MatrixClient MatrixTest $(BASE_OBJECTS)

checkFind : Sparse
	$(MEMCHECK) Sparse in8 junk8

checkClient : MatrixClient
	$(MEMCHECK) MatrixClient

checkTest : MatrixTest
	$(MEMCHECK) MatrixTest