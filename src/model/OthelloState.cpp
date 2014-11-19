/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of othello-assignment.
 * 
 * othello-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Implements OthelloState.hpp
 *
 * Linus Narva.
 */
#include "OthelloState.hpp"

#include <vector>

using std::vector;

namespace othello {

OthelloState::OthelloState() noexcept : OthelloState(8,8,Player::Black)
{
}

OthelloState::OthelloState(int boardRows, int boardColumns, Player starter)
		noexcept
		: playersTurn{starter}, boardRows{boardRows}
		, boardColumns{boardColumns}
		, grid{vector<vector<Tile>>(boardRows,vector<Tile>(boardColumns
			,Tile::Empty))}
{
}

OthelloState OthelloState::initialState() noexcept
{
	OthelloState initial;

	initial.setTile(Position(3,3), Tile::White);
	initial.setTile(Position(3,4), Tile::Black);
	initial.setTile(Position(4,4), Tile::White);
	initial.setTile(Position(4,3), Tile::Black);

	return initial;
}

bool OthelloState::isInsideGrid(Position position) const noexcept
{
	return (0 <= position.row) && (position.row < boardRows)
		&& (0 <= position.column) && (position.column < boardColumns);
}

Player OthelloState::whosTurn() const noexcept
{
	return playersTurn;
}

Tile OthelloState::inspectTile(Position position) const
{
	return grid.at(position.row).at(position.column);
}

void OthelloState::setTile(Position position, Tile value)
{
	grid.at(position.row).at(position.column) = value;
}

void OthelloState::flipBrick(Position position)
{
	switch (inspectTile(position)) {
	case Tile::Black: setTile(position, Tile::White); break;
	case Tile::White: setTile(position, Tile::Black); break;
	default: ; /* Do nothing if empty */
	}
}

void OthelloState::updateGameStatus(bool actionWasPass) noexcept
{
	/* If the previous player passed and pass is legal, then the game is
	 * over.
	 */
	gameIsOver = (previousActionWasPass && actionWasPass) || gameIsOver;
	previousActionWasPass = actionWasPass;
}

bool OthelloState::gameOver() const noexcept
{
	return gameIsOver;
}

void OthelloState::changeTurn() noexcept
{
	switch(playersTurn) {
	case Player::Black: playersTurn = Player::White; break;
	case Player::White:
	default: playersTurn = Player::Black;
	}
}

bool operator==(const OthelloState& state1, const OthelloState& state2)
{
	const auto rows = state1.get_boardRows();
	const auto columns = state1.get_boardColumns();
	/* Check the 'simple components before the board.' */
	if ( (rows != state2.get_boardRows())
			|| (columns != state2.get_boardColumns())
			|| (state1.whosTurn() != state2.whosTurn())
			|| (state1.gameOver() != state2.gameOver()) )
	{
		return false;
	}

	bool boardEqual{true};

	for (auto row = 0; boardEqual && (row < rows); row++) {
		for (auto col = 0; boardEqual && (col < columns); col++) {

			const Position pos(row,col);
			boardEqual = boardEqual
				&& (state1.inspectTile(pos) == state2.inspectTile(pos));
		}
	}

	return boardEqual;
}

bool operator!=(const OthelloState& state1, const OthelloState& state2)
{
	return !(state1 == state2);
}

} //namespace othello

//std::ostream& operator<<(std::ostream& os, othello::OthelloState action);
