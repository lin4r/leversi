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
 * Main function for the othello gui.
 *
 * Linus Narva.
 */

#include "GUI.hpp"

#include <gtkmm/application.h>
#include <glibmm/fileutils.h>

#include <iostream>

using Gtk::Application;
using Glib::FileError;
using Gdk::PixbufError;
using othello::GUI;
using std::cerr;
using std::endl;

int main(int argc, char *argv[])
{
	auto application = Application::create(argc, argv
		, "se.umu.cs.c10lna.othello");

	try {
		GUI gui;
		return application->run(gui);
	} catch (const FileError e) {
		cerr << "FileError: " << e.what() << endl;
	} catch (const PixbufError e) {
		cerr << "PixbufError: " << e.what() << endl;
	}

	return -1;
}
