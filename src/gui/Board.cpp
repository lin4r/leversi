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

#include <iostream>

using Cairo::Context;
using Gdk::Pixbuf;
using Glib::FileError;
using Gdk::PixbufError;
using std::cerr;
using std::endl;

namespace reversi {

Board::Board()
{
	try {
		backgroundImage = Pixbuf::create_from_file(
			"res/GameBoard_Reversi_8x8.gif");
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

	return true;
}

} //namespace reversi
