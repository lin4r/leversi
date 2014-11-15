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
 * A state of the othello game.
 *
 * Linus Narva.
 */
#ifndef REVERSI_STATE_HPP_
#define REVERSI_STATE_HPP_

#include "Tile.hpp"
#include "Player.hpp"
#include "getter_setter.hpp"
#include "ReversiAction.hpp"
#include "Position.hpp"
#include "illegal_action_exception.hpp"

#include <vector>

namespace othello {

class ReversiState
{	
public:

	ReversiState() noexcept;
	ReversiState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~ReversiState() = default;

	/* FIXME It turns out that this is the Othello starting state and that
	 * Othello techbically differs from othello in this rule only. 
	 * SO I NEED TO RENAME EVRYTHING :(
	 */
	static ReversiState initialState() noexcept;

	GETTER(int, boardRows)
	GETTER(int, boardColumns)

	virtual Player whosTurn() const noexcept;
	virtual Tile inspectTile(Position position) const;
	virtual void performAction(ReversiAction action);
	virtual bool existsNonpassAction() const noexcept; //XXX Rename placementPossible
	virtual void setTile(Position position, Tile value);
	virtual bool gameOver() const noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */
	virtual std::vector<Position> searchFlips(ReversiAction action) const;

	//TODO Reverse action.

private:

	void changeTurn() noexcept;

	/* XXX Rename flip */
	void turnBrick(Position position);

	bool isInsideGrid(Position position) const noexcept;

	Tile playerColour(Player player) const noexcept;

	bool gameIsOver{false};
	ReversiAction previousAction;

	Player turn;

	const int boardRows;
	const int boardColumns;

	/* XXX Improvement: const const matrix. */
	std::vector<std::vector<Tile>> grid;
};

} //namespace othello

#endif //REVERSI_STATE_HPP_
