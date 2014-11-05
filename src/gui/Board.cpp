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

Board::Board() : imageBorderSizeX{1}, imageBorderSizeY{1}
		, grid(8, vector<Tile>(8, Tile::Empty))
{
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

	/* Draw the image in the middle of the drawing area. */
	Gdk::Cairo::set_source_pixbuf(cr, backgroundImage
		, (width - bgWidth)/2, (height - bgHeight)/2);

	cr->paint();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			const auto coordinates = tileCoordinates(i,j);

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

pair<double,double> Board::tileCoordinates(int gridX, int gridY) const noexcept
{
	const auto bgWidth = backgroundImage->get_width();
	const auto bgHeight = backgroundImage->get_height();

	const auto tileWidth = (bgWidth-imageBorderSizeX*2)/8;
	const auto tileHeight = (bgHeight-imageBorderSizeY*2)/8;

	const auto centreX = imageBorderSizeX + tileWidth*(gridX);
	const auto centreY = imageBorderSizeY + tileHeight*(gridY);

	return pair<double,double>(centreX, centreY);
}

} //namespace reversi
