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

	virtual void changeTurn() noexcept;
	virtual void flipBrick(Position position);
	virtual bool isInsideGrid(Position position) const noexcept;

	virtual std::string toString() const noexcept;
	virtual std::string gridString() const noexcept;

	virtual bool isGameOver() const noexcept
		{ return gameIsOver; }

	virtual void setGameOver(bool gameOver) noexcept
		{ gameIsOver = gameOver; }

	virtual bool wasActionPass() const noexcept
		{ return actionWasPass; }

	virtual void setActionWasPass(bool actionWasPass) noexcept
		{ this->actionWasPass = actionWasPass; }

	virtual Tile inspectTile(Position position) const
		{ return grid.at(position2GridIndex(position)); }

	virtual void setTile(Position position, Tile value)
		{ grid.at(position2GridIndex(position)) = value; }

	virtual Player whosTurn() const noexcept
		{ return playersTurn; }

	virtual void setTurn(Player player) noexcept
		{ playersTurn = player; }

	virtual int getBoardRows() const noexcept
		{ return boardRows; }

	virtual int getBoardColumns() const noexcept
		{ return boardColumns; }

	typedef std::vector<Tile>::iterator iterator;
	typedef std::vector<Tile>::const_iterator const_iterator;

	iterator begin() { return grid.begin(); }
	iterator end() { return grid.end(); }

private:

	/* Elements are stored in column major order. */
	int position2GridIndex(Position position) const noexcept
		{ return position.row + boardRows*position.column; }

	bool gameIsOver{false};
	bool actionWasPass{false};

	Player playersTurn;

	int boardRows;
	int boardColumns;
	std::vector<Tile> grid;
};

bool operator==(const OthelloState& state1, const OthelloState& state2)
	noexcept;

inline bool operator!=(const OthelloState& state1, const OthelloState& state2)
		noexcept
	{ return !(state1 == state2); }

inline std::ostream& operator<<(std::ostream& os, const OthelloState& state)
	{ return os << state.toString(); }

} //namespace othello

#endif //OTHELLO_STATE_HPP_
