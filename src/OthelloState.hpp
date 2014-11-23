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
#include "getter_setter.hpp" //XXX Deptrecated.
#include "Position.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace othello {

class OthelloState
{	
public:

	OthelloState() noexcept;
	OthelloState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~OthelloState() = default;

	static OthelloState initialState() noexcept;

	GETTER(int, boardRows) //XXX Deptrecated
	GETTER(int, boardColumns) //XXX Deprecated

	virtual void changeTurn() noexcept;
	virtual void flipBrick(Position position);
	virtual bool isInsideGrid(Position position) const noexcept;
	virtual void updateGameStatus(bool actionWasPass) noexcept; //XXX Deprecated
	virtual bool gameOver() const noexcept; //XXX Deprecated.

	virtual std::string toString() const noexcept;
	virtual std::string gridString() const noexcept;

	virtual std::string whoLeads() const noexcept;

	//Getters and setters.
	virtual bool isGameOver() const noexcept
		{ return gameIsOver; }

	virtual void setGameOver(bool gameOver) noexcept
		{ gameIsOver = gameOver; }

	virtual bool wasActionPass() const noexcept
		{ return actionWasPass; }

	virtual void setActionWasPass(bool actionWasPass) noexcept
		{ this->actionWasPass = actionWasPass; }

	virtual Tile inspectTile(Position position) const
		{ return grid.at(position.row).at(position.column); }

	virtual void setTile(Position position, Tile value)
		{ grid.at(position.row).at(position.column) = value; }

	virtual Player whosTurn() const noexcept
		{ return playersTurn; }

	virtual int getBoardRows() const noexcept
		{ return boardRows; }

	virtual int getBoardColumns() const noexcept
		{ return boardColumns; }

private:

	bool gameIsOver{false};
	bool actionWasPass{false};

	Player playersTurn;

	int boardRows;
	int boardColumns;
	std::vector<std::vector<Tile>> grid;

//Friends

	friend bool operator==(const OthelloState& state1
		, const OthelloState& state2);

	friend std::ostream& operator<<(std::ostream& os
		, const OthelloState& state);
};

bool operator==(const OthelloState& state1, const OthelloState& state2);

inline bool operator!=(const OthelloState& state1, const OthelloState& state2)
	{ return !(state1 == state2); }

inline std::ostream& operator<<(std::ostream& os, const OthelloState& state)
	{ return os << state.toString(); }

} //namespace othello

#endif //OTHELLO_STATE_HPP_
