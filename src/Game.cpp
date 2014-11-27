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

using std::vector;

namespace othello {

flips_t Game::commitAction(OthelloAction action)
{
	auto flips = action.execute(state);

	Outcome outcome = {action, flips};
	history.push_back(outcome);

	return flips;
}

void Game::undoLastAction()
{
	if (history.empty()) {

		throw undo_initial_state_exception();

	} else {

		const auto outcome = history.back();
		history.pop_back();

		if (! outcome.action.isPass()) {

			/* Remove the placed brick. */
			state.setTile(outcome.action.getPosition(), Tile::Empty);

			/* Unflip flipped bricks. */
			for (auto flip : outcome.flips) {
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
			history.empty() ? false : history.back().action.isPass();
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
