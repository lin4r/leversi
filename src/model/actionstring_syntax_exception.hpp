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
 * The Reversi action string is not well formed.
 *
 * Linus Narva.
 */
#ifndef ACTIONSTRING_SYNTAX_EXCEPTION_
#define ACTIONSTRING_SYNTAX_EXCEPTION_

#include "getter_setter.hpp"

#include <exception>
#include <string>

namespace othello {

class actionstring_syntax_exception : public std::exception
{
public:

	actionstring_syntax_exception() noexcept;
	actionstring_syntax_exception(std::string action) noexcept;
	virtual ~actionstring_syntax_exception() = default;

	GETTER(std::string, action)

	virtual const char* what() const noexcept override;

private:

	const std::string action;
};

} //namespace othello

#endif //ACTIONSTRING_SYNTAX_EXCEPTION_
