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

namespace reversi {

class Board : public Gtk::DrawingArea
{
public:

	Board();
	virtual ~Board() = default;

protected:

	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

	Glib::RefPtr<Gdk::Pixbuf> backgroundImage;
};

} //namespace reversi

#endif //BOARD_HPP_
