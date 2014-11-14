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
};

} //namespace reversi

inline bool operator==(const reversi::Position& p1, const reversi::Position& p2)
{
	return (p1.row == p2.row) && (p1.column == p2.column);
}

inline std::ostream& operator<<(std::ostream& os, const reversi::Position& p)
{
	return os << "reversi::Position(" << p.row << "," << p.column << ")";
}

#endif //POSITION_HPP_
