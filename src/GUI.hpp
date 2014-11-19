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
 * Garphical user interface for a othello game.
 *
 * Linus Narva.
 */
#ifndef GUI_HPP_
#define GUI_HPP_

#include "Board.hpp"
#include "OthelloState.hpp"
#include "Observer.hpp"

#include <gtkmm/window.h>

#include <memory>

namespace othello {

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

} //namespace othello

#endif //GUI_HPP_
