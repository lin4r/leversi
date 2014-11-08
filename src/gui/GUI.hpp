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
 * Garphical user interface for a reversi game.
 *
 * Linus Narva.
 */
#ifndef GUI_HPP_
#define GUI_HPP_

#include "Board.hpp"

#include <gtkmm/window.h>

namespace reversi {

class GUI : public Gtk::Window
{
public:

	GUI();
	virtual ~GUI() = default;

protected:

	Board board;

private:

	void initBoard();
};

} //namespace reversi

#endif //GUI_HPP_
