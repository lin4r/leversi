CC=g++
CFLAGS=-Wall -O0 -std=c++11 `pkg-config --cflags gtkmm-3.0`
LDFLAGS=`pkg-config --libs gtkmm-3.0`

TARGET=reversi
OBJ=main.o GUI.o
DEPS=GUI.hpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
