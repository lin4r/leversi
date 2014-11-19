CC=g++
CFLAGS=-Wall -g -std=c++11 `pkg-config --cflags gtkmm-3.0` -I../model/
LDFLAGS=`pkg-config --libs gtkmm-3.0`

TARGET=othello
OBJ=main.o GUI.o Board.o
DEPS=GUI.hpp Board.hpp OthelloView.hpp OthelloController.hpp ../model/Tile.hpp

.PHONY: all clean purge

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
