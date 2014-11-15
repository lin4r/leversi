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
 * Implements ReversiState.hpp
 *
 * Linus Narva.
 */
#include "ReversiState.hpp"

#include <vector>
#include <functional>

using std::vector;

namespace othello {

ReversiState::ReversiState() noexcept : ReversiState(8,8,Player::Black)
{
}

ReversiState::ReversiState(int boardRows, int boardColumns, Player starter)
		noexcept
		: previousAction(Position(-1,-1), false), turn{starter}
		, boardRows{boardRows}, boardColumns{boardColumns}
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

vector<Position> ReversiState::searchFlips(ReversiAction action) const
{
	using std::mem_fn;

	const auto positionToPlace = action.get_position();
	const auto brickColour = playerColour(turn);
	vector<Position> flips;

	/* Obviusly there are no flips if the action is a pass, outside the grid
	 * or the tile is non-empty.
	 */
	if (action.get_pass()
			|| (! isInsideGrid(positionToPlace))
			|| inspectTile(positionToPlace) != Tile::Empty)
	{
		return flips;
	}

	static const auto directions =
		{ mem_fn(&Position::north), mem_fn(&Position::northEast)
		, mem_fn(&Position::east),  mem_fn(&Position::southEast)
		, mem_fn(&Position::south), mem_fn(&Position::southWest)
		, mem_fn(&Position::west),  mem_fn(&Position::northWest) };

	/* Search in all directions from the position */
	for (auto& step : directions) {

		/* Stores possible turnings in the direction. They are discarded if no
		 * brick of the same colour ocurrs. */
		vector<Position> possibleFlips;

		/* Will be set true if a brick of the same colour was found along the
		 * direction.
		 */
		bool foundSameColour{false};

		/* Search for turnings in the direction, inside the grid and an Empty
		 * Tile has not ocurred. */
		for (auto p = step(positionToPlace)
				; isInsideGrid(p) && (inspectTile(p) != Tile::Empty)
					&& (! foundSameColour)
				; p = step(p))
		{
			auto tile = inspectTile(p);

			/* If a terminating brick of the same colour was found along the
			 * direction, then the search is done. Otherwise the tile had the
			 * oposite colour and can be flipped.
			 */
			if (brickColour == tile) {
				foundSameColour = true;
			} else {
				possibleFlips.push_back(p);
			}
		}

		/* If the direction of search was terminated by a brick of the same
		 * colour, then commit the flipped positions (possibly zero).
		 */
		if (foundSameColour) {
			flips.insert(flips.end(), possibleFlips.begin()
				, possibleFlips.end());
		}
	}

	return flips;
}

void ReversiState::performAction(ReversiAction action)
{
	Tile pieceColour;

	switch (turn) {
	case Player::White:
		pieceColour = Tile::White;
		break;
	case Player::Black:
	default:
		pieceColour = Tile::Black;
	}

	/* Pass iss only allowed if it is the only option.
	 */
	if (action.get_pass()) {

		if (existsNonpassAction()) {
			throw illegal_move_exception(action);
		}

		/* If the previous player passed and pass is legal, then the game is
		 * over.
		 */
		gameIsOver = previousAction.get_pass();
	} else {

		auto flips = searchFlips(action);

		/* Just take advantage of the simple rule that a non-pass action must
		 * cause flips.
		 */
		if (flips.size() == 0) {
			throw illegal_move_exception(action);
		}

		/* Lastly commit the effects of the move. */
		setTile(action.get_position(), pieceColour);

		for (auto flipPosition : flips) {
			turnBrick(flipPosition);
		}
	}

	previousAction = action;
	changeTurn();
}

bool ReversiState::isInsideGrid(Position position) const noexcept
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

bool ReversiState::existsNonpassAction() const noexcept
{
	bool foundLegalMove{false}; //XXX Bad Name

	for (auto row = 0; (! foundLegalMove) && (row < boardRows); row++ ) {
		for (auto col = 0; (! foundLegalMove) && (col < boardColumns); col++) {

			auto flips = searchFlips(ReversiAction(Position(row,col)));
			foundLegalMove = foundLegalMove || (flips.size() != 0);
		}
	}

	return foundLegalMove;
}

bool ReversiState::gameOver() const noexcept
{
	return gameIsOver;
}

void ReversiState::changeTurn() noexcept
{
	switch(turn) {
	case Player::Black: turn = Player::White; break;
	case Player::White:
	default: turn = Player::Black;
	}
}

} //namespace othello

//std::ostream& operator<<(std::ostream& os, othello::ReversiState action);
