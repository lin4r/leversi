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
 * Implements illegal_action_exception.hpp
 *
 * Linus Narva.
 */
#include "illegal_action_exception.hpp"

#include <sstream>

namespace othello {

illegal_action_exception::illegal_action_exception(OthelloAction action)
		noexcept
		: action{action}
{
}

OthelloAction illegal_action_exception::getAction() const noexcept
{
	return action;
}

const char* illegal_action_exception::what() const noexcept
{
	using std::stringstream;

	stringstream ss;
	ss << "The action " << action << ", is illegal in othello.";

	return ss.str().c_str();
}

} //namespace othello
