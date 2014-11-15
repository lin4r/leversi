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
#ifndef REVERSI_ACTION_HPP_
#define REVERSI_ACTION_HPP_

#include "getter_setter.hpp"
#include "actionstring_syntax_exception.hpp"
#include "Position.hpp"

#include <string>
#include <iostream>

namespace othello {

class ReversiAction
{	
private:
	Position position = {-1,-1};
	int value{0};
	bool pass{false};

public:

	ReversiAction(Position position) noexcept;
	ReversiAction(Position position, bool pass) noexcept;
	ReversiAction(std::string action);

	virtual ~ReversiAction() = default;

	GETTERSETTER(Position, position);
	GETTERSETTER(int, value)
	GETTERSETTER(bool, pass)

	virtual std::string actionString() const noexcept;

};

} //namespace othello

std::ostream& operator<<(std::ostream& os, othello::ReversiAction action);

#endif //REVERSI_ACTION_HPP_
