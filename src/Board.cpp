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
 * Implements Board.hpp
 *
 * Linus Narva.
 */
#include "Board.hpp"
#include "Callback.hpp"
#include "Player.hpp"
#include "Position.hpp"

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
using std::size_t;

namespace othello {

NotificationReceiver::NotificationReceiver(Board* updateObject)
		: updateObject{updateObject}
{}

void NotificationReceiver::notify(const OthelloState* state)
{
	updateObject->update(*state);
}

bool BoardGraphics::isInitialized() const noexcept
{
	return backgroundImage && blackPieceSprite && whitePieceSprite;
}

Board::Board() : Board(8,8) {};
Board::Board(int sizeX, int sizeY) : gridSizeX{sizeX}, gridSizeY{sizeY}
		, grid(sizeX, vector<Tile>(sizeY, Tile::Empty))
		, notifyReceiver{new NotificationReceiver(this)}
		, controller{new Callback()} //XXX Should not depend on this class.
{
	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK
		| Gdk::BUTTON_RELEASE_MASK);

//	signal_motion_notify_event().connect(sigc::mem_fun(*this
//		, &Board::on_motion));

	signal_button_press_event().connect(sigc::mem_fun(*this
		, &Board::on_button_press));

//	signal_button_release_event().connect(sigc::mem_fun(*this
//		, &Board::on_button_release));

	controller->addGameObserver(notifyReceiver);

	/* Initially, show othellos initial state. */
	update(OthelloState::initialState());
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

	for (int i{0}; i < gridSizeX; i++) {
		for (int j{0}; j < gridSizeY; j++) {
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

void Board::update(OthelloState state)
{
	const auto rows = state.getBoardRows();
	const auto columns = state.getBoardColumns();

	for (auto row = 0; row < rows; row++) {
		for (auto col = 0; col < columns; col++) {

			const Position pos(row, col);
			const auto colour = state.inspectTile(pos);

			/* Uses different coordinate systems. */
			const auto x = col;
			const auto y = row;

			placePiece(colour, x, y);
		}
	}

	queue_draw();
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
	const auto tileWidth = boardWidth/static_cast<double>(gridSizeX);
	const auto tileHeight = boardHeight/static_cast<double>(gridSizeY);

	/* Draw coordinates for the piece. */
	const auto drawX = tileWidth*gridX + boardOrigoX;
	const auto drawY = tileHeight*gridY + boardOrigoY;

	return pair<double,double>(drawX, drawY);
}

pair<int,int> Board::tileAt(double pixelX, double pixelY) const noexcept
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
	const auto tileWidth = boardWidth/static_cast<double>(gridSizeX);
	const auto tileHeight = boardHeight/static_cast<double>(gridSizeY);

	/* Translate to board coordinates. */
	const auto pixelOnBoardX = pixelX - boardOrigoX;
	const auto pixelOnBoardY = pixelY - boardOrigoY;

	/* Get tile indizes by integral division. */
	const auto gridX = static_cast<int>(pixelOnBoardX/tileWidth);
	const auto gridY = static_cast<int>(pixelOnBoardY/tileHeight);

	return pair<int,int>(gridX,gridY);
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
		auto tile = tileAt(event->x, event->y);
		controller->pressedTile(tile.first, tile.second);

		cout << "Double click at (x,y)=(" << tile.first << "," << tile.second << ")." << endl; //XXX DEBUG
	}

	return true;
}

//bool Board::on_button_release(GdkEventButton* event)
//{
//	cout << "Button relesased!" << endl; //XXX DEBUG
//
//	return true;
//}

} //namespace othello
