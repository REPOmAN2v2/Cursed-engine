# this makefile is outdated, it will not work
# TODO: compile as library

PACKAGE = cursed_example
VERSION = 0.11.14
DATE = $(shell date "+%b%y")

EXE = $(PACKAGE)

CXXFLAGS = -std=c++11

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -Wall -Wextra -g
else
	CXXFLAGS += -O2 -march=native
endif

LDFLAGS = -lncurses -lconfig++
INCLUDES = -I"engine/"

CXXFILES = $(shell find engine -type f -name '*.cpp')
OBJECTS = $(CXXFILES:.cpp=.o)

DEFINES = -DVERSION=\""$(VERSION)"\" \
		  -DPACKAGE=\""$(PACKAGE)"\" \
		  -DDATE=\""$(DATE)"\"

all: dirs $(EXE)

run: all
	./bin/$(EXE)

dirs: 
	@test -d bin || mkdir bin

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o bin/$(EXE) $(LDFLAGS)

engine/%.o: engine/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(DEFINES) $(INCLUDES)

clean:
	rm -f $(OBJECTS)
	rm -f bin/$(EXE)

.PHONY: default clean check dist distcheck install rebuild uninstall
