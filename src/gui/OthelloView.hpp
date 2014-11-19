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
 * MVC View interface for othello.
 *
 * Linus Narva.
 */
#ifndef OTHELLO_VIEW_HPP_
#define OTHELLO_VIEW_HPP_

#include "Tile.hpp"

namespace othello {

class OthelloView
{
public:

	virtual void placePiece(Tile colour, int gridX, int gridY) = 0;
};

} //namespace othello

#endif //OTHELLO_VIEW_HPP_
