/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of reversi-assignment.
 * 
 * reversi-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Implements ReversiState.hpp
 *
 * Linus Narva.
 */
#include "ReversiState.hpp"

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;
using std::ostream;
using std::endl;

namespace reversi {

ReversiState::ReversiState() : ReversiState(8,8,Player::Black)
{
}

ReversiState::ReversiState(int boardRows, int boardColumns, Player starter)
		: playersTurn{starter}, boardRows{boardRows}
		, boardColumns{boardColumns}
		, board{vector<Tile>(boardRows*boardColumns,Tile::Empty)}
{
}

ReversiState ReversiState::initialState() noexcept
{
	ReversiState initial;

	initial.setTile(Position(3,3), Tile::White);
	initial.setTile(Position(3,4), Tile::Black);
	initial.setTile(Position(4,4), Tile::White);
	initial.setTile(Position(4,3), Tile::Black);

	return initial;
}

#define CHECK_RANGE(position) \
	if (! isInsideGrid(position)) { \
		stringstream message; \
		message << "The position " << position << " is outside the board."; \
		throw std::out_of_range(message.str()); \
	}

Tile ReversiState::inspectTile(Position position) const
{
	CHECK_RANGE(position);

	return board.at(position2GridIndex(position));
}

void ReversiState::setTile(Position position, Tile value)
{
	CHECK_RANGE(position)

	board.at(position2GridIndex(position)) = value;
}

#undef CHECK_RANGE

bool ReversiState::isInsideGrid(Position position) const noexcept
{
	return (0 <= position.row) && (position.row < boardRows)
		&& (0 <= position.column) && (position.column < boardColumns);
}

void ReversiState::flipBrick(Position position)
{
	switch (inspectTile(position)) {
	case Tile::Black: setTile(position, Tile::White); break;
	case Tile::White: setTile(position, Tile::Black); break;
	default: ; /* Do nothing if empty */
	}
}

string ReversiState::boardString() const noexcept
{
	stringstream ss;

	const auto hline = [&]() {
		for (auto col = 0; col < boardColumns+2; col++) {
			ss << "-";
		}
	};

	hline();
	ss << " ..." << endl;
	for (auto row = 0; row < boardRows; row++) {
		ss << "|";
		for (auto col = 0; col < boardColumns; col++) {

			const Position pos(row,col);
			switch (inspectTile(pos)) {
			case Tile::White: ss << "O"; break;
			case Tile::Black: ss << "X"; break;
			default: ss << " ";
			}
		}
		ss << "| ..." << endl;
	}

	hline();

	return ss.str();
}

string ReversiState::toString() const noexcept
{
	#define PVAR(var) #var << "{" << var << "}"

	stringstream ss;

	ss << "reversi::ReversiState[" << PVAR(gameIsOver) << ", "
		<< PVAR(actionWasPass) << ", " << PVAR(playersTurn) << ", "
		<< PVAR(boardRows) << ", " << PVAR(boardColumns) << ", board{ ..."
		<< endl << boardString() << "}]";

	#undef PVAR

	return ss.str();
}

bool operator==(const ReversiState& state1, const ReversiState& state2)
{
	const auto rows = state1.numBoardRows();
	const auto columns = state1.numBoardColumns();

	/* Check the 'simple components before the board.' */
	if ( (rows != state2.numBoardRows())
			|| (columns != state2.numBoardColumns())
			|| (state1.whosTurn() != state2.whosTurn())
			|| (state1.wasActionPass() != state2.wasActionPass())
			|| (state1.isGameOver() != state2.isGameOver()) )
	{
		return false;
	}

	bool boardEqual{true};

	auto it1 = state1.constBoardIterator();
	auto it2 = state2.constBoardIterator();

	for (auto p1 = it1.begin(), p2 = it2.begin()
			; boardEqual && ((p1 != it1.end()) || (p2 != it2.end()))
			; p1++, p2++)
	{
		boardEqual = *p1 == *p2;
	}

	return boardEqual;
}

} //namespace reversi
