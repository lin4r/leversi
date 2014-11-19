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
 * Implements Callback.hpp
 *
 * Linus Narva.
 */
#include "Callback.hpp"
#include "Position.hpp"
#include "OthelloAction.hpp"

namespace othello {

Callback::Callback() : model{new Game()}
{
}

void Callback::pressedTile(int indexX, int indexY)
{
	//TODO error handling.
	Position pos(indexX, indexY);
	OthelloAction action(pos);
	model->commitAction(action);
}

} //namespace othello
