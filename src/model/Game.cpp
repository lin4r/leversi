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
 * Implements Game.hpp
 *
 * Linus Narva.
 */
#include "Game.hpp"

#include <vector>

using std::pair;

namespace othello {

void Game::commitAction(OthelloAction action)
{
	auto effect = action.execute(state);

	pair<OthelloAction,std::vector<Position>> event(action, effect);
	history.push_back(event);
}

void Game::undoLastAction() noexcept
{
	const auto event = history.back();
	history.pop_back();

	const auto action = event.first;
	const auto effect = event.second;

	/* Remove the placed tile */
	state.setTile(action.get_position(), Tile::Empty);

	/* Flip back all bricks that where flipped. */
	for (auto flippedPos : effect) {
		state.flipBrick(flippedPos);
	}
}

int Game::numTurns() const noexcept
{
	return history.size();
}

const OthelloState& Game::refState() const noexcept
{
	return state;
}

} //namespace othello
