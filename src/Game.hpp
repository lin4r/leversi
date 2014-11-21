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
 * The game is a composite of the game state and history. It maintains a state
 * on which one can apply actions. It os possible to undo actions to restore
 * an earlier state of the game.
 *
 * Linus Narva.
 */
#ifndef GAME_HPP_
#define GAME_HPP_

#include "OthelloState.hpp"
#include "OthelloAction.hpp"
#include "Observable.hpp"

#include <vector>
#include <exception>

namespace othello {

class undo_initial_state_exception : std::exception
{
public:

	virtual ~undo_initial_state_exception() = default;

	virtual const char* what() const noexcept override;
};

class Game : public Observable<OthelloState>
{	
public:

	Game() noexcept;
	virtual ~Game() = default;

	/* Commits an action to the game. Returns a vector of flips.
	 */
	virtual std::vector<Position> commitAction(OthelloAction action);
	virtual void undoLastAction() noexcept;
	virtual int numTurns() const noexcept;
	virtual OthelloState getState() const noexcept;

	virtual const OthelloState* getNotifyData() const override;

	/* Used for testing with passes. */
	static Game testEmptyBoard();

private:

	/* The history: all states this far.
	 */
	std::vector<OthelloState> history;
};

} //namespace othello

#endif //GAME_HPP_
