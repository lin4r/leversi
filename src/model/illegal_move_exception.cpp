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
 * Implements illegal_move_exception.hpp
 *
 * Linus Narva.
 */
#include "illegal_move_exception.hpp"

#include <sstream>

namespace reversi {

illegal_move_exception::illegal_move_exception(ReversiAction action)
		: action{action}
{
}

ReversiAction illegal_move_exception::getAction() const noexcept
{
	return action;
}

const char* illegal_move_exception::what() const noexcept
{
	using std::stringstream;

	stringstream ss;
	ss << "The action " << action << ", is illegal in reversi.";

	return ss.str().c_str();
}

} //namespace reversi
