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
 * Implements GUI.hpp
 *
 * Linus Narva.
 */
#include "GUI.hpp"

#include <gdkmm/general.h>

/* By setting these constants, graphic objects can be changed at compile time
 *, without the need of editing the code.
 */
#ifndef DEFAULT_BACKGROUND_IMAGE_BORDER_NORTH
#define DEFAULT_BACKGROUND_IMAGE_BORDER_NORTH 1
#endif //DEFAULT_BACKGROUND_IMAGE_BORDER_NORTH

#ifndef DEFAULT_BACKGROUND_IMAGE_BORDER_EAST
#define DEFAULT_BACKGROUND_IMAGE_BORDER_EAST 1
#endif //DEFAULT_BACKGROUND_IMAGE_BORDER_EAST


#ifndef DEFAULT_BACKGROUND_IMAGE_BORDER_SOUTH
#define DEFAULT_BACKGROUND_IMAGE_BORDER_SOUTH 1
#endif //DEFAULT_BACKGROUND_IMAGE_BORDER_SOUTH

#ifndef DEFAULT_BACKGROUND_IMAGE_BORDER_WEST
#define DEFAULT_BACKGROUND_IMAGE_BORDER_WEST 1
#endif //DEFAULT_BACKGROUND_IMAGE_BORDER_WEST

#ifndef DEFAULT_BACKGROUND_IMAGE_PATH
#define DEFAULT_BACKGROUND_IMAGE_PATH "res/board.gif"
#endif //DEFAULT_BACKGROUND_IMAGE_PATH

#ifndef DEFAULT_BLACK_PIECE_SPRITE_PATH
#define DEFAULT_BLACK_PIECE_SPRITE_PATH "res/blackPiece.gif"
#endif //DEFAULT_BLACK_PIECE_SPRITE_PATH

#ifndef DEFAULT_WHITE_PIECE_SPRITE_PATH
#define DEFAULT_WHITE_PIECE_SPRITE_PATH "res/whitePiece.gif"
#endif //DEFAULT_WHITE_PIECE_SPRITE_PATH

using Gdk::Pixbuf;

namespace othello {

GUI::GUI()
{
	set_title("Reversi Game by Linus (C) 2014");
	set_border_width(10);
	set_default_size(100,100);

	initBoard();

	//XXX DEBUG code.
	board.placePiece(Tile::White, 0,0);
	board.placePiece(Tile::Black, 0,7);
	board.placePiece(Tile::Black, 7,0);
	board.placePiece(Tile::White, 7,7);

	board.placePiece(Tile::Black, 3,3);
	board.placePiece(Tile::White, 4,3);
	board.placePiece(Tile::Black, 4,4);
	board.placePiece(Tile::White, 3,4);
	board.queue_draw();
	//<<XXX DEBUG code.
}

void GUI::initBoard()
{
	BorderSize bgImageBorderSize = {
		DEFAULT_BACKGROUND_IMAGE_BORDER_NORTH
		, DEFAULT_BACKGROUND_IMAGE_BORDER_WEST
		, DEFAULT_BACKGROUND_IMAGE_BORDER_SOUTH
		, DEFAULT_BACKGROUND_IMAGE_BORDER_EAST
	};

	BoardGraphics graphics;

	graphics.backgroundImage = Pixbuf::create_from_file(
		DEFAULT_BACKGROUND_IMAGE_PATH);
	graphics.blackPieceSprite = Pixbuf::create_from_file(
		DEFAULT_BLACK_PIECE_SPRITE_PATH);
	graphics.whitePieceSprite = Pixbuf::create_from_file(
		DEFAULT_WHITE_PIECE_SPRITE_PATH);

	board.setGraphics(bgImageBorderSize, graphics);
	add(board);
	board.show();
}

} //namespace othello
