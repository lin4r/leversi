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
 * Implements ReversiAction.hpp
 *
 * Linus Narva.
 */

#include "ReversiAction.hpp"
#include "illegal_action_exception.hpp"
#include "actionstring_syntax_exception.hpp"

//#include <regex>
#include <cctype> //FIXME Not needed with regex.
#include <functional>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

namespace reversi {

ReversiAction ReversiAction::pass() noexcept
{
	return ReversiAction(Position(-1,-1),true);
}

/* FIXME Use regular expressions. However it turns out these don't exist until
 *gcc 4.9 :(
 */
ReversiAction ReversiAction::parse(string actionstring)
{
//	using std::regex;
//	using std::regex_match;
//
//	const regex passEx("pass");
//	const regex putPieceEx(R"([[:digit:]])"); //FIXME
//
//	if (regex_match(actionstring, passEx)) {
//		ispass = true;
//	} else if (regex_match(actionstring, putPieceEx)) {
//		//FIXME
//		row = 3;
//		column = 4;
//	} else {
//		throw actionstring_syntax_exception(actionstring);
//	}

	using std::isdigit;
	using std::stoi;

	ReversiAction action(Position(-1,-1));

	if (actionstring.compare("pass") == 0) {

		action = pass();

	} else if ((actionstring.size() > 4) && isdigit(actionstring.at(1))
			&& isdigit(actionstring.at(3))) {

		const auto row = stoi(actionstring.substr(1,1));
		const auto column = stoi(actionstring.substr(3,1));

		action = ReversiAction(Position(row, column));

	} else {
		throw actionstring_syntax_exception(actionstring);
	}

	return action;
}

string ReversiAction::actionString() const noexcept
{
	using std::to_string;

	string actionStr;

	if (ispass) {
		actionStr = "pass";
	} else {
		actionStr = "(" + to_string(position.row) + ","
			+ to_string(position.column) + ")";
	}

	return actionStr;
}

vector<Position> ReversiAction::searchFlips(const ReversiState& state)
		const noexcept
{
	using std::mem_fn;

	const auto brickColour = playerBrickColour(state.whosTurn());
	vector<Position> flips;

	/* Obviusly there are no flips if the action is a pass, outside the grid
	 * or the tile is non-empty.
	 */
	if (ispass
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

vector<Position> ReversiAction::execute(ReversiState& state) const
{
	if (state.isGameOver()) {
		throw illegal_action_exception("The game is over.");
	}

	vector<Position> flips;

	auto pieceColour = playerBrickColour(state.whosTurn());

	/* Pass is only allowed if it is the only option.
	 */
	if (ispass) {

		if (existsLegalPlacement(state)) {
			throw illegal_action_exception(
				"Can't pass because thera are placements avalible.");
		}

	} else {

		flips = searchFlips(state);

		/* At least one brick must flip for the move to be legal. */
		if (flips.size() == 0) {
			throw illegal_action_exception(
				"This move is illegal, because no bricks are flipped.");
		}

		/* Lastly commit the effects of the move. */
		state.setTile(getPosition(), pieceColour);

		for (auto flipPosition : flips) {
			state.flipBrick(flipPosition);
		}
	}

	updateGameOverStaus(state);
	state.changeTurn();

	return flips;
}

void ReversiAction::updateGameOverStaus(ReversiState& state)
		const noexcept
{
	const auto previousWasPass = state.wasActionPass();
	const auto alreadyGameOver = state.isGameOver();

	/* Two (legal) passes in a row -> Game Over!
	 */
	state.setGameOver((ispass && previousWasPass) || alreadyGameOver);
	state.setActionWasPass(ispass);
}

bool ReversiAction::existsLegalPlacement(const ReversiState& state) noexcept
{
	bool foundLegalPlacement{false};

	for (auto row = 0; (! foundLegalPlacement)
			&& (row < state.numBoardRows()); row++ )
	{
		for (auto col = 0; (! foundLegalPlacement)
				&& (col < state.numBoardColumns()); col++)
		{
			ReversiAction placement(Position(row,col));
			auto flips = placement.searchFlips(state);
			foundLegalPlacement = foundLegalPlacement || (flips.size() != 0);
		}
	}

	return foundLegalPlacement;
}

vector<Outcome> ReversiAction::findLegalPlacements(const ReversiState& state)
		noexcept
{
	vector<Outcome> placements;

	for (auto row = 0; row < state.numBoardRows(); row++ ) {
		for (auto col = 0; col < state.numBoardColumns(); col++) {

			ReversiAction placement(Position(row,col));
			auto flips = placement.searchFlips(state);

			if (flips.size() > 0) {

				const Outcome outcome = {placement, flips};
				placements.push_back(outcome);
			}
		}
	}

	return placements;
}

bool operator==(const ReversiAction& a1, const ReversiAction& a2) noexcept
{
	return (a1.getPosition() == a2.getPosition())
		&& (a1.isPass() == a2.isPass());
}

bool operator<(const ReversiAction& a1, const ReversiAction& a2) noexcept
{
	if (a1.isPass() && (! a2.isPass())) {
		return true;
	} else if ((!a1.isPass()) && a2.isPass()) {
		return false;
	} else {
		return a1.getPosition() < a2.getPosition();
	}
}

std::ostream& operator<<(std::ostream& os, const ReversiAction& action)
{
	return os << "ReversiAction[" << action.actionString() << "]";
}

} //namespace reversi
