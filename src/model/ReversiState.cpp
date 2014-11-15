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
#include <functional>

using std::vector;

namespace reversi {

ReversiState::ReversiState() noexcept : ReversiState(8,8,Player::Black)
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

Tile ReversiState::playerColour(Player player) const noexcept
{
	switch (player) {
	case Player::Black: return Tile::Black;
	case Player::White:
	default: return Tile::White;
	}
}

vector<Position> ReversiState::getTurnings(ReversiAction action)
{
	using std::mem_fn;

	const auto positionToPlace = action.get_position();
	const auto brickColour = playerColour(turn);

	vector<Position> flips;

	auto directions =
		{ mem_fn(&Position::north), mem_fn(&Position::northEast)
		, mem_fn(&Position::east),  mem_fn(&Position::southEast)
		, mem_fn(&Position::south), mem_fn(&Position::southWest)
		, mem_fn(&Position::west),  mem_fn(&Position::northWest) };

	/* Search in all directions from the position */
	for (auto& step : directions) {

		/* Stores possible turnings in the direction. They are discarded if no
		 * brick of the same colour ocurrs. */
		vector<Position> possibleFlips;

		/* Will be set true if the flips where 'terminated' by a brick of same
		 * color as the player. */
		bool directionHasFlips{false};

		/* Search for turnings in the direction, inside the grid and an Empty
		 * Tile has not ocurred. */
		for (auto p = step(positionToPlace)
				; isInsideGrid(p) && (inspectTile(p) != Tile::Empty)
					&& (!directionHasFlips)
				; p = step(p))
		{
			auto tile = inspectTile(p);

			/* If it passes over brick of opposite color, it is a possible
			 * turns. Tile is not Tile::Empty, because of the for constraint;
			 */
			if (brickColour != tile) {

				possibleFlips.push_back(p);

			/* If it passe over a tile of the same color and has caused flips
			 * the search is done.
			 */
			} else if (possibleFlips.size() > 0) {
				directionHasFlips = true;
			}
		}

		/* If flips where found, commit them. */
		if (directionHasFlips) {
			flips.insert(flips.end(), possibleFlips.begin()
				, possibleFlips.end());
		}
	}

	return flips;
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

void ReversiState::turnBrick(Position position)
{
	switch (inspectTile(position)) {
	case Tile::Black: setTile(position, Tile::White); break;
	case Tile::White: setTile(position, Tile::Black); break;
	default: ; /* Do nothing if empty */
	}
}

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);
