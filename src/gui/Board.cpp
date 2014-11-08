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
 * Implements Board.hpp
 *
 * Linus Narva.
 */
#include "Board.hpp"

#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>

#include <utility>
#include <vector>
#include <iostream>

using Cairo::Context;
using Gdk::Pixbuf;
using Glib::FileError;
using Gdk::PixbufError;
using std::pair;
using std::vector;
using std::cerr;
using std::endl;

namespace reversi {

Board::Board() : grid(8, vector<Tile>(8, Tile::Empty))
{
	imageBorderSize = {1,1,1,1};

	try {
		backgroundImage = Pixbuf::create_from_file(
			"res/GameBoard_Reversi_8x8.gif");
		blackPieceImage = Pixbuf::create_from_file("res/pieceBlack.gif");
		whitePieceImage = Pixbuf::create_from_file("res/pieceWhite.gif");
	} catch (const FileError e) {
		cerr << "FileError: " << e.what() << endl;
	} catch (const PixbufError e) {
		cerr << "PixbufError: " << e.what() << endl;
	}

	if (backgroundImage) {
		/* Resize the parent container to make place. */
		set_size_request(backgroundImage->get_width()
			, backgroundImage->get_height());
	}
}

bool Board::on_draw(const Cairo::RefPtr<Context>& cr)
{
	if (! backgroundImage) {
		return false;
	}

	auto allocation = get_allocation();
	const auto width = allocation.get_width();
	const auto height = allocation.get_height();

	const auto bgWidth = backgroundImage->get_width();
	const auto bgHeight = backgroundImage->get_height();

	/* Draw in the middle of the draw area if it is bigger than the image. */
	const auto centredBackgroundX = (width - bgWidth)/2;
	const auto centredBackgroundY = (height - bgHeight)/2;

	/* Draw the image in the middle of the drawing area. */
	Gdk::Cairo::set_source_pixbuf(cr, backgroundImage
		, centredBackgroundX, centredBackgroundY);

	cr->paint();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			const auto coordinates = tileDrawCoordinates(i,j);

			const auto drawPiece = [&](Glib::RefPtr<Gdk::Pixbuf> pieceImg
				, pair<double,double> coordinates)
			{
				Gdk::Cairo::set_source_pixbuf(cr, pieceImg
					, coordinates.first, coordinates.second);
				cr->paint();
			};

			switch (grid.at(i).at(j)) {
			case Tile::Black: drawPiece(blackPieceImage, coordinates); break;
			case Tile::White: drawPiece(whitePieceImage, coordinates); break;
			default: ;
			}
		}
	}

	return true;
}

void Board::placePiece(Tile colour, int gridX, int gridY)
{
	grid.at(gridX).at(gridY) = colour;
}

pair<double,double> Board::tileDrawCoordinates(
		int gridX, int gridY) const noexcept
{
	/* Widget size. */
	auto allocation = get_allocation();
	const auto widgetWidth = allocation.get_width();
	const auto widgetHeight = allocation.get_height();

	/* Background size. */
	const auto bgWidth = backgroundImage->get_width();
	const auto bgHeight = backgroundImage->get_height();

	/* Shift between the widget coordinate system and board. */
	const auto boardOrigoX = (widgetWidth - bgWidth)/2.0
		+ imageBorderSize.west;
	const auto boardOrigoY = (widgetHeight - bgHeight)/2.0
		+ imageBorderSize.north;

	/* The size of the board */
	const auto boardWidth = bgWidth - imageBorderSize.west
		- imageBorderSize.east;
	const auto boardHeight = bgHeight - imageBorderSize.north
		- imageBorderSize.south;

	/* The size of a tile on the board. */
	const auto tileWidth = boardWidth/8.0;
	const auto tileHeight = boardHeight/8.0;

	/* Draw coordinates for the piece. */
	const auto drawX = tileWidth*gridX + boardOrigoX;
	const auto drawY = tileHeight*gridY + boardOrigoY;

	return pair<double,double>(drawX, drawY);
}

} //namespace reversi
