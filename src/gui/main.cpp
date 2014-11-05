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
 * Main function for the reversi gui.
 *
 * Linus Narva.
 */

#include "GUI.hpp"

#include <gtkmm/application.h>

using Gtk::Application;
using reversi::GUI;

int main(int argc, char *argv[])
{
	auto application = Application::create(argc, argv
		, "se.umu.cs.c10lna.reversi");

	GUI gui;

	return application->run(gui);
}
