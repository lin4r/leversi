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
 * Implements Position.hpp
 *
 * Linus Narva.
 */
#include "Position.hpp"

namespace reversi {

bool operator==(const reversi::Position& p1, const reversi::Position& p2)
		noexcept
{
	return (p1.row == p2.row) && (p1.column == p2.column);
}

bool operator<(const reversi::Position& p1, const reversi::Position& p2)
		noexcept
{
	if (p1.row == p2.row) {
		return p1.column < p2.column;
	} else {
		return p1.row < p2.row;
	}
}

std::ostream& operator<<(std::ostream& os, const reversi::Position& p)
{
	return os << "reversi::Position(" << p.row << "," << p.column << ")";
}

} //namespace reversi
