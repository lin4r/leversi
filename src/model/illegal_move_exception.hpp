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
#ifndef ILLEGAL_MOVE_EXCEPTION_HPP_
#define ILLEGAL_MOVE_EXCEPTION_HPP_

#include "ReversiAction.hpp"

#include <exception>

namespace reversi {

class illegal_move_exception : public std::exception
{
public:

	illegal_move_exception(ReversiAction action);
	virtual ~illegal_move_exception() = default;

	virtual ReversiAction getAction() const noexcept;

	virtual const char* what() const noexcept override;

private:

	ReversiAction action;
};

} //namespace reversi

#endif //ILLEGAL_MOVE_EXCEPTION_HPP_
