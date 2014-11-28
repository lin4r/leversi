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

/**
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

class Game : public Observable<OthelloState>
{	
public:

	/**
	 * Construct a standard rule game.
	 */
	Game() noexcept : currentState{OthelloState::initialState()} {}

	/**
	 * Specify the initial state of the game.
	 * param:	The 'custom' initial state of the came.
	 */
	Game(OthelloState initial) noexcept : currentState(initial) {}

	virtual ~Game() = default;

	/**
	 * Commits an action to the game (that is modifies the state and remembers
	 * the changes). Returns a vector of flips.
	 * param:	The action to commit.
	 * return:	The flips caused by the action.
	 */
	virtual flips_t commitAction(OthelloAction action);

	/**
	 * Undoes the last action.
	 * return:	The undone action.
	 */
	virtual void undoLastAction();

	/**
	 * The number of turns that this far.
	 * return:	The number of turns.
	 */
	virtual int numTurns() const noexcept;

	/**
	 * The ObserverObservable notify data, a pointer to the last state.
	 * return: A pointer to the last state.
	 */
	virtual const OthelloState* getNotifyData() const override;

	/**
	 * Gets the state (by copy).
	 * return:	A copy of the state.
	 */
	virtual OthelloState getState() const noexcept
		{ return currentState; }

	/**
	 * Gets a read-only reference to the state.
	 * return:	State reference.
	 */
	virtual const OthelloState& refState() const noexcept
		{ return currentState; }

private:

	/**
	 * The current state.
	 */
	OthelloState currentState;

	/* The history: all outcomes so far, in order.
	 */
	std::vector<Outcome> history;
};

} //namespace othello

#endif //GAME_HPP_
