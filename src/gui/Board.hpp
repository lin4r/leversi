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

class Board : public Gtk::DrawingArea
{
public:

	Board();
	virtual ~Board() = default;

	virtual void placePiece(Tile colour, int gridX, int gridY);

	virtual void setGraphics(BorderSize bgImageBorderSize
		, BoardGraphics graphics) noexcept;


protected:

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:

	bool on_motion(GdkEventMotion* event);
	bool on_button_press(GdkEventButton* event);
	bool on_button_release(GdkEventButton* event);

	std::pair<double,double> tileDrawCoordinates(int gridX, int gridY)
		const noexcept;

	BorderSize imageBorderSize;

	BoardGraphics graphics;

	std::vector<std::vector<Tile>> grid;
};

} //namespace reversi

#endif //BOARD_HPP_
