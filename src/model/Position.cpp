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

Position::Position(int row, int column) : row{row}, column{column} {}

Position Position::north() const noexcept
{
	return Position(row-1, column);
}

Position Position::east() const noexcept
{
	return Position(row, column+1);
}

Position Position::south() const noexcept
{
	return Position(row+1, column);
}

Position Position::west() const noexcept
{
	return Position(row, column-1);
}

Position Position::northEast() const noexcept
{
	return north().east();
}

Position Position::southEast() const noexcept
{
	return south().east();
}

Position Position::southWest() const noexcept
{
	return south().west();
}

Position Position::northWest() const noexcept
{
	return north().west();
}

} //namespace othello

bool operator==(const othello::Position& p1, const othello::Position& p2)
{
	return (p1.row == p2.row) && (p1.column == p2.column);
}

std::ostream& operator<<(std::ostream& os, const othello::Position& p)
{
	return os << "othello::Position(" << p.row << "," << p.column << ")";
}
