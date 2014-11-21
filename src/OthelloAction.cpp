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
 * Implements OthelloAction.hpp
 *
 * Linus Narva.
 */

#include "OthelloAction.hpp"
#include "illegal_action_exception.hpp"
#include "actionstring_syntax_exception.hpp"

//#include <regex>
#include <cctype> //FIXME Not needed with regex.
#include <functional>
#include <vector>
#include <utility>

using std::vector;
using std::string;
using std::ostream;
using std::pair;

namespace othello {

OthelloAction::OthelloAction(Position position) noexcept
		: position(position), pass{false}
{
}

OthelloAction::OthelloAction(Position position, bool pass) noexcept
		: position(position), pass{pass}
{
}

OthelloAction OthelloAction::constructPass() noexcept
{
	return OthelloAction(Position(-1,-1),true);
}

bool OthelloAction::isPass() const noexcept
{
	return pass;
}

/* FIXME Use regular expressions. However it turns out these don't exist until
 *gcc 4.9 :(
 */
OthelloAction::OthelloAction(string action)
{
//	using std::regex;
//	using std::regex_match;
//
//	const regex passEx("pass");
//	const regex putPieceEx(R"([[:digit:]])"); //FIXME
//
//	if (regex_match(action, passEx)) {
//		pass = true;
//	} else if (regex_match(action, putPieceEx)) {
//		//FIXME
//		row = 3;
//		column = 4;
//	} else {
//		throw actionstring_syntax_exception(action);
//	}

	using std::isdigit;
	using std::stoi;

	if (action.compare("pass") == 0) {
		pass = true;
	} else if ((action.size() > 4) && isdigit(action.at(1))
			&& isdigit(action.at(3))) {
		position.row = stoi(action.substr(1,1));
		position.column = stoi(action.substr(3,1));
	} else {
		throw actionstring_syntax_exception(action);
	}
}

string OthelloAction::actionString() const noexcept
{
	using std::to_string;

	string actionStr;

	if (pass) {
		actionStr = "pass";
	} else {
		actionStr = "(" + to_string(position.row) + ","
			+ to_string(position.column) + ")";
	}

	return actionStr;
}

vector<Position> OthelloAction::searchFlips(const OthelloState& state) const
{
	using std::mem_fn;

	const auto brickColour = playerBrickColour(state.whosTurn());
	vector<Position> flips;

	/* Obviusly there are no flips if the action is a pass, outside the grid
	 * or the tile is non-empty.
	 */
	if (pass
			|| (! state.isInsideGrid(position))
			|| state.inspectTile(position) != Tile::Empty)
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
		for (auto p = step(position)
				; state.isInsideGrid(p) && (! foundSameColour)
				; p = step(p))
		{
			auto tile = state.inspectTile(p);

			/* If an empty tile ocurred, just terminate. Else, If a terminating
			 * brick of the same colour was found along the  direction, then
			 * the search is done. Otherwise the tile had the oposite colour
			 * and can be flipped.
			 */
			if (tile == Tile::Empty) {
				break;
			} else if (tile == brickColour) {
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

vector<Position> OthelloAction::execute(OthelloState& state)
{
	vector<Position> flips;

	auto pieceColour = playerBrickColour(state.whosTurn());

	/* Pass iss only allowed if it is the only option.
	 */
	if (pass) {

		if (existsLegalPlacement(state)) {
			throw illegal_action_exception(*this);
		}

	} else {

		flips = searchFlips(state);

		/* At least one brick must flip for the move to be legal. */
		if (flips.size() == 0) {
			throw illegal_action_exception(*this);
		}

		/* Lastly commit the effects of the move. */
		state.setTile(get_position(), pieceColour);

		for (auto flipPosition : flips) {
			state.flipBrick(flipPosition);
		}
	}

	state.updateGameStatus(pass);
	state.changeTurn();

	return flips;
}

bool OthelloAction::existsLegalPlacement(const OthelloState& state) noexcept
{
	bool foundLegalPlacement{false};

	for (auto row = 0; (! foundLegalPlacement)
			&& (row < state.get_boardRows()); row++ )
	{
		for (auto col = 0; (! foundLegalPlacement)
				&& (col < state.get_boardColumns()); col++)
		{
			OthelloAction placement(Position(row,col));
			auto flips = placement.searchFlips(state);
			foundLegalPlacement = foundLegalPlacement || (flips.size() != 0);
		}
	}

	return foundLegalPlacement;
}

vector<pair<OthelloAction,vector<Position>>>
		OthelloAction::findLegalPlacements(const OthelloState& state) noexcept
{
	vector<pair<OthelloAction,vector<Position>>> placements;

	for (auto row = 0; row < state.get_boardRows(); row++ ) {
		for (auto col = 0; col < state.get_boardColumns(); col++) {

			OthelloAction placement(Position(row,col));
			auto flips = placement.searchFlips(state);

			if (flips.size() > 0) {
				placements.push_back(pair<OthelloAction,vector<Position>>
					(placement,flips));
			}
		}
	}

	return placements;
}

bool operator==(const OthelloAction& a1, const OthelloAction& a2)
{
	return (a1.get_position() == a2.get_position())
		&& (a1.isPass() == a2.isPass());
}

bool operator<(const OthelloAction& a1, const OthelloAction& a2)
{
	if (a1.isPass() && (! a2.isPass())) {
		return true;
	} else if ((!a1.isPass()) && a2.isPass()) {
		return false;
	} else {
		return a1.get_position() < a2.get_position();
	}
}

std::ostream& operator<<(std::ostream& os, const OthelloAction& action)
{
	return os << "OthelloAction[" << action.actionString() << "]";
}

} //namespace othello
