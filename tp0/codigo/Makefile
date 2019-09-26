CC = g++   #g++ o clang++
CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  = -g 
OBJS = main.o cmdline.o ComplexSignal.o DynamicArray.o complex.o

all: tp0

tp0: $(OBJS)	
	$(CC) $(LDFLAGS) -o tp0 $(OBJS)

main.o: main.cpp cmdline.h ComplexSignal.hpp DynamicArray.hpp complex.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(CXXFLAGS) -c cmdline.cpp
	
ComplexSignal.o: ComplexSignal.cpp ComplexSignal.hpp complex.hpp DynamicArray.hpp
	$(CC) $(CXXFLAGS) -c ComplexSignal.cpp

DynamicArray.o: DynamicArray.cpp DynamicArray.hpp
	$(CC) $(CXXFLAGS) -c DynamicArray.cpp

complex.o: complex.cpp complex.hpp
	$(CC) $(CXXFLAGS) -c complex.cpp
	
	
clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
