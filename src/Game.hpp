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
#include <utility>

namespace othello {

//XXX Refacor, repllace the action flip pairs with outcomes.
class Game : public Observable<OthelloState>
{	
public:

	Game() noexcept : state{OthelloState::initialState()} {}

	Game(OthelloState initial) noexcept : state(initial) {}

	virtual ~Game() = default;

	/* Commits an action to the game. Returns a vector of flips.
	 */
	virtual flips_t commitAction(OthelloAction action);

	/* Only ever throws if thhere is no history, and then with strong
	 * exception guarantee.
	 */
	virtual void undoLastAction();
	virtual int numTurns() const noexcept;

	virtual const OthelloState* getNotifyData() const override;

	/* Used for testing with passes. */
	static Game testEmptyBoard();

	virtual OthelloState getState() const noexcept
		{ return state; }

	virtual const OthelloState& refState() const noexcept
		{ return state; }

private:

	OthelloState state;

	/* The history: all actions and flips so far.
	 */
	std::vector<std::pair<OthelloAction,flips_t>> history;
};

} //namespace othello

#endif //GAME_HPP_
