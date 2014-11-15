CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=

OBJ=actionstring_syntax_exception.o illegal_action_exception.o Position.o ReversiAction.o OthelloState.o 
DEPS=actionstring_syntax_exception.hpp getter_setter.hpp illegal_action_exception.hpp Player.hpp Position.hpp ReversiAction.hpp ReversiAlgorithm.hpp OthelloState.hpp Tile.hpp

.PHONY: all build clean runtest purge

all: build runtest

build: $(OBJ)

runtest: PositionTest ReversiActionTest OthelloStateTest
	./PositionTest
	./ReversiActionTest
	./OthelloStateTest

PositionTest: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReversiActionTest: ReversiActionTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

OthelloStateTest: OthelloStateTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET): $(OBJ)
#	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
