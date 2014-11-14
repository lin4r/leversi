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
 * A state of the reversi game.
 *
 * Linus Narva.
 */
#ifndef REVERSI_STATE_HPP_
#define REVERSI_STATE_HPP_

#include "Tile.hpp"

#include <vector>

namespace reversi {

class ReversiState
{	
public:

	ReversiState() noexcept;
	ReversiState(int rows, int columns) noexcept;

	virtual ~ReversiState() = default;

private:

	int rows;
	int columns;

	std::vector<std::vector<Tile>> grid;
};

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);

#endif //REVERSI_STATE_HPP_
