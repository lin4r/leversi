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
 * Implements actionstring_syntax_exception.hpp
 *
 * Linus Narva.
 */
#include "actionstring_syntax_exception.hpp"

using std::string;

namespace reversi {

actionstring_syntax_exception::actionstring_syntax_exception() noexcept
		: action{""}
{
}

actionstring_syntax_exception::actionstring_syntax_exception(string action)
		noexcept
		: action{action}
{
}

const char* actionstring_syntax_exception::what() const noexcept
{
	string message{"The action pattern was note well formed."};

	if (! action.empty()) {
		message += " The pattern was \"" + action + "\".";
	}

	return message.c_str();
}

} //namespace reversi
