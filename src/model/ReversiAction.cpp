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

#include <regex>

using std::string;
using std::ostream;

namespace reversi {


ReversiAction::ReversiAction(int row, int col)
		: row{row}, column{col}, pass{false}
{
}

ReversiAction::ReversiAction(int row, int col, bool pass)
		: row{row}, column{col}, pass{pass}
{
}

ReversiAction::ReversiAction(string action)
{
	using std::regex;
	using std::regex_match;

	const regex passEx(R"(\s*pass\s*)");
	const regex putPieceEx(R"([[:space:]]*[(]\d,\d[)][[:space:]]*)");

	if (regex_match(action, passEx)) {
		row = 0;
		column = 0;
		pass = true;
	} else if (regex_match(action, putPieceEx)) {
		//TODO
	} else {
		throw actionstring_syntax_exception(action);
	}
}

string ReversiAction::moveString() const noexcept
{
	return "TODO"; //TODO
}

} //namespace reversi

std::ostream& operator<<(std::ostream& os, reversi::ReversiAction action)
{
	return os << "ReversiAction[" << action.moveString() << "]";
}
