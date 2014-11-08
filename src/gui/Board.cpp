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

#include <utility>
#include <vector>

#include <iostream> //XXX DEBUG
using namespace std; //XXX DEBUG

using Cairo::Context;
using Gdk::Pixbuf;
using std::pair;
using std::vector;

namespace reversi {

bool BoardGraphics::isInitialized() const noexcept
{
	return backgroundImage && blackPieceSprite && whitePieceSprite;
}

Board::Board() : grid(8, vector<Tile>(8, Tile::Empty))
{
	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK
		| Gdk::BUTTON_RELEASE_MASK);

//	signal_motion_notify_event().connect(sigc::mem_fun(*this
//		, &Board::on_motion));

	signal_button_press_event().connect(sigc::mem_fun(*this
		, &Board::on_button_press));

//	signal_button_release_event().connect(sigc::mem_fun(*this
//		, &Board::on_button_release));
}

void Board::setGraphics(BorderSize bgImageBorderSize, BoardGraphics graphics)
		noexcept
{
	this->imageBorderSize = bgImageBorderSize;
	this->graphics = graphics;

	/* Resize the parent container to make place. */
	set_size_request(graphics.backgroundImage->get_width()
		, graphics.backgroundImage->get_height());
}

bool Board::on_draw(const Cairo::RefPtr<Context>& cr)
{
	if (! graphics.isInitialized()) {
		return false;
	}

	auto allocation = get_allocation();
	const auto width = allocation.get_width();
	const auto height = allocation.get_height();

	const auto bgWidth = graphics.backgroundImage->get_width();
	const auto bgHeight = graphics.backgroundImage->get_height();

	/* Draw in the middle of the draw area if it is bigger than the image. */
	const auto centredBackgroundX = (width - bgWidth)/2;
	const auto centredBackgroundY = (height - bgHeight)/2;

	/* Draw the image in the middle of the drawing area. */
	Gdk::Cairo::set_source_pixbuf(cr, graphics.backgroundImage
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
			case Tile::Black:
				drawPiece(graphics.blackPieceSprite, coordinates);
				break;
			case Tile::White:
				drawPiece(graphics.whitePieceSprite, coordinates);
				break;
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
	const auto bgWidth = graphics.backgroundImage->get_width();
	const auto bgHeight = graphics.backgroundImage->get_height();

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

//bool Board::on_motion(GdkEventMotion* event)
//{
//	cout << "Mouse moved!" << endl; //XXX DEBUG
//
//	return true;
//}

bool Board::on_button_press(GdkEventButton* event)
{
	constexpr int LEFT_MOUSE_BUTTON{1};

	/* Only react to left mouse button double clicks. */
	if (event->button == LEFT_MOUSE_BUTTON
			&& event->type == GDK_2BUTTON_PRESS)
	{
		cout << "Double click pressed!" << endl; //XXX DEBUG
	}

	return true;
}

//bool Board::on_button_release(GdkEventButton* event)
//{
//	cout << "Button relesased!" << endl; //XXX DEBUG
//
//	return true;
//}

} //namespace reversi
