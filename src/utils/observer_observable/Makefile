CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=

OBJ=
DEPS=Observable.hpp Observer.hpp

.PHONY: all build clean runtest purge

all: build runtest

build: $(OBJ)

runtest: test
	./test

test: ObserverObservableTest.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
