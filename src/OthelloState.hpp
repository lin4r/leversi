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

// XXX Make generic iterator classes instead.
class OthelloBoardIterator
{
public:

	OthelloBoardIterator(std::vector<Tile>* board) noexcept : board{board} {}

	typedef std::vector<Tile>::iterator iterator;

	virtual iterator begin() { return board->begin(); }
	virtual iterator end() { return board->end(); }

private:

	std::vector<Tile>* board;
};

class ConstOthelloBoardIterator
{
public:

	ConstOthelloBoardIterator(const std::vector<Tile>* board) noexcept
			: board{board}
	{}

	typedef std::vector<Tile>::const_iterator const_iterator;

	virtual const_iterator begin() { return board->begin(); }
	virtual const_iterator end() { return board->end(); }

private:

	const std::vector<Tile>* board;
};

class OthelloState
{	
public:

	/**
	 * Creates an empty othello state. 8*8 board an black player starts.
	 */
	OthelloState() noexcept;

	/**
	 * params:
	 *	boardRows - The number of rows on the board.
	 *	boardColumns - The number of columns on the board.
	 *	starter - The palyer who starts.
	 */
	OthelloState(int boardRows, int boardColumns, Player starter) noexcept;

	virtual ~OthelloState() = default;

	/**
	 * Creates the inirtial state, according to othello rules.
	 * The central 2*2 square has white at positions (3,3) and (4,4) and black
	 * at (3,4) and (4,3).
	 * return:	The initial othello state.
	 */
	static OthelloState initialState() noexcept;

	/**
	 * Changes the player turn.
	 */
	virtual void changeTurn() noexcept;

	/**
	 * Flips the brick at the specified position, i.e. white bricjs will be
	 * black and vice versa. If the position has no brick (Tile::Empty), then
	 * nothing will happen.
	 * param:	Position to flip prick on.
	 * throws:	out_of_bound_exception if the position is outside the board.
	 */
	virtual void flipBrick(Position position);

	/**
	 * Checks if the specific position is inside the board.
	 * return:	true iff it is inside the board.
	 */
	virtual bool isInsideGrid(Position position) const noexcept;

	/**
	 * Creates a string representation of the state.
	 * return: string representation.
	 */
	virtual std::string toString() const noexcept;

	/**
	 * Creates a string representation of the board.
	 * return: string representation.
	 */
	virtual std::string boardString() const noexcept;

	/**
	 * Checks if game over.
	 * return true iff game over.
	 */
	virtual bool isGameOver() const noexcept
		{ return gameIsOver; }

	/**
	 * Sets the game over flag.
	 * param:	New game over status.
	 */
	virtual void setGameOver(bool gameOver) noexcept
		{ gameIsOver = gameOver; }

	/**
	 * Checks the action was pass flag (used to test if game over).
	 * return:	actionWasPass flag.
	 */
	virtual bool wasActionPass() const noexcept
		{ return actionWasPass; }

	/**
	 * Sets the action was pass flag (used to test if game over).
	 * param:	new actionWasPass flag.
	 */
	virtual void setActionWasPass(bool actionWasPass) noexcept
		{ this->actionWasPass = actionWasPass; }

	/**
	 * Gets the tile value at the specific position.
	 * param:	Position to inspect tile at.
	 * throws:	out_of_bound_exception if the position is outside the board. XXX No it doesn't
	 */
	virtual Tile inspectTile(Position position) const
		{ return board.at(position2GridIndex(position)); }

	/**
	 * Sets the tile value at the specified position.
	 * params:
	 *	position - Position to set value at.
	 *	value - new tile value.
	 * throws:	out_of_bound_exception if the position is outside the board. XXX No id doesn't.
	 */
	virtual void setTile(Position position, Tile value)
		{ board.at(position2GridIndex(position)) = value; }

	/**
	 * Checks whos turn it is.
	 * return:	The player whos turn it is.
	 */
	virtual Player whosTurn() const noexcept
		{ return playersTurn; }

	/**
	 * Sets whos turn it is.
	 * param:	Player whos turn it will be.
	 */
	virtual void setTurn(Player player) noexcept
		{ playersTurn = player; }

	/**
	 * Gets the number of rows of the board.
	 * return:	The number of rows.
	 */
	virtual int numBoardRows() const noexcept
		{ return boardRows; }

	/**
	 * Gets the number of board columns.
	 * return:	The number of columns.
	 */
	virtual int numBoardColumns() const noexcept
		{ return boardColumns; }

	/**
	 * Gets a iterator wrapper for the board.
	 * return:	Iterator.
	 */
	virtual OthelloBoardIterator boardIterator() noexcept
		{ return OthelloBoardIterator(&board); }

	/**
	 * Gets a const iterator for the board.
	 * return: const iterator.
	 */
	virtual ConstOthelloBoardIterator constBoardIterator() const noexcept
		{ return ConstOthelloBoardIterator(&board); }

private:

	/**
	 * Helper function for computing the column major indexx of the board.
	 * param:	Position.
	 * return:	Column major index corresponding to the position.
	 */
	int position2GridIndex(Position position) const noexcept
		{ return position.row + boardRows*position.column; }

	/**
	 * Flag indicating if the game is over.
	 */
	bool gameIsOver{false};

	/**
	 *  Flag indicating if the latest action was pass. It is needed becase game
	 * over ocurrs when two passes in a row has happened.
	 */
	bool actionWasPass{false};

	/**
	 * The player who's turn it is.
	 */
	Player playersTurn;

	/**
	 * The number of rows on the board.
	 */
	int boardRows;

	/**
	 * The number of columns on the board.
	 */
	int boardColumns;

	/**
	 * The othello board.
	 */
	std::vector<Tile> board;
};

bool operator==(const OthelloState& state1, const OthelloState& state2);

inline bool operator!=(const OthelloState& state1, const OthelloState& state2)
	{ return !(state1 == state2); }

inline std::ostream& operator<<(std::ostream& os, const OthelloState& state)
	{ return os << state.toString(); }

} //namespace othello

#endif //OTHELLO_STATE_HPP_
