CC=g++
CFLAGS=-Wall -g -std=c++11 -O0
LDFLAGS=

MODEL=Position.o OthelloState.o OthelloAction.o Game.o SimpleEvaluator.o
MODELTEST=PositionTest.o OthelloStateTest.o OthelloActionTest.o GameTest.o

GUI=Callback.o Board.o GUI.o

OOTEST=ObserverObservableTest.o

TEST=Position.test OthelloState.test OthelloAction.test Game.test ObserverObservable.test SimpleEvaluator.test Cloneable.test

AI=MaximinSearcher.o TimeboxedMaximinSearcher.o

TARGET=lothello

LAB=lothello-bot

.PHONY: all build clean test purge

all: $(TARGET) $(MODEL) $(GUI) $(LAB) test 

test: $(TEST)
	./Position.test
	./OthelloState.test
	./OthelloAction.test
	./Game.test
	./ObserverObservable.test
	./SimpleEvaluator.test
	./Cloneable.test

#Compile lab code.
$(LAB): main-bot.o $(MODELEX) $(MODEL) $(AI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main-bot.o: main-bot.cpp OthelloState.hpp Position.hpp Player.hpp Tile.hpp OthelloAction.hpp Game.hpp MaximinSearcher.hpp
	$(CC) $(CFLAGS) -c $<

# Compile Target
main-gui.o: main-gui.cpp GUI.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<

$(TARGET): main-gui.o $(MODELEX) $(MODEL) $(GUI) $(AI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

# Compile model parts.
Position.o: Position.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

OthelloState.o: OthelloState.cpp OthelloState.hpp Tile.hpp Player.hpp Position.hpp
	$(CC) $(CFLAGS) -c $<

OthelloAction.o: OthelloAction.cpp OthelloAction.hpp Position.hpp OthelloState.hpp illegal_action_exception.hpp actionstring_syntax_exception.hpp game_over_exception.hpp
	$(CC) $(CFLAGS) -c $<

Game.o: Game.cpp Game.hpp OthelloState.hpp OthelloAction.hpp Observable.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<

SimpleEvaluator.o: SimpleEvaluator.cpp SimpleEvaluator.hpp Evaluator.hpp OthelloAction.hpp OthelloState.hpp Cloneable.hpp
	$(CC) $(CFLAGS) -c $<


# Tests for model parts.
PositionTest.o: PositionTest.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

Position.test: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

OthelloStateTest.o: OthelloStateTest.cpp
	$(CC) $(CFLAGS) -c $<

OthelloState.test: OthelloStateTest.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

OthelloActionTest.o: OthelloActionTest.cpp illegal_action_exception.hpp game_over_exception.hpp actionstring_syntax_exception.hpp
	$(CC) $(CFLAGS) -c $<

OthelloAction.test: OthelloActionTest.o OthelloAction.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

GameTest.o: GameTest.cpp Game.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<

Game.test: GameTest.o Game.o OthelloAction.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

SimpleEvaluatorTest.o: SimpleEvaluatorTest.cpp SimpleEvaluator.hpp Evaluator.hpp OthelloAction.hpp OthelloState.hpp Position.hpp
	$(CC) $(CFLAGS) -c $<

SimpleEvaluator.test: SimpleEvaluatorTest.o SimpleEvaluator.o OthelloAction.o OthelloState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


# Compile gui parts.
Callback.o: Callback.cpp Callback.hpp Game.hpp OthelloController.hpp illegal_action_exception.hpp OthelloState.hpp Observer.hpp MaximinSearcher.hpp TimeboxedMaximinSearcher.hpp
	$(CC) $(CFLAGS) -c $<

Board.o: Board.cpp Board.hpp OthelloView.hpp OthelloController.hpp Callback.hpp Tile.hpp Observer.hpp OthelloState.hpp Player.hpp Position.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<

GUI.o: GUI.cpp GUI.hpp Board.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<


# Observer Observable tests.
ObserverObservableTest.o: ObserverObservableTest.cpp Observer.hpp Observable.hpp
	$(CC) $(CFLAGS) -c $<

ObserverObservable.test: ObserverObservableTest.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


# Cloneable test.
CloneableTest.o: CloneableTest.cpp Cloneable.hpp
	$(CC) $(CFLAGS) -c $<

Cloneable.test: CloneableTest.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile AI.
MaximinSearcher.o: MaximinSearcher.cpp MaximinSearcher.hpp Game.hpp OthelloAction.hpp Evaluator.hpp SimpleEvaluator.hpp Cloneable.hpp
	$(CC) $(CFLAGS) -c $<

TimeboxedMaximinSearcher.o: TimeboxedMaximinSearcher.cpp TimeboxedMaximinSearcher.hpp MaximinSearcher.hpp OthelloAction.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
	rm -f *.test
