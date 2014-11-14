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

using std::vector;

namespace reversi {

ReversiState::ReversiState() noexcept : ReversiState(8,8,Player::White)
{
}

ReversiState::ReversiState(int boardRows, int boardColumns, Player starter)
		noexcept
		: turn{starter}, boardRows{boardRows}, boardColumns{boardColumns}
		, grid{vector<vector<Tile>>(boardRows,vector<Tile>(boardColumns
			,Tile::Empty))}
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

void ReversiState::performAction(ReversiAction action)
{
	Player nextTurn;
	Tile pieceColour;

	switch (turn) {
	case Player::White:
		pieceColour = Tile::White;
		nextTurn = Player::Black;
		break;
	case Player::Black:
	default:
		pieceColour = Tile::Black;
		nextTurn = Player::White;
	}

	/* TODO Exception handling here. */

	if ((! action.get_pass()) && (! isInsideGrid(action.get_position()))) {
		throw illegal_move_exception(action);
	}

	/* Commit updates lastly to preserve strong exception guarantee. */
	if (! action.get_pass()) {
		setTile(action.get_position(), pieceColour);
	}

	turn = nextTurn;
}

bool ReversiState::isInsideGrid(Position position)
{
	return (0 <= position.row) && (position.row < boardRows)
		&& (0 <= position.column) && (position.column < boardColumns);
}

Player ReversiState::whosTurn() const noexcept
{
	return turn;
}

Tile ReversiState::inspectTile(Position position) const
{
	return grid.at(position.row).at(position.column);
}

void ReversiState::setTile(Position position, Tile value)
{
	grid.at(position.row).at(position.column) = value;
}

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);
