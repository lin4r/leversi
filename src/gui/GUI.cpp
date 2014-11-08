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

#include <gdkmm/general.h>

/* By setting these constants, graphic objects can be changed at compile time
 *, without the need of editing the code.
 */
#ifndef DEFAULT_BACKGROUND_IMAGE_PATH
#define DEFAULT_BACKGROUND_IMAGE_PATH "res/GameBoard_Reversi_8x8.gif"
#endif //DEFAULT_BACKGROUND_IMAGE_PATH

#ifndef DEFAULT_BLACK_PIECE_SPRITE_PATH
#define DEFAULT_BLACK_PIECE_SPRITE_PATH "res/pieceBlack.gif"
#endif //DEFAULT_BLACK_PIECE_SPRITE_PATH

#ifndef DEFAULT_WHITE_PIECE_SPRITE_PATH
#define DEFAULT_WHITE_PIECE_SPRITE_PATH "res/pieceWhite.gif"
#endif //DEFAULT_WHITE_PIECE_SPRITE_PATH

using Gdk::Pixbuf;

namespace reversi {

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
	BoardGraphics graphics;

	graphics.backgroundImage = Pixbuf::create_from_file(
		DEFAULT_BACKGROUND_IMAGE_PATH);
	graphics.blackPieceSprite = Pixbuf::create_from_file(
		DEFAULT_BLACK_PIECE_SPRITE_PATH);
	graphics.whitePieceSprite = Pixbuf::create_from_file(
		DEFAULT_WHITE_PIECE_SPRITE_PATH);

	board.setGraphics(graphics);
	add(board);
	board.show();
}

} //namespace reversi
