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
 * A position on a grid.
 *
 * Linus Narva.
 */
#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <iostream>

namespace othello {

struct Position
{
public:

	int row;
	int column;

	Position(int row, int column);

	virtual ~Position() = default;

	virtual Position north() const noexcept;
	virtual Position east() const noexcept;
	virtual Position south() const noexcept;
	virtual Position west() const noexcept;

	virtual Position northEast() const noexcept;
	virtual Position southEast() const noexcept;
	virtual Position southWest() const noexcept;
	virtual Position northWest() const noexcept;
};

} //namespace othello

bool operator==(const othello::Position& p1, const othello::Position& p2);

std::ostream& operator<<(std::ostream& os, const othello::Position& p);

#endif //POSITION_HPP_
