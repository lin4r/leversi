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
#include "getter_setter.hpp"

#include <vector>
#include <utility>

namespace othello {

class Game
{	
public:

	Game() = default;
	virtual ~Game() = default;

	GETTER(OthelloState, state)

	virtual void commitAction(OthelloAction action);
	virtual void undoLastAction() noexcept;
	virtual int numTurns() const noexcept;
	virtual const OthelloState& refState() const noexcept;

private:

	OthelloState state{OthelloState::initialState()};

	/* The history consists of a vector of Action - Result pairs, the result
	 * being the positions of the flipped bricks.
	 */
	std::vector<std::pair<OthelloAction,std::vector<Position>>> history;
};

} //namespace othello

#endif //GAME_HPP_
