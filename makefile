PROG = DDD_Linux
CC = g++
CCFLAGS = -Wall -O2 -std=c++11 -fexceptions
LIBS = -lalleg
INC = include
SRC = src
REL = *.o
DEB = *.o

all:rel
	$(CC) -o $(PROG) $(REL) -s -I$(INC) -I$(SRC) $(CCFLAGS) $(LIBS)

rel:*.cpp
	$(CC) -c *.cpp $(SRC)/*.cpp $(INC)/*.h -I$(INC) -I$(SRC) $(CCFLAGS) $(LIBS)

debug:deb
	$(CC) -o $(PROG) $(DEB) -g -I$(INC) -I$(SRC) $(CCFLAGS) $(LIBS)

deb:*.cpp
	$(CC) -c *.cpp $(SRC)/*.cpp $(INC)/*.h -DDEBUG -I$(INC) -I$(SRC) $(CCFLAGS) $(LIBS)

clean:
	rm -rf *.o

,PHONY: all debug clean

