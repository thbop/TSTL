CC = g++
CCFLAGS = -fdiagnostics-color=always -Wall -std=c++23 -Iinclude -g

SOURCES = $(wildcard src/TSTL/*.cpp)
OBJECTS = $(patsubst src/TSTL/%.cpp, lib/%.o, $(SOURCES))
TEST_LDFLAGS = -Llib -lTSTL
TEST_SOURCES = $(wildcard src/tests/*.cpp)
TEST_OUTPUTS = $(patsubst src/tests/%.cpp, bin/%.exe, $(TEST_SOURCES))
OUTPUT = lib/libTSTL.a

all: always $(OBJECTS)

test: always $(OBJECTS) $(TEST_OUTPUTS)

always:
	mkdir -p lib bin

lib/%.o: src/TSTL/%.cpp
	$(CC) -c $< -o $@ $(CCFLAGS)
	ar -rv $(OUTPUT) $@

bin/%.exe: src/tests/%.cpp
	$(CC) $< -o $@ $(CCFLAGS) $(TEST_LDFLAGS)

clean:
	rm bin/*.exe
	rm lib/*.o
