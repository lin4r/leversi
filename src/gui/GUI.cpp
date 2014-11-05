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
 * Implements GUI.hpp
 *
 * Linus Narva.
 */
#include "GUI.hpp"

namespace reversi {

GUI::GUI()
{
	set_default_size(300,200);
	set_border_width(10);
	set_title("Reversi Game by Linus (C) 2014");
}

} //namespace reversi
