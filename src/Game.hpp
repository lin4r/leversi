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

/**
 * The game is a composite of the game state and history. It maintains a state
 * on which one can apply actions. It os possible to undo actions to restore
 * an earlier state of the game.
 *
 * Linus Narva.
 */
#ifndef GAME_HPP_
#define GAME_HPP_

#include "ReversiState.hpp"
#include "ReversiAction.hpp"
#include "Observable.hpp"

#include <vector>
#include <exception>

namespace reversi {

class Game : public Observable<ReversiState>
{	
public:

	/**
	 * Construct a standard rule game.
	 */
	Game() : currentState{ReversiState::initialState()} {}

	/**
	 * Specify the initial state of the game.
	 * param:	The 'custom' initial state of the came.
	 */
	Game(ReversiState initial) noexcept : currentState(initial) {}

	virtual ~Game() = default;

	/**
	 * Commits an action to the game (that is modifies the state and remembers
	 * the changes). Returns a vector of flips.
	 * param:	The action to commit.
	 * return:	The flips caused by the action.
	 */
	virtual flips_t commitAction(ReversiAction action);

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
	virtual const ReversiState* getNotifyData() const override;

	/**
	 * Gets the state (by copy).
	 * return:	A copy of the state.
	 */
	virtual ReversiState getState() const noexcept
		{ return currentState; }

	/**
	 * Gets a read-only reference to the state.
	 * return:	State reference.
	 */
	virtual const ReversiState& refState() const noexcept
		{ return currentState; }

private:

	/**
	 * The current state.
	 */
	ReversiState currentState;

	/* The history: all outcomes so far, in order.
	 */
	std::vector<Outcome> history;
};

} //namespace reversi

#endif //GAME_HPP_
