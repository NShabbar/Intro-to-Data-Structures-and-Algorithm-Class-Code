#-----------------------------------------------------------------------------
# Nadia Shabbar
# nshabbar
# pa6
# Makefile
# Makefile for pa6.
#-----------------------------------------------------------------------------

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make ListClient          makes ListClient
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o List.o BigInteger.o
	g++ -std=c++17 -Wall -g -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : List.h BigInteger.h Arithmetic.cpp
	g++ -std=c++17 -Wall -g -c Arithmetic.cpp
	
ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -g -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -g -c ListTest.cpp
	
BigIntegerTest : BigIntegerTest.o List.o BigInteger.o
	g++ -std=c++17 -Wall -g -o BigIntegerTest BigIntegerTest.o List.o BigInteger.o

BigIntegerTest.o : List.h BigInteger.h ListTest.cpp
	g++ -std=c++17 -Wall -g -c BigIntegerTest.cpp
	
BigIntegerClient : BigIntegerClient.o List.o BigInteger.o
	g++ -std=c++17 -Wall -g -o BigIntegerClient BigIntegerClient.o List.o BigInteger.o

BigIntegerClient.o : List.h BigInteger.h BigIntegerClient.cpp
	g++ -std=c++17 -Wall -g -c BigIntegerClient.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -g -c List.cpp

clean :
	rm -f *.o Arithmetic BigIntegerClient ListTest BigIntegerTest

check1 : BigIntegerClient
	valgrind --leak-check=full BigIntegerClient

check2 : Arithmetic
	valgrind --leak-check=full Arithmetic 35
