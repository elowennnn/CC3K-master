CXX=g++ 
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
PLAYERS= player/shade.cc player/drow.cc player/vampire.cc player/troll.cc player/goblin.cc
ENEMIES= enemy/orcs.cc
OBJECTS=${SOURCES:.cc=.o} ${PLAYERS:.cc=.o} ${ENEMIES:.cc=.o} # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=cc3k

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g $(OBJECTS) -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
