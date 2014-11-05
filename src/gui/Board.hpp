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
 * Reversi board widget.
 *
 * Linus Narva.
 */
#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

#include <vector>
#include <utility>

namespace reversi {

enum class Tile
{
	Empty, Black, White
};

class Board : public Gtk::DrawingArea
{
public:

	Board();
	virtual ~Board() = default;

	virtual void placePiece(Tile colour, int gridX, int gridY);

protected:

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:

	std::pair<double,double> tileCoordinates(int gridX, int gridY)
		const noexcept;

	int imageBorderSizeX;
	int imageBorderSizeY;

	Glib::RefPtr<Gdk::Pixbuf> backgroundImage;
	Glib::RefPtr<Gdk::Pixbuf> blackPieceImage;
	Glib::RefPtr<Gdk::Pixbuf> whitePieceImage;

	std::vector<std::vector<Tile>> grid;
};

} //namespace reversi

#endif //BOARD_HPP_
