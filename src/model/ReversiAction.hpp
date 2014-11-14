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

/*
 * A reversi action i.e. putting the reversi brick on some position on the
 * board.
 *
 * Linus Narva.
 */
#ifndef REVERSI_ACTION_HPP_
#define REVERSI_ACTION_HPP_

#include "getter_setter.hpp"
#include "actionstring_syntax_exception.hpp"

#include <string>
#include <iostream>

namespace reversi {

class ReversiAction
{	
private:
	int row{-1};
	int column{-1};
	int value{0};
	bool pass{false};

public:

	ReversiAction(int row, int col) noexcept;
	ReversiAction(int row, int col, bool pass) noexcept;
	ReversiAction(std::string action);

	virtual ~ReversiAction() = default;

	GETTERSETTER(int, row)
	GETTERSETTER(int, column)
	GETTERSETTER(int, value)
	GETTERSETTER(bool, pass)

	virtual std::string actionString() const noexcept;

};

} //namespace reversi

std::ostream& operator<<(std::ostream& os, reversi::ReversiAction action);

#endif //REVERSI_ACTION_HPP_
