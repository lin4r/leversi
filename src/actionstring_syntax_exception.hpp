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
 * The Reversi action string is not well formed.
 *
 * Linus Narva.
 */
#ifndef ACTIONSTRING_SYNTAX_EXCEPTION_
#define ACTIONSTRING_SYNTAX_EXCEPTION_

#include <exception>
#include <string>

namespace reversi {

class actionstring_syntax_exception : public std::exception
{
public:

	actionstring_syntax_exception(std::string action) : action{action}
		{}

	virtual ~actionstring_syntax_exception() = default;

	virtual std::string getActionString() const noexcept
		{ return action; }

	inline virtual const char* what() const noexcept override;

private:

	const std::string action;
};

const char* actionstring_syntax_exception::what() const noexcept
{
	std::string message{"The action pattern was note well formed."};

	if (! action.empty()) {
		message += " The pattern was \"" + action + "\".";
	}

	return message.c_str();
}

} //namespace reversi

#endif //ACTIONSTRING_SYNTAX_EXCEPTION_
