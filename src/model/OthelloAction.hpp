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
 * A othello action i.e. putting the othello brick on some position on the
 * board.
 *
 * Linus Narva.
 */
#ifndef OTHELLO_ACTION_HPP_
#define OTHELLO_ACTION_HPP_

#include "getter_setter.hpp"
#include "Position.hpp"
#include "OthelloState.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace othello {

class OthelloAction
{	
private:
	Position position = {-1,-1};
	bool pass{false};

public:

	OthelloAction(Position position) noexcept;
	OthelloAction(Position position, bool pass) noexcept;
	OthelloAction(std::string action);

	virtual ~OthelloAction() = default;

	GETTER(Position, position);

	virtual bool isPass() const noexcept;

	virtual std::string actionString() const noexcept;

	virtual void execute(OthelloState& state);
	virtual bool existsLegalPlacement(const OthelloState& state) const noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */ 
	virtual std::vector<Position> searchFlips(const OthelloState& state) const;
};

} //namespace othello

std::ostream& operator<<(std::ostream& os, othello::OthelloAction action);

#endif //OTHELLO_ACTION_HPP_