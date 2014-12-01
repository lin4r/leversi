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
 * MVC View interface for reversi.
 *
 * Linus Narva.
 */
#ifndef REVERSI_VIEW_HPP_
#define REVERSI_VIEW_HPP_

#include "Tile.hpp"

namespace reversi {

class ReversiView
{
public:

	virtual void placePiece(Tile colour, int gridX, int gridY) = 0;
};

} //namespace reversi

#endif //REVERSI_VIEW_HPP_
