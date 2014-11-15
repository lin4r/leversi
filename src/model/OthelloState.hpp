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
#ifndef OTHELLO_STATE_HPP_
#define OTHELLO_STATE_HPP_

#include "Tile.hpp"
#include "Player.hpp"
#include "getter_setter.hpp"
#include "OthelloAction.hpp"
#include "Position.hpp"
#include "illegal_action_exception.hpp"

#include <vector>

namespace othello {

class OthelloState
{	
public:

	OthelloState() noexcept;
	OthelloState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~OthelloState() = default;

	static OthelloState initialState() noexcept;

	GETTER(int, boardRows)
	GETTER(int, boardColumns)

	virtual Player whosTurn() const noexcept;
	virtual Tile inspectTile(Position position) const;
	virtual void performAction(OthelloAction action);
	virtual bool existsNonpassAction() const noexcept; //XXX Rename placementPossible
	virtual void setTile(Position position, Tile value);
	virtual bool gameOver() const noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */
	virtual std::vector<Position> searchFlips(OthelloAction action) const;

	//TODO Reverse action.

private:

	void changeTurn() noexcept;

	/* XXX Rename flip */
	void turnBrick(Position position);

	bool isInsideGrid(Position position) const noexcept;

	Tile playerColour(Player player) const noexcept;

	bool gameIsOver{false};
	OthelloAction previousAction;

	Player turn;

	const int boardRows;
	const int boardColumns;

	/* XXX Improvement: const const matrix. */
	std::vector<std::vector<Tile>> grid;
};

} //namespace othello

#endif //OTHELLO_STATE_HPP_
