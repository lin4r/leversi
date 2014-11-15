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
 * The requested move is illegal in othello rules.
 *
 * Linus Narva.
 */
//XXX Rename to illegal_action_exception
#ifndef ILLEGAL_ACTION_EXCEPTION_HPP_
#define ILLEGAL_ACTION_EXCEPTION_HPP_

#include "ReversiAction.hpp"

#include <exception>

namespace othello {

class illegal_action_exception : public std::exception
{
public:

	illegal_action_exception(ReversiAction action) noexcept;
	virtual ~illegal_action_exception() = default;

	virtual ReversiAction getAction() const noexcept;

	virtual const char* what() const noexcept override;

private:

	ReversiAction action;
};

} //namespace othello

#endif //ILLEGAL_ACTION_EXCEPTION_HPP_