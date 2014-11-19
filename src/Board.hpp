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
 * Othello board widget.
 *
 * Linus Narva.
 */
#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "OthelloView.hpp"

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

#include <vector>
#include <utility>

namespace othello {

struct BorderSize
{
	int north;
	int east;
	int south;
	int west;
};

struct BoardGraphics
{
	Glib::RefPtr<Gdk::Pixbuf> backgroundImage{nullptr};
	Glib::RefPtr<Gdk::Pixbuf> blackPieceSprite{nullptr};
	Glib::RefPtr<Gdk::Pixbuf> whitePieceSprite{nullptr};

	virtual ~BoardGraphics() = default;

	virtual bool isInitialized() const noexcept;
};

class Board : public Gtk::DrawingArea, public OthelloView
{
public:

	Board();
	Board(int sizeX, int sizeY);
	virtual ~Board() = default;

	virtual void placePiece(Tile colour, int gridX, int gridY) override;

	virtual void setGraphics(BorderSize bgImageBorderSize
		, BoardGraphics graphics) noexcept;


protected:

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:

//	bool on_motion(GdkEventMotion* event);
	bool on_button_press(GdkEventButton* event);
//	bool on_button_release(GdkEventButton* event);

	std::pair<double,double> tileDrawCoordinates(int gridX, int gridY)
		const noexcept;

	std::pair<int,int> tileAt(double pixelX, double pixelY) const noexcept;

	int gridSizeX;
	int gridSizeY;

	BorderSize imageBorderSize;

	BoardGraphics graphics;

	std::vector<std::vector<Tile>> grid;
};

} //namespace othello

#endif //BOARD_HPP_
