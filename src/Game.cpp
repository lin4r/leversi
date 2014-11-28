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
	auto flips = action.execute(currentState);

	Outcome outcome = {action, flips};
	history.push_back(outcome);

	return flips;
}

void Game::undoLastAction()
{
	if (history.empty()) {

		throw undo_initial_state_exception();

	} else {

		const auto lastOutcome = history.back();
		history.pop_back();


		if (! lastOutcome.action.isPass()) {

			/* Remove the placed brick. */
			currentState.setTile(lastOutcome.action.getPosition()
				, Tile::Empty);

			/* Unflip flipped bricks. */
			for (auto flip : lastOutcome.flips) {
				currentState.flipBrick(flip);
			}
		}

		currentState.changeTurn();

		/* Nothin can have happened after game over. */
		currentState.setGameOver(false);

		/* Set the action was pass flag in the state. Its false if i was the
		 * first action.
		 */
		const auto previousActionWasPass =
			history.empty() ? false : history.back().action.isPass();
		currentState.setActionWasPass(previousActionWasPass);
	}
}

int Game::numTurns() const noexcept
{
	return history.size();
}

const OthelloState* Game::getNotifyData() const
{
	return &currentState;
}

} //namespace othello
