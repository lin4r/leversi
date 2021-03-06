/**
 *  Main method for running the program as specified in the lab description.
 *
 * Linus Narva.
 */
#include "Position.hpp"
#include "ReversiState.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "ReversiAction.hpp"
#include "Game.hpp"
#include "MaximinSearcher.hpp"
#include "TimeboxedMaximinSearcher.hpp"
#include "WashingtonEvaluator.hpp"

#include <string>
#include <iostream>
#include <exception>

using namespace reversi;
using namespace std;

/**
 * Exception thhrown if the state string is invalid.
 */
class parse_exception : public exception
{
public:

	virtual const char* what() const noexcept override
		{ return "Invalid character in state string."; }
};

/**
 * Prints usage information.
 * param:	Name of the executable.
 */
static void usage(const char* executableName) noexcept;

/**
 * Parses the state string.
 * param:	String containing the reversi state.
 * return:	The parsed reversi state.
 */
static ReversiState parseStateString(string stateString);

/**
 * Uses timaboxed maximin search to find an action.
 * params:
 *	state - The current state of the game.
 *	timeout_ms - The time it has to find choose the move in milliseconds.
 */
static ReversiAction chooseAction(ReversiState state, int timeout_ms);

/* Changes the coordinate system from [0 7] (as in my code) to [1, 8]
 * (as in the lab test code).
 */
static ReversiAction adaptCoordinateSystem(ReversiAction action);

int main(int argc, char* args[])
{
	if (argc < 3) {
		if (argc != 1) {
			cerr << "To few arguments!" << endl;
		}
		usage(args[0]);
		return -1;
	}

	const string stateString(args[1]);

	if (stateString.size() != 65) {
		cerr << "The state string is not of the correct size!" << endl
			<< "Size is> " << stateString.size() << endl;
		usage(args[0]); 
		return -1;
	}

	auto state = parseStateString(stateString);

	const auto timeout_s = atoi(args[2]);

	auto action = adaptCoordinateSystem(chooseAction(state, 1000*timeout_s));

	cout << action.actionString() << endl;

	return 0;
}

static ReversiState parseStateString(string stateString)
{
	ReversiState state;

	/* The first char indicates whos turn it is. */
	Player turn;
	switch (stateString.at(0)) {
	case 'B': turn = Player::Black; break;
	case 'W': turn = Player::White; break;
	default: throw parse_exception();
	}

	state.setTurn(turn);

	const auto rows = state.numBoardRows();
	const auto cols = state.numBoardColumns();

	/* The chars remaining specifies the board in row major order. */
	for (auto col = 0; col < cols; col++) {
		for (auto row = 0; row < rows; row++) {
			/* Row major index of string plus one for the first char. */
			const auto index = col + cols*row + 1;

			Tile tile;
			switch (stateString.at(index)) {
			case 'E': tile = Tile::Empty; break;
			case 'O': tile = Tile::White; break;
			case 'X': tile = Tile::Black; break;
			default: throw parse_exception();
			}

			state.setTile(Position(row, col), tile);
		}
	}

	return state;
}

static ReversiAction chooseAction(ReversiState state, int timeout_ms)
{
	WashingtonEvaluator evaluator;
	Game game(state);
	MaximinSearcher actionFinder(game);
	actionFinder.setEvaluator(evaluator);
	TimeboxedMaximinSearcher timedFinder(5, timeout_ms, actionFinder);
	const auto action = timedFinder.maximinAction();
	

	/* Print analysis data to standard error. */
	const auto analysis = timedFinder.getAnalysis();
	const auto exectime = timedFinder.getLastRuntime_ms();
	const auto maxDepth = timedFinder.getMaxDepth();
	const auto player = timedFinder.getPlayer();

	cerr << "*** Analysis ***" << endl
		<<  "player:           " << player << endl
		<<  "nodes:            " << analysis.numNodes << endl
		<<  "branching factor: " << analysis.branchingFactor << endl
		<<  "predicted score:  " << analysis.predictedScore << endl
		<<  "Time used (s):    " << exectime << endl
		<<  "ReachedDepth:     " << analysis.reachedDepth << endl
		<<  "MaxDepth:         " << maxDepth << endl
		<<  "****************" << endl;

	return action;
}

static ReversiAction adaptCoordinateSystem(ReversiAction action)
{
	auto oldCoordinates = action.getPosition();
	Position newCoordinates(oldCoordinates.row+1, oldCoordinates.column+1);
	return ReversiAction(newCoordinates, action.isPass());
}

void usage(const char* executableName) noexcept
{
	cerr << executableName << " state time" << endl
		<< endl
		<< "State is the chould be 65 chars. The first is the player turn "
		<< "(B or W)." << endl
		<< endl
		<< "The remaining chars are the tiles in row major order. E - empty"
		<< endl
		<< ", O - White, X - Black." << endl
		<< "Time is the time limit" << endl
		<< endl
		<< "The output will be either a position of the form\"(r,c)\", where"
		<< endl
		<< "r is the row and c is the column of the placement (starting from"
		<< endl
		<< "index 1). If no move is available the string \"pass\" is returned."
		<< endl
		<< "The output is delimited by a newline at the end."
		<< endl;
}
