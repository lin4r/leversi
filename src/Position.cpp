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
 * Implements Position.hpp
 *
 * Linus Narva.
 */
#include "Position.hpp"

namespace othello {

bool operator==(const othello::Position& p1, const othello::Position& p2)
		noexcept
{
	return (p1.row == p2.row) && (p1.column == p2.column);
}

bool operator<(const othello::Position& p1, const othello::Position& p2)
		noexcept
{
	if (p1.row == p2.row) {
		return p1.column < p2.column;
	} else {
		return p1.row < p2.row;
	}
}

std::ostream& operator<<(std::ostream& os, const othello::Position& p)
{
	return os << "othello::Position(" << p.row << "," << p.column << ")";
}

} //namespace othello
