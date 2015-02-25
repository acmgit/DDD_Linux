#Makefile (?) by A.C.M.
#it was f**ing hard to create this file, pls handle it with care
#-----------------------------------------------------------------------------------------------

PROGNAME = DDD_Linux
PROGNAME_DEBUG = DDD_Linux_Debug
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

#Foregroundcolors
STANDARD = \e[0m
FBLACK = \e[1;30m
FRED = \e[1;31m
FGREEN = \e[1;32m
FYELLOW = \e[1;33m
FBLUE = \e[1;34m
FPURPLE = \e[1;35m
FCYAN = \e[1;36m

#Backgroundcolors
BBLACK = \e[1;40m
BRED = \e[1;41m
BGREEN = \e[1;42m
BYELLOW = \e[1;43m
BBLUE = \e[1;44m
BPURPLE = \e[1;45m
BCYAN = \e[1;46m

#Dekoration
DLEFT = $(FBLUE)-----=====<
DRIGHT = $(FBLUE) >=====-----$(STANDARD)

release:rel
	@echo -e ' $(DLEFT) linking Programm [$(FPURPLE)$(PROGNAME)$(FBLUE)],$(DRIGHT)'
	$(CC) -o $(PROGNAME) $(OBJDIR)/$(OBJ) -s -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSRELEASE) $(LIBS)
	@echo -e '$(DLEFT) done, now enjoy $(FGREEN)$(PROGNAME)$(FBLUE).$(DRIGHT)'

rel:*.cpp
	@echo -e '$(DLEFT) Compiling [$(FRED)$(SRC)$(FBLUE)],$(DRIGHT)'
	$(CC) -c $(SRC) $(INCLUDE)/$(INC)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSRELEASE) $(LIBS)
	@echo -e '$(DLEFT) compiling [$(FRED)$(SOURCE)/$(SRC)$(FBLUE)],$(DRIGHT)'
	$(CC) -c $(SOURCE)/$(SRC) $(INCLUDE)/$(INC)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSRELEASE) $(LIBS)

debug:deb
	@echo -e '$(DLEFT) linking Programm [$(FPURPLE)$(PROGNAME)$(FBLUE)],$(DRIGHT)'
	$(CC) -o $(PROGNAME_DEBUG) $(OBJDIR)/$(OBJ) -g -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSDEBUG) $(LIBS)
	@echo -e '$(DLEFT) be care, this is to Debug $(FGREEN)$(PROGNAME)$(FBLUE).$(DRIGHT)'

deb:*.cpp
	@echo -e '$(DLEFT) Compiling [$(FRED)$(SRC)$(FBLUE)],$(DRIGHT)'
	$(CC) -c $(SRC) $(INCLUDE)/$(INC) $(DEBFLAG)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSDEBUG) $(LIBS)
	@echo -e '$(DLEFT) compiling [$(FRED)$(SOURCE)/$(SRC)$(FBLUE)],$(DRIGHT)'
	$(CC) -c $(SOURCE)/$(SRC) $(INCLUDE)/$(INC) $(DEBFLAG)  -I$(INCLUDE) -I$(SOURCE) $(CCFLAGSDEBUG) $(LIBS)

clean:
	@echo -e '$(DLEFT) Cleaning [$(FRED)$(OBJDIR)/$(OBJ)$(FBLUE)],$(DRIGHT)'
	rm -rf $(OBJDIR)/$(OBJ)
	@echo -e '$(DLEFT) cleaning [$(FPURPLE)$(INCLUDE)/$(INCOBJ)$(FBLUE)],$(DRIGHT)'
	rm -rf $(INCLUDE)/$(INCOBJ)
	@echo -e '$(DLEFT) $(FGREEN)done, this was a dirty job.$(DRIGHT)'

,PHONY: debug release clean

