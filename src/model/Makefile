CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=

OBJ=actionstring_syntax_exception.o illegal_move_exception.o Position.o ReversiState.o ReversiAction.o
DEPS=actionstring_syntax_exception.hpp getter_setter.hpp illegal_move_exception.hpp ReversiAction.hpp ReversiAlgorithm.hpp Position.hpp Tile.hpp Player.hpp ReversiState.hpp

.PHONY: all build clean runtest purge

all: build runtest

build: $(OBJ)

runtest: PositionTest ReversiActionTest ReversiStateTest
	./PositionTest
	./ReversiActionTest
	./ReversiStateTest

PositionTest: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReversiActionTest: ReversiActionTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReversiStateTest: ReversiStateTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET): $(OBJ)
#	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
