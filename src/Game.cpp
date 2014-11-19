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

Game::Game() noexcept
{
	history.push_back(OthelloState::initialState());
}

void Game::commitAction(OthelloAction action)
{
	auto state = getState();
	action.execute(state);
	history.push_back(state);
}

const char* undo_initial_state_exception::what() const noexcept
{
	return "The initial state of the game can not be undone.";
}

void Game::undoLastAction() noexcept
{
	if (history.size() > 1) {
		history.pop_back();
	} else {
		throw undo_initial_state_exception();
	}
}

int Game::numTurns() const noexcept
{
	return history.size() -1;
}

OthelloState Game::getState() const noexcept
{
	return history.back();
}

const OthelloState* Game::getNotifyData() const
{
	return &(history.back());
}

Game Game::testEmptyBoard()
{
	Game game;
	game.history[0] = OthelloState();

	return game;
}

} //namespace othello
