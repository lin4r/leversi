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
#include "undo_initial_state_exception.hpp"

#include <vector>
#include <utility>

using std::vector;
using std::pair;

namespace othello {

flips_t Game::commitAction(OthelloAction action)
{
	auto flips = action.execute(state);
	history.push_back(pair<OthelloAction,flips_t>(action,flips));

	return flips;
}

void Game::undoLastAction()
{
	if (history.empty()) {

		throw undo_initial_state_exception();

	} else {

		const auto actionFlipsPair = history.back();
		history.pop_back();

		const auto action = actionFlipsPair.first;
		const auto flips = actionFlipsPair.second;

		if (! action.isPass()) {

			/* Remove the placed brick. */
			state.setTile(action.getPosition(), Tile::Empty);

			/* Unflip flipped bricks. */
			for (auto flip : flips) {
				state.flipBrick(flip);
			}
		}

		state.changeTurn();

		/* Nothin can have happened after game over. */
		state.setGameOver(false);

		/* Set the action was pass flag in the state. Its false if i was the
		 * first action.
		 */
		const auto previousActionWasPass =
			history.empty() ? false : history.back().first.isPass();
		state.setActionWasPass(previousActionWasPass);

	}
}

int Game::numTurns() const noexcept
{
	return history.size();
}

const OthelloState* Game::getNotifyData() const
{
	return &state;
}

Game Game::testEmptyBoard()
{
	Game game;
	game.state = OthelloState();

	return game;
}

} //namespace othello
