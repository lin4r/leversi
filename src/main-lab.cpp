/* Main method for running the program as specified in the lab description.
 *
 * Linus Narva.
 */
#include "Position.hpp"
#include "OthelloState.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "OthelloAction.hpp"
#include "Game.hpp"
#include "BestMoveFinder.hpp"

#include <string>
#include <iostream>
#include <exception>

using namespace othello;
using namespace std;

class parse_exception : public exception
{
public:

	virtual const char* what() const noexcept override
		{ return "Invalid character in state string."; }
};

static void usage(const char* executableName) noexcept;
static OthelloState parseStateString(string stateString);
static OthelloAction chooseAction(OthelloState state);

/* Changes the coordinate system from [0 7] (as in my code) to [1, 8]
 * (as in the lab test code).
 */
static OthelloAction adaptCoordinateSystem(OthelloAction action);

int main(int argc, char* args[])
{
	if (argc < 2) {
		cerr << "To few arguments!" << endl;
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

	//cerr << "DEBUG: The parsed state:" << endl << state << endl;

	auto action = adaptCoordinateSystem(chooseAction(state));

	cout << action.actionString() << endl;

	return 0;
}

static OthelloState parseStateString(string stateString)
{
	OthelloState state;

	switch (stateString.at(0)) {
	case 'B': state.setTurn(Player::Black); break;
	case 'W': state.setTurn(Player::White); break;
	default: throw parse_exception();
	}

//	cerr << "DEBUG: is colour" << state.whosTurn() << endl;

	const auto rows = state.getBoardRows();
	const auto cols = state.getBoardColumns();

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

static OthelloAction chooseAction(OthelloState state)
{
	Game game(state);
	BestMoveFinder actionFinder(game);
	actionFinder.setMaxDepth(5);

	return actionFinder.getBestMove();
}

static OthelloAction adaptCoordinateSystem(OthelloAction action)
{
	auto oldCoordinates = action.getPosition();
	Position newCoordinates(oldCoordinates.row+1, oldCoordinates.column+1);
	return OthelloAction(newCoordinates, action.isPass());
}

void usage(const char* executableName) noexcept
{
	cerr << executableName << " state time" << endl
		<< "State is the chould be 65 chars. The first is the player turn "
		<< "(B or W)." << endl
		<< "The remaining chars are the tiles in row major order. E - empty"
		<< ", O - White, X - Black." << endl
		<< "time is the time limit" << endl;
}
