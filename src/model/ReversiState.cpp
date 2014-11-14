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
 * Implements ReversiState.hpp
 *
 * Linus Narva.
 */
#include "ReversiState.hpp"

#include <vector>

using std::vector;

namespace reversi {

ReversiState::ReversiState() noexcept : ReversiState(8,8,Player::White)
{
}

ReversiState::ReversiState(int boardRows, int boardColumns, Player starter)
		noexcept
		: turn{starter}, boardRows{boardRows}, boardColumns{boardColumns}
		, grid{vector<vector<Tile>>(boardRows,vector<Tile>(boardColumns
			,Tile::Empty))}
{
}

void ReversiState::performAction(ReversiAction action)
{
	switch (turn) {
	case Player::White: turn = Player::Black; break;
	case Player::Black:
	default: turn = Player::White;
	}
}

Player ReversiState::whosTurn() const noexcept
{
	return turn;
}

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);
