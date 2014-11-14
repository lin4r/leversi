CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=

TARGET=reversi
OBJ=actionstring_syntax_exception.o illegal_move_exception.o ReversiState.o ReversiAction.o
DEPS=actionstring_syntax_exception.hpp getter_setter.hpp illegal_move_exception.hpp ReversiAction.hpp ReversiAlgorithm.hpp ReversiPosition.hpp Tile.hpp Player.hpp

TEST=test

.PHONY: all clean runtest

all: $(TARGET) runtest

runtest: $(TEST)
	./$(TEST)

$(TEST): ReversiActionTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET): $(OBJ)
#	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
