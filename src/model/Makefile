CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=

OBJ=Game.o actionstring_syntax_exception.o illegal_action_exception.o Position.o OthelloAction.o OthelloState.o 
DEPS=Game.hpp actionstring_syntax_exception.hpp getter_setter.hpp illegal_action_exception.hpp Player.hpp Position.hpp OthelloAction.hpp OthelloState.hpp Tile.hpp

.PHONY: all build clean runtest purge

all: build runtest

build: $(OBJ)

runtest: PositionTest OthelloActionTest OthelloStateTest GameTest
	./PositionTest
	./OthelloActionTest
	./OthelloStateTest
	./GameTest

GameTest: GameTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

PositionTest: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

OthelloActionTest: OthelloActionTest.o $(OBJ)
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
