CC=g++
CFLAGS=-Wall -std=c++11 -O4 -DNDEBUG
LDFLAGS=

MODEL=Position.o ReversiState.o ReversiAction.o Game.o SimpleEvaluator.o WashingtonEvaluator.o

GUI=Callback.o Board.o GUI.o

OOTEST=ObserverObservableTest.o

TEST=Position.test ReversiState.test ReversiAction.test Game.test ObserverObservable.test SimpleEvaluator.test Cloneable.test WashingtonEvaluator.test

AI=MaximinSearcher.o TimeboxedMaximinSearcher.o

TARGET=leversi

LAB=leversi-bot

.PHONY: all build clean test test-build clean purge

all: build $(MODEL) $(GUI) test 

test: test-build
	./Position.test
	./ReversiState.test
	./ReversiAction.test
	./Game.test
	./ObserverObservable.test
	./SimpleEvaluator.test
	./Cloneable.test
	./WashingtonEvaluator.test

test-build: $(TEST)

build: $(TARGET) $(LAB)

#Compile lab code.
$(LAB): main-bot.o $(MODELEX) $(MODEL) $(AI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main-bot.o: main-bot.cpp ReversiState.hpp Position.hpp Player.hpp Tile.hpp ReversiAction.hpp Game.hpp MaximinSearcher.hpp TimeboxedMaximinSearcher.hpp WashingtonEvaluator.hpp
	$(CC) $(CFLAGS) -c $<

# Compile Target
main-gui.o: main-gui.cpp GUI.hpp
	$(CC) $(CFLAGS) `pkg-config --cflags gtkmm-3.0` -c $<

$(TARGET): main-gui.o $(MODELEX) $(MODEL) $(GUI) $(AI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

# Compile model parts.
Position.o: Position.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

ReversiState.o: ReversiState.cpp ReversiState.hpp Tile.hpp Player.hpp Position.hpp
	$(CC) $(CFLAGS) -c $<

ReversiAction.o: ReversiAction.cpp ReversiAction.hpp Position.hpp ReversiState.hpp illegal_action_exception.hpp actionstring_syntax_exception.hpp
	$(CC) $(CFLAGS) -c $<

Game.o: Game.cpp Game.hpp ReversiState.hpp ReversiAction.hpp Observable.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<

SimpleEvaluator.o: SimpleEvaluator.cpp SimpleEvaluator.hpp Evaluator.hpp ReversiAction.hpp ReversiState.hpp Cloneable.hpp
	$(CC) $(CFLAGS) -c $<


# Tests for model parts.
PositionTest.o: PositionTest.cpp Position.hpp
	$(CC) $(CFLAGS) -c $<

Position.test: PositionTest.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReversiStateTest.o: ReversiStateTest.cpp
	$(CC) $(CFLAGS) -c $<

ReversiState.test: ReversiStateTest.o ReversiState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ReversiActionTest.o: ReversiActionTest.cpp illegal_action_exception.hpp actionstring_syntax_exception.hpp
	$(CC) $(CFLAGS) -c $<

ReversiAction.test: ReversiActionTest.o ReversiAction.o ReversiState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

GameTest.o: GameTest.cpp Game.hpp undo_initial_state_exception.hpp
	$(CC) $(CFLAGS) -c $<

Game.test: GameTest.o Game.o ReversiAction.o ReversiState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

SimpleEvaluatorTest.o: SimpleEvaluatorTest.cpp SimpleEvaluator.hpp Evaluator.hpp ReversiAction.hpp ReversiState.hpp Position.hpp Player.hpp Tile.hpp
	$(CC) $(CFLAGS) -c $<

SimpleEvaluator.test: SimpleEvaluatorTest.o SimpleEvaluator.o ReversiAction.o ReversiState.o Position.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

WashingtonEvaluator.o: WashingtonEvaluator.cpp WashingtonEvaluator.hpp SimpleEvaluator.hpp ReversiAction.hpp ReversiState.hpp Position.hpp Player.hpp Tile.hpp
	$(CC) $(CFLAGS) -c $<

WashingtonEvaluatorTest.o: WashingtonEvaluatorTest.cpp WashingtonEvaluator.hpp Evaluator.hpp ReversiAction.hpp ReversiState.hpp Position.hpp Player.hpp Tile.hpp
	$(CC) $(CFLAGS) -c $<

WashingtonEvaluator.test: WashingtonEvaluatorTest.o WashingtonEvaluator.o ReversiAction.o ReversiState.o Position.o SimpleEvaluator.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


# Compile gui parts.
Callback.o: Callback.cpp Callback.hpp Game.hpp ReversiController.hpp illegal_action_exception.hpp ReversiState.hpp Observer.hpp MaximinSearcher.hpp TimeboxedMaximinSearcher.hpp
	$(CC) $(CFLAGS) -c $<

Board.o: Board.cpp Board.hpp ReversiView.hpp ReversiController.hpp Callback.hpp Tile.hpp Observer.hpp ReversiState.hpp Player.hpp Position.hpp
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
MaximinSearcher.o: MaximinSearcher.cpp MaximinSearcher.hpp Game.hpp ReversiAction.hpp Evaluator.hpp SimpleEvaluator.hpp Cloneable.hpp
	$(CC) $(CFLAGS) -c $<

TimeboxedMaximinSearcher.o: TimeboxedMaximinSearcher.cpp TimeboxedMaximinSearcher.hpp MaximinSearcher.hpp ReversiAction.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

purge: clean
	rm -f *~
	rm -f *.test
