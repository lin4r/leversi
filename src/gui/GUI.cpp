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
 * Implements GUI.hpp
 *
 * Linus Narva.
 */
#include "GUI.hpp"

namespace reversi {

GUI::GUI()
{
	set_title("Reversi Game by Linus (C) 2014");
	set_border_width(10);
	set_default_size(100,100);

	add(board);
	board.show();

	//XXX DEBUG code.
	board.placePiece(Tile::Black, 3,3);
	board.placePiece(Tile::White, 4,3);
	board.placePiece(Tile::Black, 4,4);
	board.placePiece(Tile::White, 3,4);
	board.queue_draw();
	//<<XXX DEBUG code.
}

} //namespace reversi
