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
	virtual void execute(OthelloAction action);
	virtual bool existsLegalPlacement() const noexcept;
	virtual void setTile(Position position, Tile value);
	virtual bool gameOver() const noexcept;

	/* Lists which bricks are turned by the action.
	 * Ret: A vector of positions where the bricks where turned
	 */
	virtual std::vector<Position> searchFlips(OthelloAction action) const;

private:

	void changeTurn() noexcept;
	void flipBrick(Position position);
	bool isInsideGrid(Position position) const noexcept;
	bool gameIsOver{false};
	OthelloAction previousAction;

	Player playersTurn;

	const int boardRows;
	const int boardColumns;
	std::vector<std::vector<Tile>> grid;
};

} //namespace othello

#endif //OTHELLO_STATE_HPP_
