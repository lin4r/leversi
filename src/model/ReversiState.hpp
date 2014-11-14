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
 * A state of the reversi game.
 *
 * Linus Narva.
 */
#ifndef REVERSI_STATE_HPP_
#define REVERSI_STATE_HPP_

#include "Tile.hpp"
#include "Player.hpp"
#include "getter_setter.hpp"
#include "ReversiAction.hpp"

#include <vector>

namespace reversi {

class ReversiState
{	
public:

	ReversiState() noexcept;
	ReversiState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~ReversiState() = default;

	GETTER(int, boardRows)
	GETTER(int, boardColumns)

	virtual Player whosTurn() const noexcept;

	virtual void performAction(ReversiAction action);

	//TODO Reverse action.

private:

	Player turn;

	const int boardRows;
	const int boardColumns;

	/* XXX Improvement: const const matrix. */
	std::vector<std::vector<Tile>> grid;
};

} //namespace reversi

//std::ostream& operator<<(std::ostream& os, reversi::ReversiState action);

#endif //REVERSI_STATE_HPP_
