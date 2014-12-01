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
 * The requested move is illegal in reversi rules.
 *
 * Linus Narva.
 */
#ifndef ILLEGAL_ACTION_EXCEPTION_HPP_
#define ILLEGAL_ACTION_EXCEPTION_HPP_

#include "ReversiAction.hpp"

#include <exception>
#include <string>

namespace reversi {

class illegal_action_exception : public std::exception
{
public:

	illegal_action_exception(std::string message) : message{message} {}
	virtual ~illegal_action_exception() = default;

	virtual const char* what() const noexcept override
		{ return message.c_str(); }

private:

	std::string message;
};

} //namespace reversi

#endif //ILLEGAL_ACTION_EXCEPTION_HPP_
