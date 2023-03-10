#-----------------------------------------------------------------------------
# Nadia Shabbar
# nshabbar
# pa7
# Makefile
# Makefile for pa7.
#-----------------------------------------------------------------------------

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Order
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make OrderCheck          runs Order under valgrind on in5 junk5
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -g -o Order Order.o Dictionary.o

Order.o : Dictionary.h Order.cpp
	g++ -std=c++17 -Wall -g -c Order.cpp
	
DictionaryTest : DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -g -o DictionaryTest DictionaryTest.o Dictionary.o 

DictionaryTest.o : Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -g -c DictionaryTest.cpp

DictionaryClient : DictionaryClient.o Dictionary.o Dictionary.o
	g++ -std=c++17 -Wall -g -o DictionaryClient DictionaryClient.o Dictionary.o Dictionary.o

DictionaryClient.o : Dictionary.h Dictionary.h DictionaryClient.cpp
	g++ -std=c++17 -Wall -g -c DictionaryClient.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -g -c Dictionary.cpp

clean :
	rm -f *.o Order DictionaryClient DictionaryTest DictionaryTest

check1 : DictionaryClient
	valgrind --leak-check=full DictionaryClient

check2 : Order
	valgrind --leak-check=full Order 35