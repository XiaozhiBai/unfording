# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++14 $(shell root-config --cflags) -I/evtgen/include/Pythia8 -I/evtgen/include
LDFLAGS = $(shell root-config --glibs) -L/evtgen/lib  -lEvtGen -lEvtGenExternal -lpythia8

# Source files and executable name
SOURCES = runSimTreeMaker.cpp EvtGenDecay.cxx
OBJECTS = $(SOURCES:.cpp=.o) 
OBJECTS := $(OBJECTS:.cxx=.o)
EXECUTABLE = runSimTreeMaker

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# To obtain object files from .cpp
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# To obtain object files from .cxx
%.o: %.cxx
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
