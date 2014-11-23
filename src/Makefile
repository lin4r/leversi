CC=g++
CFLAGS=-Wall -g -std=c++11 -O0
LDFLAGS=

MODEL=Position.o OthelloState.o OthelloAction.o Game.o
MODELTEST=PositionTest.o OthelloStateTest.o OthelloActionTest.o GameTest.o

GUI=Callback.o Board.o GUI.o

OOTEST=ObserverObservableTest.o

TEST=PositionTest OthelloStateTest OthelloActionTest GameTest ObserverObservableTest

AI=BestMoveFinder.o

TARGET=othello

.PHONY: all build clean test purge

all: $(TARGET) $(MODEL) $(GUI) test

test: $(TEST)
	./PositionTest
	./OthelloStateTest
	./OthelloActionTest
	./GameTest
	./ObserverObservableTest


# Compile Target
main.o: main.cpp GUI.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<

$(TARGET): main.o $(MODELEX) $(MODEL) $(GUI) $(AI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

# Compile model parts.
Position.o: Position.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

OthelloState.o: OthelloState.cpp OthelloState.hpp Tile.hpp Player.hpp getter_setter.hpp Position.hpp
	$(CC) $(CFLAGS) -c $<

OthelloAction.o: OthelloAction.cpp OthelloAction.hpp getter_setter.hpp Position.hpp OthelloState.hpp illegal_action_exception.hpp actionstring_syntax_exception.hpp game_over_exception.hpp
	$(CC) $(CFLAGS) -c $<

Game.o: Game.cpp Game.hpp OthelloState.hpp OthelloAction.hpp Observable.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<


# Tests for model parts.
PositionTest.o: PositionTest.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

PositionTest: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


OthelloStateTest.o: OthelloStateTest.cpp
	$(CC) $(CFLAGS) -c $<

OthelloStateTest: OthelloStateTest.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

OthelloActionTest.o: OthelloActionTest.cpp illegal_action_exception.hpp game_over_exception.hpp actionstring_syntax_exception.hpp
	$(CC) $(CFLAGS) -c $<

OthelloActionTest: OthelloActionTest.o OthelloAction.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

GameTest.o: GameTest.cpp Game.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<

GameTest: GameTest.o Game.o OthelloAction.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


# Compile gui parts.
Callback.o: Callback.cpp Callback.hpp Game.hpp OthelloController.hpp illegal_action_exception.hpp OthelloState.hpp Observer.hpp BestMoveFinder.hpp
	$(CC) $(CFLAGS) -c $<

Board.o: Board.cpp Board.hpp OthelloView.hpp OthelloController.hpp Callback.hpp Tile.hpp Observer.hpp OthelloState.hpp Player.hpp Position.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<

GUI.o: GUI.cpp GUI.hpp Board.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<


# Observer Observable tests.
ObserverObservableTest.o: ObserverObservableTest.cpp Observer.hpp Observable.hpp
	$(CC) $(CFLAGS) -c $<


# Compile AI.
BestMoveFinder.o: BestMoveFinder.cpp BestMoveFinder.hpp Game.hpp OthelloAction.hpp
	$(CC) $(CFLAGS) -c $<

ObserverObservableTest: ObserverObservableTest.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o

purge: clean
	rm -f *~
