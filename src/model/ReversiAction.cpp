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
 * Implements ReversiAction.hpp
 *
 * Linus Narva.
 */

#include "ReversiAction.hpp"

//#include <regex>
#include <cctype> //FIXME Not needed with regex.

using std::string;
using std::ostream;

namespace reversi {


ReversiAction::ReversiAction(int row, int col) noexcept
		: row{row}, column{col}, pass{false}
{
}

ReversiAction::ReversiAction(int row, int col, bool pass) noexcept
		: row{row}, column{col}, pass{pass}
{
}

/* FIXME Use regular expressions. However it turns out these don't exist until
 *gcc 4.9 :(
 */
ReversiAction::ReversiAction(string action)
{
//	using std::regex;
//	using std::regex_match;
//
//	const regex passEx("pass");
//	const regex putPieceEx(R"([[:digit:]])"); //FIXME
//
//	if (regex_match(action, passEx)) {
//		pass = true;
//	} else if (regex_match(action, putPieceEx)) {
//		//FIXME
//		row = 3;
//		column = 4;
//	} else {
//		throw actionstring_syntax_exception(action);
//	}

	using std::isdigit;
	using std::stoi;

	if (action.compare("pass") == 0) {
		pass = true;
	} else if ((action.size() > 4) && isdigit(action.at(1))
			&& isdigit(action.at(3))) {
		row = stoi(action.substr(1,1));
		column = stoi(action.substr(3,1));
	} else {
		throw actionstring_syntax_exception(action);
	}
}

string ReversiAction::actionString() const noexcept
{
	using std::to_string;

	string actionStr;

	if (pass) {
		actionStr = "pass";
	} else {
		actionStr = "(" + to_string(row) + "," + to_string(column) + ")";
	}

	return actionStr;
}

} //namespace reversi

std::ostream& operator<<(std::ostream& os, reversi::ReversiAction action)
{
	return os << "ReversiAction[" << action.actionString() << "]";
}
