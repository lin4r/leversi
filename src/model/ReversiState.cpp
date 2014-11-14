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
 * Implements ReversiState.hpp
 *
 * Linus Narva.
 */
#include "ReversiState.hpp"

#include <vector>

using std::vector;

namespace reversi {

ReversiState::ReversiState() noexcept : ReversiState(8,8)
{
}

ReversiState::ReversiState(int rows, int columns) noexcept
		: rows{rows}, columns{columns}
{
	grid = vector<vector<Tile>>(rows,vector<Tile>(columns,Tile::Empty));
}

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);
