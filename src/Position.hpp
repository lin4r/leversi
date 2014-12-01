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
 * A position on a grid.
 *
 * Linus Narva.
 */
#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <iostream>

namespace reversi {

struct Position
{
public:

	int row;
	int column;

	Position(int row, int column) : row{row}, column{column} {}

	virtual ~Position() = default;

	virtual Position north() const noexcept
		{ return Position(row-1, column); }

	virtual Position east() const noexcept
		{ return Position(row, column+1); }

	virtual Position south() const noexcept
		{ return Position(row+1, column); }

	virtual Position west() const noexcept
		{ return Position(row, column-1); }

	virtual Position northEast() const noexcept
		{ return north().east(); }

	virtual Position southEast() const noexcept
		{ return south().east(); }

	virtual Position southWest() const noexcept
		{ return south().west(); }

	virtual Position northWest() const noexcept
		{ return north().west(); }
};

bool operator==(const Position& p1, const Position& p2) noexcept;

inline bool operator!=(const Position& p1, const Position& p2) noexcept
	{ return !(p1 == p2); }

/* This operator is defined so that the position can be put in a set. Rows
 * first decides predecense. If the rows are equal then the columns decide.*/
bool operator<(const Position& p1, const Position& p2) noexcept;

std::ostream& operator<<(std::ostream& os, const Position& p);

} //namespace reversi

#endif //POSITION_HPP_
