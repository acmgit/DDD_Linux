PROG = DDD_Linux
CC = g++
CCFLAGSRELEASE = -Wall -Wextra -O3 -std=c++11 -fexceptions -fexpensive-optimizations
CCFLAGSDEBUG = -Wall -Wextra -std=c++11 -fexceptions
LIBS = -lalleg
INCLUDE = include
SOURCE = src
OBJ = *.o
SRC = *.cpp
INC = *.h
INCOBJ = *.gch
DEBFLAG = -DDEBUG
OBJDIR = .

release:rel
	$(CC) -o $(PROG) $(OBJDIR)/$(OBJ) -s -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSRELEASE) $(LIBS)

rel:*.cpp
	$(CC) -c $(SRC) $(SOURCE)/$(SRC) $(INCLUDE)/$(INC)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSRELEASE) $(LIBS)

debug:deb
	$(CC) -o $(PROG) $(OBJDIR)/$(OBJ) -g -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSDEBUG) $(LIBS)

deb:*.cpp
	$(CC) -c $(SRC) $(SOURCE)/$(SRC) $(INCLUDE)/$(INC) $(DEBFLAG)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSDEBUG) $(LIBS)

clean:
	rm -rf $(OBJDIR)/$(OBJ)
	rm -rf $(INCLUDE)/$(INCOBJ)

,PHONY: debug release clean

