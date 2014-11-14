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

#include <string>

namespace reversi {

struct Position
{
	int row;
	int column;
};

} //namespace reversi

#endif //POSITION_HPP_
